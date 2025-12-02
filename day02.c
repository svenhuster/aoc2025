#include <stdio.h>
#include <math.h>

#ifdef DEBUG
#define DPRINT(...) printf("DEBUG: " __VA_ARGS__)
#else
#define DPRINT(...) do {} while(0)
#endif

int main(int argc, char** argv)
{
  (void)argc;
  (void)argv;

  long long start, end;
  long long total = 0;

  while (scanf("%lld-%lld,", &start, &end) == 2) {
    switch (AOCPART) {
    case 1: 			// part 1
      for (long long i = start; i <= end; ++i) {
	int len = (int)log10((double)i) + 1;
	if (len % 2 == 0) {
	  long long mask = (long long)pow(10, len/2);
	  long long first = i / mask;
	  long long second = i % mask;
	  if (first == second)
	    total += (long long)i;
	  DPRINT("%lld %lld %lld %d\n", i, first, second, first == second);
	}
      }
      break;

    case 2:			// part 2
      for (long long i = start; i <= end; ++i) {
	int len = (int)log10((double)i) + 1;
	int success = 0;
	for (int recur = 1; recur <= len/2 && !success; ++recur) {
	  if (len % recur == 0) {
	    long long rem;
	    long long num = i;
	    long long match = num % (long long)pow(10, recur);
	    while (num > 0) {
	      rem = num % (long long)pow(10, recur);
	      if (rem != match)
		goto FAILED;
	      num /= (long long)pow(10, recur);
	    }
	    total += i;
	    success = 1;
	    DPRINT("i:%lld rem:%lld\n", i, rem);
	  FAILED:
	    ;
	  }
	}
      }
      break;

    }
  }

  printf("%lld\n", total);
}
