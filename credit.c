#include <stdio.h>
#include <cs50.h>


bool isValidCard( long long passedInNumber);
void printType(long long number);

int main(void)
{
    printf("Number: ");
    long long cnumber = get_long_long();
    printType(cnumber);
} 


bool isValidCard( long long passedInNumber) {
    long long number = passedInNumber;
    bool isOdd = true;
    int sum = 0;
    while (number > 0) 
    {
        int digit = number % 10;
        if (isOdd) 
        {
            sum += digit;
        } 
        else 
        {
            int tmp = digit * 2;
            if (tmp > 9) 
            {
                tmp = 1 + tmp%10;
            }
            sum += tmp;
        }
        number  = number / 10;
        isOdd = !isOdd;
    }
    return (sum%10 == 0);
}


void printType(long long number) {
    if (isValidCard(number)) 
    {
        while(number>100)
        {
            number=number/10;
        }
        if(number == 34 || number == 37)
        {
            printf("AMEX\n");
        }
        else if(number >= 51 && number <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if(number >= 40 && number <= 49)
        {
            printf("VISA\n");
        }
        else printf("INVALIDCARDTYPE\n");
    }
    else
    {
        printf("%s\n", "INVALID");
    }
}