/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
*/

bool search(int value, int values[], int n)
{
    int left = 0;
    int right = n-1;
    // this mid-point computation is used to avoid overflow
    while(left <= right)
    {
        int mid = (right - left)/2 + left;
        if(values[mid] == value)
        {
            return true;
            break;
        }
        else if(values[mid] > value)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    int counter = 1;
    while(counter > 0)
    {
        counter = 0;
        for(int i=0; i<n-1; i++)
        {
            if(values[i] > values[i+1])
            {
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                counter ++;
            }
        }
    }
    return;
}

