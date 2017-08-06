/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
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
    int counter[65536] = {};
    for(int i=0; i<65536; i++)
    {
        counter[i] = 0;
    }
    for(int i=0; i<n; i++)
    {
        int temp = values[i];
        counter[temp]++;
    }

    int k = 0;
    int j = 0;
    for(int i=0; i<65536; i++)
    {
        if(counter[i] > 0)
        {
            j = counter[i];
            while(j > 0)
            {
                values[k] = i;
                k++;
                j--;
            }
        }
    }
}

