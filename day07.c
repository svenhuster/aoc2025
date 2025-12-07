#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef DEBUG
#define DPRINT(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DPRINT(...) do {} while(0)
#endif

#define MAX_ROWS 256
#define MAX_COLS 1024
#define MAX_WIDTH 4096

int main(void)
{
	char input[MAX_ROWS][MAX_WIDTH] = {0};
	int row = 0;

	while(fgets(input[row], MAX_WIDTH, stdin)) {
		if (row >= MAX_ROWS) {
			assert(0 && "too many rows");
		}
		input[row][strlen(input[row]) - 1] = '\0';
		row++;
	}

	int rows = row;
	int cols = (int)strlen(input[0]);
	long long beam_col[cols+1];
	memset(beam_col, 0, sizeof(beam_col));

	beam_col[strchr(input[0], 'S') - input[0]] = 1;
	int splits = 0;
	for (int row = 1; row < rows; ++row) {
		for (int b = 1; b < cols-1; ++b) {
			if (beam_col[b] && input[row][b] == '^') {
				beam_col[b-1] += beam_col[b];
				beam_col[b+1] += beam_col[b];
				beam_col[b]    = 0;
				++splits;
			}
		}
	}

	long long total = 0;
	for (int i = 0; i < cols; ++i) {
		if (beam_col[i])
			total += beam_col[i];
	}

	printf("splits: %d\n", splits);
	printf("paths : %lld\n", total);
	return 0;
}
