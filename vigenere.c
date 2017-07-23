#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool isValidInput(string input) 
{
	for(int i=0; i<strlen(input); i++) 
	{
		char ch = input[i];
		if (!((ch >='a' && ch <='z')||(ch>='A' && ch <='Z'))) 
		{
			return false;
		}
	}
	return true;
}


int main(int argc, string argv[])
{
	if (argc != 2 || !isValidInput(argv[1])) {
		printf("Usage: ./vigenere k\n");
		return 1;
	}
	int h = 0;
	string key = argv[1];
	printf("plaintext: ");
	string text = get_string();
	printf("ciphertext: ");
	for(int i=0, n=strlen(text); i<n; i++)
	{
		int j= h%strlen(key);
		int k = toupper(key[j])-'A';
		char ch = text[i];
		if (ch >= 'A' && ch <= 'Z') 
		{
			char index = (ch - 'A' + k) % 26;
			printf("%c", (char)(index + 'A'));
			h++;
		} 
		else if (ch >= 'a' && ch <= 'z') 
		{
			char index = (ch - 'a' + k) % 26;
			printf("%c", (char)(index + 'a'));
			h++;
		} 
		else {
			printf("%c", ch);
		}
	}
	printf("\n");
	return 0;
}
