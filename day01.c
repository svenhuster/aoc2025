#include <stdio.h>

#ifdef DEBUG
#define DPRINT(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DPRINT(...) do {} while(0)
#endif

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	char direction;
	int steps;

	int position = 50;
	int zero_count = 0;

	while (scanf("%c%d\n", &direction, &steps) == 2) {
		switch (AOCPART) {
		case 1:		/* part 1 */
			if (direction == 'L') {
				position -= steps;
			} else {
				position += steps;
			}

			position = ((position % 100) + 100) % 100;

			if (position == 0)
				++zero_count;
			break;

		case 2:		/* part 2 */
			zero_count += steps / 100;
			steps %= 100;

			if (direction == 'L') {
				if (position != 0 && position <= steps)
					++zero_count;
				position -= steps;
			} else {
				if (100 - position <= steps)
					++zero_count;
				position += steps;
			}
			position = ((position % 100) + 100) % 100;
			break;
		}
		DPRINT("%c %d => %d / %d\n", direction, steps, position, zero_count);
	}
	printf("%d\n", zero_count);
}
