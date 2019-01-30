#define _GNU_SOURCE

#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BAIL() exit(1)

void setup(void);
void dump_file(char *);
size_t count2d(char ** arr);
char * choose2d(char ** arr);

static char * usernames[] = {
	"root",
	"admin",
	"cdc",
	NULL
};

static char * lsfiles[] = {
	"ls1.txt",
	"ls2.txt",
	"ls3.txt",
	"ls4.txt",
	NULL
};

static char * hostnames[] = {
	"db1",
	"db2",
	"db3",
	"db4",
	"db5",
	"atm",
	"www",
	"firewall",
	NULL
};

static char * ascii_art[] = {
	"owl.txt",
	"owl2.txt",
	NULL
};

int main()
{
	srand(time(NULL));

	int root = !(rand() % 8);
	char * hostname = choose2d(hostnames);
	char * username = root ? usernames[0] : choose2d(usernames);

	char prompt[128];
	memset(prompt, 0, 128);
	snprintf(prompt, 127, "%s@%s ~ %s ", username, hostname, root ? "#" : "$");

	char * line = NULL;
	size_t linelen = 0;
	for (size_t i = 0; i < 32; i++) {
		if (i > 3 ) {
			dump_file("funpit.txt");
		}

		fputs(prompt, stdout);

		ssize_t len = getline(&line, &linelen, stdin);
		if (len < 0) {
			perror("getline");
			BAIL();
		}

		line[strlen(line) - 1] = '\0';

		char * tok = strtok(line, " ");
		if (!strcmp("ls", tok)) {
			dump_file(choose2d(lsfiles));
		} else if (!strcmp("cat", tok)) {
			dump_file(choose2d(ascii_art));
		} else if (!strncmp("su", tok, 2)) {
			dump_file("jurrasic.txt");
		} else {
			if (rand() % 3) {
				dump_file(choose2d(ascii_art));
			} else {
				printf("%s: command not found\n", tok);
			}
		}
	}
}

void dump_file(char * fname)
{
	FILE * f = fopen(fname, "r");
	if (f == NULL) {
		perror("fopen");
	}

	char * line = NULL;
	size_t linelen = 0;
	do {
		ssize_t len = getline(&line, &linelen, f);
		if (len < 1) {
			break;
		}
		fwrite(line, 1, strlen(line), stdout);
	} while (!feof(f));

	fclose(f);
}

size_t count2d(char ** arr)
{
	size_t i = 0;
	while (arr[i] != NULL) {
		i++;
	}

	return i;
}

char * choose2d(char ** arr)
{
	size_t n = count2d(arr);
	n = rand() % n;

	return arr[n];
}
