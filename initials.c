#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();
    if (name != NULL)
    {
        for (int i=0, n=strlen(name); i<n; i++)
        {
            if (name[i]!=' ')
            {
                char ch = islower(name[i]) ? toupper(name[i]):name[i];
                printf("%c", ch);
                
                // if (islower(name[i]))
                // {
                //     printf("%c", toupper(name[i]));
                // }
                // else
                // {
                //     printf("%c", name[i]);
                // }
                while (i+1 < n && name[i+1] != ' ')
                {
                    i++;
                }
            }
        }
        printf("\n");
    }
}