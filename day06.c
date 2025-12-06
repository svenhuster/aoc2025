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
	long long total = 0;

	char input[MAX_ROWS][MAX_WIDTH] = {0};
	int row = 0;

	while(fgets(input[row], MAX_WIDTH, stdin)) {
		if (row >= MAX_ROWS) {
			assert(0 && "too many rows");
		}
		row++;
	}

	int cols[MAX_COLS];

	char *current = input[row-1];
	int col = 0;
	while (*current != '\0') {
		while (*current == ' ') {
			++current;
		}
		cols[col] = (int)(current - input[row-1]);
		++current;
		++col;
	}

	switch (AOCPART) {
	case 1:
		for (int c = 0; c < col-1; ++c) {
			char op = *(input[row-1] + cols[c]);
			DPRINT("OP: %c\n", op);
			long long acc = 1;
			for (int r = 0; r < row-1; ++r) {
				long long value = strtoll(input[r] + cols[c], NULL, 10);
				if (op == '+')
					acc += value;
				else
					acc *= value;
				DPRINT("VAL: %lld\n", value);
			}

			if (op == '+')
				--acc;

			DPRINT("ACC: %lld\n", acc);
			total += acc;
			DPRINT("\n");
		}
		break;
	case 2:
		for (int c = col-1; c > 0; --c) {
			char op = *(input[row-1] + cols[c-1]);
			DPRINT("OP: %c\n", op);
			long long acc = 1;
			for (int i = cols[c]-1; i >= cols[c-1]; --i) {
				int col_acc = 0;
				for (int r = 0; r < row-1; ++r) {
					int digit = *(input[r] + i) - '0';
					if (0 <= digit && digit <= 9) {
						col_acc *= 10;
						col_acc += digit;
					}
				}
				if (col_acc > 0) {
					if (op == '+')
						acc += col_acc;
					else
						acc *= col_acc;
					DPRINT("%d\n", col_acc);
				}
			}
			if (op == '+')
				--acc;

			DPRINT("ACC: %lld\n", acc);
			total += acc;
			DPRINT("\n");
		}
		break;
	}
	printf("%lld\n", total);
	return 0;
}
