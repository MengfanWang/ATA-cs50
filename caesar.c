#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        printf("plaintext: ");
        string text = get_string();
        printf("ciphertext: ");
        for(int i=0, n=strlen(text); i<n; i++)
        {
            char ch = text[i];
            if (ch >= 'A' && ch <= 'Z') 
            {
                char index = (ch - 'A' + k) % 26;
                printf("%c", (char)(index + 'A'));
            } 
            else if (ch >= 'a' && ch <= 'z') 
            {
                char index = (ch - 'a' + k) % 26;
                printf("%c", (char)(index + 'a'));
            } 
            else {
                printf("%c", ch);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}