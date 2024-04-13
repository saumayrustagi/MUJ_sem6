#include <stdio.h>
#include <ctype.h>
#include <string.h>
void encipher();
void decipher();
int main()
{
	encipher();
	return 0;
}
void encipher()
{
	unsigned int i, j;
	char input[50], key[10];
	printf("Enter Plain Text: ");
	scanf("%s", input);
	printf("\nEnter Key Value: ");
	scanf("%s", key);
	printf("\nResultant Cipher Text: ");
	for (i = 0, j = 0; i < strlen(input); i++, j++)
	{
		if (j >= strlen(key))
		{
			j = 0;
		}
		printf("%c", 65 + (((toupper(input[i]) - 65) + (toupper(key[j]) -
														65)) %
						   26));
	}
	printf("\n");
}
void decipher()
{
	unsigned int i, j;
	char input[50], key[10];
	int value;
	printf("\n\nEnter Cipher Text: ");
	scanf("%s", input);
	printf("\n\nEnter the key value: ");
	scanf("%s", key);
	for (i = 0, j = 0; i < strlen(input); i++, j++)
	{
		if (j >= strlen(key))
		{
			j = 0;
		}
		value = (toupper(input[i]) - 64) - (toupper(key[j]) - 64);
		if (value < 0)
		{
			value = value * -1;
			printf("%c", 65 + (value % 26));
		}
	}
}