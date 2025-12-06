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

#define MAX_ROW 256
#define MAX_LEN 64

int cmp_ingredient_ranges(const void *v1, const void *v2)
{
	const long long *i1 = v1;
	const long long *i2 = v2;

	return (i1[0] > i2[0]) - (i1[0] < i2[0]) ?
	       (i1[0] > i2[0]) - (i1[0] < i2[0]) :
               (i1[1] > i2[1]) - (i1[1] < i2[1]);
}

int main(void)
{
	long long ingredients[MAX_ROW][2];

	char ingredient_input[MAX_LEN] = {0};
	int fresh = 0;
	int ingredient_ranges = 0;

	while(fgets(ingredient_input, MAX_LEN, stdin)) {
		if (ingredient_ranges >= MAX_ROW) {
			assert(0 && "too many rows");
		}
		ingredient_input[strlen(ingredient_input) - 1] = '\0';
		if (strcmp(ingredient_input, "") == 0)
			break;

		char *split = strchr(ingredient_input, '-');
		assert(split && "separator '-' not found");

		*split = '\0';
		ingredients[ingredient_ranges][0] = strtoll(ingredient_input, NULL, 10);
		ingredients[ingredient_ranges][1] = strtoll(split+1, NULL, 10);
		DPRINT("Range: %lld %lld\n", ingredients[ingredient_ranges][0], ingredients[ingredient_ranges][1]);
		++ingredient_ranges;
	}

	qsort(ingredients, (size_t)ingredient_ranges, sizeof(long long[2]), cmp_ingredient_ranges);

	switch (AOCPART) {
	case 1:
		while(fgets(ingredient_input, MAX_LEN, stdin)) {
			assert(strcmp(ingredient_input, "\n") && "empty line unexpected");
			ingredient_input[strlen(ingredient_input) - 1] = '\0';

			long long ingredient = strtoll(ingredient_input, NULL, 10);
			DPRINT("I: %lld\n", ingredient);
			for (int i = 0; i < ingredient_ranges; ++i) {
				bool in_range = ingredients[i][0] <= ingredient &&
						ingredients[i][1] >= ingredient;
				if (in_range) {
					++fresh;
					break;
				}
				DPRINT("C: %16lld <= %16lld <= %16lld %2d\n",
				       ingredients[i][0], ingredient, ingredients[i][1], in_range);
			}
		}
		printf("%d\n", fresh);
		break;
	case 2:
		;
		long long total = 0;
		int left = 0;
		int right = 1;
		char *debug_action;

		DPRINT("Ranges before: %d\n", ingredient_ranges);
		while (right < ingredient_ranges) {
			DPRINT("Left : %16lld %16lld\n", ingredients[left][0], ingredients[left][1]);
			DPRINT("Right: %16lld %16lld\n", ingredients[right][0], ingredients[right][1]);
			if (ingredients[left][1] < ingredients[right][0]) {
				++left;
				ingredients[left][0] = ingredients[right][0];
				ingredients[left][1] = ingredients[right][1];
				debug_action = "Next";
			} else if (ingredients[left][1] < ingredients[right][1]) {
				ingredients[left][1] = ingredients[right][1];
				debug_action = "Expand";
			} else {
				debug_action = "Within";
			}
			++right;
			DPRINT("-----: %45s\n", debug_action);
		}
		DPRINT("Ranges after: %d\n", left+1);
		for (int i = 0; i <= left; ++i) {
			total += ingredients[i][1] - ingredients[i][0] + 1;
		}
		printf("%lld\n", total);
		break;
	}
	return 0;
}
