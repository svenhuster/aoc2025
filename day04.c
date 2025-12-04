#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define DPRINT(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DPRINT(...) do {} while(0)
#endif

#define MAX_GRID 256

int check_neighbor(char grid[MAX_GRID][MAX_GRID], int y, int x, int height, int width)
{
	if (0 <= x && x < width && 0 <= y && y < height)
		return grid[y][x] == '@';

	return 0;
}

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	char grid[MAX_GRID][MAX_GRID];
	long long total = 0;

	int height = 0;
	while (fgets(grid[height], MAX_GRID, stdin)) {
		/* grid[height][strlen(grid[height]) - 1] = 0; */
		++height;
	}

	/* int width = (int)strlen(grid[0]); */
	int width = (int)strlen(grid[0]) - 1;

	DPRINT("Grid size: %d/%d\n", width, height);

	int running = 1;
	while (running) {
		running = 0;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (grid[y][x] == '@') {
					int neighbors = 0;
					neighbors += check_neighbor(grid, y-1, x,   height, width);
					neighbors += check_neighbor(grid, y+1, x,   height, width);
					neighbors += check_neighbor(grid, y,   x-1, height, width);
					neighbors += check_neighbor(grid, y,   x+1, height, width);
					neighbors += check_neighbor(grid, y-1, x-1, height, width);
					neighbors += check_neighbor(grid, y-1, x+1, height, width);
					neighbors += check_neighbor(grid, y+1, x-1, height, width);
					neighbors += check_neighbor(grid, y+1, x+1, height, width);
					if (neighbors < 4) {
						++total;
						if (AOCPART == 2) {
							running = 1;
							grid[y][x] = '.';
						}
					}
					DPRINT("Loc: %d/%d %c %d %d\n", y, x, grid[y][x], neighbors, neighbors < 4);
				}
			}
		}
	}

	printf("%lld\n", total);
}
