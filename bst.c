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
#define CHECK_UWRAPADD(a, b, fn, line) \
do{\
	if (a < b) {\
	             die("Unsigned integer wrap detected (addition) at: %s:%d\n", fn, line);\
	}\
} while (0);
#define CHECK_UWRAPMUL(x, a, b, fn, line) \
do {\
        if (a != 0 && x / a != b) {\
                     die("Unsigned integer wrap detected (multiplication) at: %s:%d\n", fn, line);\
        }\
} while (0);

typedef unsigned long long BigInt;

void cache_init(BigInt size);
BigInt benchmark(BigInt size);
BigInt test(BigInt size);
void die(char const *fmt, ...);
BigInt parseIntULL(char const *s);

BigInt *cache = NULL;

void cache_init(BigInt size)
{
	cache = calloc(size, sizeof *cache);       /* calloc -> zero initialized */
	if (!cache)
		die("Out of memory\n");
}
BigInt benchmark(BigInt size)
{
	if (size <= 1)
		return 1;
	if (cache[size])
		return cache[size];
	BigInt total = 0;
	BigInt last = 0;
	for (BigInt i = 1; i <= size; i++) {
		BigInt L = benchmark(i - 1);
		BigInt R = benchmark(size - i);
		last = total;
		BigInt tmp = L * R;
		CHECK_UWRAPMUL(tmp, L, R, __FUNCTION__, __LINE__);
		total = last + tmp;
		CHECK_UWRAPADD(total, last, __FUNCTION__, __LINE__);
	}
	cache[size] = total;
	return total;
}
BigInt test(BigInt size)
{
	if (size <= 1)
		return 1;
	if (cache[size])
		return cache[size];
	BigInt total = 0;
	BigInt last = 0;
	BigInt top = size;
	BigInt m = size / 2;
	while (top-- > m) {
		BigInt R = test(top);
		BigInt L = test(size - top - 1);
		last = total;
		BigInt tmp = L * R;
		CHECK_UWRAPMUL(tmp, L, R, __FUNCTION__, __LINE__);
		total = last + tmp;
		CHECK_UWRAPADD(total, last, __FUNCTION__, __LINE__);
	}
	BigInt ret;
	if (size % 2u == 0u) {
		ret = total * 2u;
		CHECK_UWRAPMUL(ret, total, 2u, __FUNCTION__, __LINE__);
	} else {
		BigInt L2 = last * 2u;
		CHECK_UWRAPMUL(L2, last, 2u, __FUNCTION__, __LINE__);
		ret = (L2) + (total - last);
		CHECK_UWRAPADD(ret, L2, __FUNCTION__, __LINE__);
	}
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
BigInt parseBigInt(char const *s)
{
	char *fail;
	BigInt val = strtoull(s, &fail, 10);
	if (errno == ERANGE && (val == ULLONG_MAX))
		die("Integer too large\n");
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
	BigInt cachesize = 0;
	int argc_ = argc - 1;
	char **argv_ = argv + 1;
	for ( ;  argc_; argc_--, argv_++) {
	             char *s = *argv_;
	             cachesize = MAX(cachesize, parseBigInt(s));
	}
	cache_init(cachesize + 1);
	printf("%4s%5c%20s%c%20s%c%20s\n", "N", '|', "benchmark(N)", '|', "test(N)", '|', "ULLONG_MAX");
	while (--argc) {
		char *s = *++argv;
		BigInt size = parseBigInt(s);
		BigInt b = benchmark(size);
		BigInt t = test(size);
		if (b != t)
			die("Test failed for size = %d. Benchmark, test: %d %d\n", size, b, t);
		printf("%8llu %20llu %20llu %20llu\n", size, b, t, ULLONG_MAX);
	}
	free(cache);
	return 0;
}
