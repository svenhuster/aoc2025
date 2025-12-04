#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define DPRINT(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DPRINT(...) do {} while(0)
#endif

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	char battery_bank[256];
	long long total = 0;

	while (scanf("%s\n", battery_bank) != EOF) {
		int n = (int)strlen(battery_bank);
		DPRINT("Bank: %s\n", battery_bank);

		long long res[12];
		memset(res, -1, sizeof(res));

		int digits;
		switch (AOCPART) {
		case 1:
			digits = 2;
			break;
		case 2:
			digits = 12;
			break;
		}

		int last_max = -1;
		for (int place = 0; place < digits; ++place) {
			int max = -1;
			for (int left = last_max + 1; left < n - digits + place + 1; ++left) {
				int battery = battery_bank[left] - '0';
				if (battery > max) {
					last_max = left;
					max = battery;
					res[place] = battery;
				}
				DPRINT("%d %d %d %d %d res: "
				       "%lld/%lld/%lld/%lld/%lld/%lld/%lld/%lld/%lld/%lld/%lld/%lld\n",
				       last_max, place, left, battery, max,
				       res[0], res[1], res[2], res[3], res[4], res[5],
				       res[6], res[7], res[8], res[9], res[10], res[11]
				       );
			}
		}



		long long joltage = 0;
		for (int k = 0; k < digits; ++k) {
			joltage *= 10;
			joltage += res[k];
		}
		total += joltage;
	}
	printf("%lld\n", total);
}
