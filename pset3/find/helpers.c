/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
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
    if (n <= 0)
        return false;
    // implement a searching algorithm
    int min = 0;
    int max = n;
    bool found = false;
    int breakCounter = 0;

    do
    {
        int i = ((max - min) / 2) + min;
        printf ("i: %i, min: %i, max: %i\n", i, min, max);
        if (value == values[i])
            found = true;
        else
            if (value > values[i])
                min = i++;
            else
                max = i--;
        
        if ((max - min) == 1)
            breakCounter++;
        
        if (breakCounter > 1)
            break;
    }
    while (!found);
    return found;
}

/*
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int swaps = 0;
    // implement an O(n^2) sorting algorithm
    if (n <= 0)
        return;

    do
    {
        swaps = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i+1])
            {
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                swaps++;
            }
        }
    }
    while (swaps > 0);
    
    return;
}
