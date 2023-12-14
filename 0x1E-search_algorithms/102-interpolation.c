#include "search_algos.h"
#include <stdio.h>

/**
 * interpolation_search - Searches for a value in a sorted
 * array using Interpolation search
 * @array: Pointer to the first element of the sorted array
 * @size: Number of elements in array
 * @value: Value to search for
 *
 * Return: The index where value is located, or -1
 * if value is not present or array is NULL
 */
int interpolation_search(int *array, size_t size, int value)
{
	size_t low = 0, high = size - 1, pos;

	if (array == NULL)
		return (-1);

	while (low <= high && value >= array[low] && value <= array[high])
	{
		pos = low + (((double)(high - low) / (array[high] - array[low])) *
					(value - array[low]));
		printf("Value checked array[%lu] = [%d]\n", pos, array[pos]);
		if (array[pos] == value)
			return (pos);

		if (array[pos] < value)
			low = pos + 1;
		else
			high = pos - 1;
	}
	if (value < array[low] || value > array[high])
		printf("Value checked array[%lu] is out of range\n", pos);
	return (-1);
}
