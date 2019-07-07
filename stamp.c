#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int prefix = 1;
	int ch;
	int decimals = 6;
	int divider = 1;
	char ns[11] = { 0 };

	while ((ch = getopt(argc, argv, "0123456789")) != EOF) {
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			decimals = ch - '0';
			break;
		}
	}
	for (int i = 9; i > decimals; i--)
		divider *= 10;

	while ((ch = fgetc(stdin)) != EOF) {
		if (prefix) {
			struct timespec ts;
			if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
				perror("clock_gettime");
				exit(1);
			}
			if (decimals)
				snprintf(ns, sizeof(ns), ".%*ld", decimals,
				         ts.tv_nsec / divider);
			printf("%02ld:%02ld:%02ld%s: ",
			       ts.tv_sec / 3600 % 24, ts.tv_sec / 60 % 60,
			       ts.tv_sec % 60, ns);
			prefix = 0;
		}
		fputc(ch, stdout);
		prefix = ch == '\n';
	}
	return 0;
}
