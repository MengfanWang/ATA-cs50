#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i;
    int j;
    int k;
    int height;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while(height < 0 || height > 23);
    for(i=0; i<height; i++)
    {
        for(j=3; j>i; j--)
        {
            printf(" ");
        }
        for(k=0; k<i+2; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}