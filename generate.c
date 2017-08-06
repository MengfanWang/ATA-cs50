/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if there is no 1 or 2 command-line arguments then print out error info
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // take the user input of first command-line arguments argv[1] and convert it to an integer and pass to variable n
    int n = atoi(argv[1]);

    // if user inputs include a third command-line arguments then generate the pseudorandom-number with a seed of atoi(argv[2]), otherwise generate the pseudorandom-number without a seed
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // keep generating the pseudorandom-number until it hits the number of pseudorandom numbers user indicates to generate (n)
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
