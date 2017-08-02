#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <crypt.h>
#define _XOPEN_SOURCE

int main(int argc, string argv[])
{
	if (argc != 2) 
	{
		printf("Usage: ./crack hash\n");
		return 1;
	}
	string input = argv[1];
	// construct an array for a-z and A-Z
    char dict[52] = {};
    for(int i=0; i<26; i++)
    {
        dict[i] = (char) (i+65); 
        dict[i+26] = tolower((char) (i+65));
    }
        
    // one character case
    //string key1 = "a";
    char *key1 = (char*)malloc(2*sizeof(char));  
    key1[1] = '\0';
    for(int i=0; i<52; i++)
    {
        key1[0] = dict[i];
        if(strcmp(crypt(key1,"50"), input) == 0)
        {
            printf("%s\n", key1);
	        return 0;
        }
    }
    // two characters case
    //string key2 = "aa";
    char *key2 = (char*)malloc(3*sizeof(char));
    key2[3] = '\0';
    for(int i=0; i<52; i++)
    {
        key2[0] = dict[i];
        for(int j=0; j<52; j++)
        {
            key2[1] = dict[j];
            if(strcmp(crypt(key2,"50"), input) == 0)
            {
                printf("%s\n", key2);
    	        return 0;
            }
        }
    }
    // three characters case
    //string key3 = "aaa";
    char *key3 = (char*)malloc(4*sizeof(char));
    key3[4] = '\0';
    for(int i=0; i<52; i++)
    {
        key3[0] = dict[i];
        for(int j=0; j<52; j++)
        {
            key3[1] = dict[j];
            for(int k=0; k<52; k++)
            {
                key3[2] = dict[k];
                if(strcmp(crypt(key3,"50"), input) == 0)
                {
                    printf("%s\n", key3);
        	        return 0;
                }
            }
        }
    }
    // four characters case
    //string key4 = "aaaa";
    char *key4 = (char*)malloc(5*sizeof(char));
    key4[5] = '\0';
    for(int i=0; i<52; i++)
    {
        key4[0] = dict[i];
        for(int j=0; j<52; j++)
        {
            key4[1] = dict[j];
            for(int k=0; k<52; k++)
            {
                key4[2] = dict[k];
                for(int l=0; l<52; l++)
                {
                    key4[3] = dict[l];
                    if(strcmp(crypt(key4,"50"), input) == 0)
                    {
                        printf("%s\n", key4);
            	        return 0;
                    }
                }
            }
        }
    }
    
}

