#include <stdio.h>


int test(int total);
int isprime(int n);

/*
 * Very basic program to show that the prime validation
 * algorithm actually works. It takes in the 1000_primes
 * file as a redirect on the command line, then iterates
 * through all the integers up to the last number in the
 * 1000_primes file, ensuring it can detect primes.
 *     Usage: `./algo_test < 1000_primes`
 */



int
main() {
	printf("Passed %d tests\n", test(1000));

	return 0;
}


int
test(int total) {
	int i, n, p, correct, count;

	count = 0;
	correct = 0;
	scanf("%d ", &n);

	for(i = 0; count < total; i++) {
		p = isprime(i);
		if(p && (i == n)) {
			correct++;
			scanf("%d ", &n);
			count++;
			printf("%d GOOD: Prime\n", i);
		} else if(!p) {
			correct++;
			printf("%d GOOD: Not Prime\n", i);
		} else {
			printf("%d FAILED\n", i);
		}
	}
	return correct;
}

int
isprime(int n) {
    int i;

    if((n == 2) || (n == 3)) {
        return 1;
    }
    if((n <= 1) || (n % 2 == 0) || (n % 3 == 0)) {
        return 0;
    }

    for(i = 5; i*i <= n+1; i += 6) {
        if((n % i) == 0) {
            return 0;
        }
        if((n % (i + 2)) == 0) {
            return 0;
        }
    }
    return 1;
}
