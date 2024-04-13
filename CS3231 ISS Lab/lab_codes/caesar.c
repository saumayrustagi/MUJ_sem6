#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
	char plain[] = "hello", cipher[10];
	int key = 5, i, length;
	printf("ENCRYPTED: ");
	for (i = 0, length = strlen(plain); i < length; i++)
	{
		cipher[i] = plain[i] + key;
		if (isupper(plain[i]) && (cipher[i] > 'Z'))
			cipher[i] = cipher[i] - 26;
		if (islower(plain[i]) && (cipher[i] > 'z'))
			cipher[i] = cipher[i] - 26;
		printf("%c", cipher[i]);
	}
	printf("\nDECRYPTED: ");
	for (i = 0; i < length; i++)
	{
		plain[i] = (char)(cipher[i] - key);
		if (isupper(cipher[i]) && (plain[i] < 'A'))
			plain[i] = plain[i] + 26;
		if (islower(cipher[i]) && (plain[i] < 'a'))
			plain[i] = plain[i] + 26;
		printf("%c", plain[i]);
	}
	putchar('\n');
}