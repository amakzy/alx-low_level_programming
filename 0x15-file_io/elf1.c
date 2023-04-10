#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, 98 on error
 */

int main(int argc, char **argv)
{
	int fd;
	ssize_t n;
	Elf64_Ehdr header;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		exit(98);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Cannot open %s\n", argv[1]);
		exit(98);
	}
	n = read(fd, &header, sizeof(header));
	if (n == -1 || n != sizeof(header))
	{
		fprintf(stderr, "Error reading %s\n", argv[1]);
		close(fd);
		exit(98);
	}
	if (header.e_ident[EI_MAG0] != ELFMAG0 ||
			header.e_ident[EI_MAG1] != ELFMAG1 ||
			header.e_ident[EI_MAG2] != ELFMAG2 ||
			header.e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "%s is not an ELF file\n", argv[1]);
		close(fd);
		exit(98);
	}
	printf("ELF Header:\n");
	printf("  Magic:   ");

	for (int i = 0; i < EI_NIDENT; i++)
		printf("%02x ", header.e_ident[i]);
	printf("\n");
	printf("  Class:                             ");
	switch (header.e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", header.e_ident[EI_CLASS]);
		break;
	}
	printf("  Data:                              ");
	switch (header.e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", header.e_ident[EI_DATA]);
		break;
	}
	printf("  Version:                           ");
	switch (header.e_ident[EI_VERSION])
	{
	case EV_NONE:
		printf("0 (invalid)\n");
		break;
	case EV_CURRENT:
		printf("%d (current)\n", header.e_ident[EI_VERSION]);
		break;
	default:
		printf("%d\n", header.e_ident[EI_VERSION]);
		break;
	}
	printf("  OS/ABI:                            ");
	switch (header.e_ident[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("Sun Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("SGI Irix\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("Compaq TRU64 UNIX\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM architecture\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone (embedded) application\n");
		break;
	default:
		printf("<unknown: %x>\n", header.e_ident[EI_OSABI]);
		break;
	}
	printf("  ABI Version:                       ");
	printf("%d\n", header.e_ident[EI_ABIVERSION]);
	printf("  Type:                              ");
	switch (header.e_type)
	{
	case ET_NONE:
		printf("NONE (Unknown type)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", header.e_type);
		break;
	}
	printf("  Entry point address:               ");
	printf("%#lx\n", header.e_entry);
	close(fd);
	return (0);
}

