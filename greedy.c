#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int left_over;
    do
    {
        printf("O hai! How much change is owed?\n");
        change = get_float();
    }
    while(change < 0);
    int i = (int)round(change*100);
    
    int quarter_count = i/25;
    left_over = i%25;
    
    int dime_count = left_over/10;
    left_over = left_over%10;
    
    int nickel_count = left_over/5;
    left_over = left_over%5;
    
    printf("%i\n", quarter_count + dime_count + nickel_count + left_over);
}