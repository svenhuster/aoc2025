#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLS 1024
#define MAX_WIDTH 4096

int main(void)
{
	int splits = 0;
	long long beam_col[MAX_WIDTH] = {0};

	char input[MAX_WIDTH] = {0};
	int first_row = 0;
	while(fgets(input, MAX_WIDTH, stdin)) {
		input[strlen(input) - 1] = '\0';
		if (first_row == 0) {
			beam_col[strchr(input, 'S') - input] = 1;
			++first_row;
		} else {
			for (int b = 1; b < MAX_COLS-1; ++b) {
				if (beam_col[b] && input[b] == '^') {
					beam_col[b-1] += beam_col[b];
					beam_col[b+1] += beam_col[b];
					beam_col[b]    = 0;
					++splits;
				}
			}
		}
	}

	long long paths = 0;
	for (int i = 0; i < MAX_COLS; ++i) {
		if (beam_col[i])
			paths += beam_col[i];
	}

	printf("splits: %d\n", splits);
	printf("paths : %lld\n", paths);
	return 0;
}
