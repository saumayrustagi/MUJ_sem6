// CEASER CIPHER - ENCODE + DECODE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define USAGE_STR "Usage: %s [e|d] INFILE OUTFILE SHIFT_NUMBER\n\nEXAMPLE: %s d en.txt de.txt 1\n", argv[0], argv[0]

void shift(char* original, int key, bool transform){
	if (transform) *original = (*original + key) % 255;
	else *original = (*original - key) % 255;
}

void encoder(FILE* inp, FILE* out, int key){
	char buf[4096];
	ssize_t nread;
	
	while ((nread = fread(buf, sizeof(buf[0]), sizeof(buf), inp)) > 0)
	{
		for (ssize_t i = 0; i < nread; ++i)
		{
			shift(&buf[i], key, true);
		}
		ssize_t totalwr = 0;
		ssize_t nwr;

		while(totalwr < nread){
			nwr = fwrite(buf, sizeof(buf[0]), (size_t)nread, out);
			totalwr += nwr;
		}
	}
}

void decoder(FILE* inp, FILE* out, int key){
	char buf[4096];
	ssize_t nread;
	
	while ((nread = fread(buf, sizeof(buf[0]), sizeof(buf), inp)) > 0)
	{
		for (ssize_t i = 0; i < nread; ++i)
		{
			shift(&buf[i], key, false);
		}
		ssize_t totalwr = 0;
		ssize_t nwr;

		while(totalwr < nread){
			nwr = fwrite(buf, sizeof(buf[0]), (size_t)nread, out);
			totalwr += nwr;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		fprintf(stderr, USAGE_STR);
		return 1;
	}

	FILE *inp, *out;

	if ((inp = fopen(argv[2], "r")) == NULL)
		error(1, errno, "%s", argv[1]);
	if ((out = fopen(argv[3], "w+")) == NULL)
		error(1, errno, "%s", argv[2]);

	char transform;
	sscanf(argv[1], "%c", &transform);

	int key;
	if (sscanf(argv[4], "%d", &key) < 1)
	{
		fprintf(stderr, USAGE_STR);
		return 1;
	}

	if(transform == 'e') encoder(inp, out, key);
	else if (transform == 'd') decoder(inp, out, key);
	else
	{
		fprintf(stderr, USAGE_STR);
		return 1;
	}

	fclose(out);
	fclose(inp);

	return 0;
}
