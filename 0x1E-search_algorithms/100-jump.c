#include "search_algos.h"
#include <math.h>
#include <stdio.h>

/**
 * jump_search - Searches for a value in a sorted array using Jump search
 * @array: Pointer to the first element of the sorted array
 * @size: Number of elements in array
 * @value: Value to search for
 *
 * Return: The index where value is located,
 *         or -1 if value is not present or array is NULL
 */
int jump_search(int *array, size_t size, int value)
{
	size_t jump = sqrt(size);
	size_t left = 0, right = 0, i;

	if (array == NULL)
		return (-1);

	while (right < size && array[right] < value)
	{
		printf("Value checked array[%lu] = [%d]\n", right, array[right]);
		left = right;
		right += jump;
	}
	printf("Value found between indexes [%lu] and [%lu]\n", left, right);
	for (i = left; i <= right && i < size; i++)
	{
		printf("Value checked array[%lu] = [%d]\n", i, array[i]);
		if (array[i] == value)
			return (i);
	}
	return (-1);
}
