#include "search_algos.h"
#include <stdio.h>

/**
 * exponential_search - Searches for a value in a sorted
 *
 * array using Exponential search
 * @array: Pointer to the first element of the sorted array
 * @size: Number of elements in array
 * @value: Value to search for
 *
 * Return: The index where value is located,
 *         or -1 if value is not present or array is NULL
 */
int exponential_search(int *array, size_t size, int value)
{
	size_t bound = 1, low, high, min, i;

	if (array == NULL || size == 0)
		return (-1);

	while (bound < size && array[bound] < value)
	{
		printf("Value checked array[%lu] = [%d]\n", bound, array[bound]);
		bound *= 2;
	}
	low = bound / 2;
	high = bound < size - 1 ? bound : size - 1;
	printf("Value found between indexes [%lu] and [%lu]\n", low, high);
	while (low <= high)
	{
		min = (low + high) / 2;
		printf("Searching in array: ");
		for (i = low; i <= high; i++)
		{
			printf("%d", array[i]);
			if (i < high)
				printf(", ");
			else
				printf("\n");
		}
		if (array[min] == value)
			return (min);
		if (array[min] < value)
			low = min + 1;
		else
			high = min - 1;
	}
	return (-1);
}
