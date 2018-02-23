/*
 * Tom Maltese
 * BST combinations.
 * the function 'benchmark' is the method we know is true/correct
 * 'test' is what I am proposing. It does half the work.
 * 
 * We simply use an array for the cache.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)

void cache_init(long int size);
long int benchmark(long int size);
long int test(long int size);
void die(char const *fmt, ...);
long int parseIntL(char const *s);

long int *cache = NULL;

void cache_init(long int size)
{
	cache = calloc(size, sizeof *cache);       /* calloc -> zero initialized */
	if (!cache)
		die("Out of memory\n");
}
long int benchmark(long int size)
{
	if (size <= 1)
		return 1;
	if (cache[size])
		return cache[size];
	long int total = 0;
	for (long int i = 1; i <= size; i++) {
		long int L = benchmark(i - 1);
		long int R = benchmark(size - i);
		total += L * R;
	}
	cache[size] = total;
	return total;
}
long int test(long int size)
{
	if (size <= 1)
		return 1;
	if (cache[size])
		return cache[size];
	long int total = 0;
	long int last = 0;
	long int top = size;
	long int m = size / 2;
	while (top-- > m) {
		long int R = test(top);
		long int L = test(size - top - 1);
		last = total;
		total += L * R;
	}
	long int ret;
	if (size % 2 == 0)
		ret = total * 2;
	else
		ret = (last * 2) + (total - last);
	cache[size] = ret;
	return ret;
}
void die(char const *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}
long int parseIntL(char const *s)
{
	char *fail;
	long int val = strtol(s, &fail, 10);
	if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		die("Integer out of range\n");
	if (fail == s)
		die("Invalid input\n");
	return val;
}
int main(int argc, char **argv)
{
	if (argc < 2)
		die("Usage: %s [INT]...\n"
                    "Compute the number of unique combinations of a BST of size [INT]...\n", argv[0]);
	/* first find out how much memory we need to allocate for the cache */
	long int cachesize = 0;
	int argc_ = argc - 1;
	char **argv_ = argv + 1;
	for ( ;  argc_; argc_--, argv_++) {
	             char *s = *argv_;
	             cachesize = MAX(cachesize, parseIntL(s));
	}
	cache_init(cachesize + 1);
	printf("  N   |  benchmark(N) |  test(N)\n");
	while (--argc) {
		char *s = *++argv;
		long int size = parseIntL(s);
		long int b = benchmark(size);
		long int t = test(size);
		if (b != t)
			die("Test failed for size = %d. Benchmark, test: %d %d\n", size, b, t);
		printf("%6ld %15ld %9ld\n", size, b, t);
	}
	free(cache);
	return 0;
}
