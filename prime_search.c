#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <unistd.h>
#include <sys/file.h>


typedef unsigned long int len_t;


int
test_range(mpz_t num, mpz_t start, len_t len) {
    FILE *fp;
	mpz_t t, cur1, cur2;
    len_t i;


	mpz_init(t);
	mpz_init_set(cur1, start);  // cur1 = args->s
	mpz_init_set(cur2, cur1);	// cur2 = cur1
	mpz_add_ui(t, cur2, 2);		// t = cur2 + 2
	mpz_set(cur2, t);			// cur2 = t


	for(i = 0; i < len; i++) {
		mpz_mod(t, num, cur1);	// t = num % curl1
		if (mpz_sgn(t) == 0) {  // if t == 0
            // printf("Number is NOT PRIME\n");
			mpz_out_str(stdout, 10, num);
			printf(" %% ");
			mpz_out_str(stdout, 10, cur1);
			printf(" == 0\n");
			return 1;
		}
		mpz_mod(t, num, cur2);	// t = num % curl2
		if (mpz_sgn(t) == 0) {	// if t == 0
            // printf("Number is NOT PRIME\n");
			mpz_out_str(stdout, 10, num);
			printf(" %% ");
			mpz_out_str(stdout, 10, cur2);
			printf(" == 0\n");
			return 1;
		}
		
		mpz_add_ui(t, cur1, 6);	// t = cur1 + 6
		mpz_set(cur1, t);		// cur1 = t
		mpz_add_ui(t, cur2, 6);	// t = cur2 + 6
		mpz_set(cur2, t);		// cur2 = t
	}
	
    // mpz_add_ui(t, start, len);  // t = start + len
	// printf("Finished range (");
    // mpz_out_str(stdout, 10, start);
    // printf(", ");
    // mpz_out_str(stdout, 10, t);
    // printf(")\nPrimality not detected\n");
	return 0;
}

int
main(int argc, char *argv[]) {
    mpz_t num;
    mpz_t start;
    len_t len;


    if(argc != 4) {
        fprintf(stderr, "Usage: ./prime_search [num to check] [start] [length]\n");
        return 1;
    }
    // 12848751825131232133313313131318907819791

    mpz_init_set_str(num, argv[1], 10);
    mpz_init_set_str(start, argv[2], 10); // 5 + 6*16
    len = atoi(argv[3]);
    // 100489 = 317^2

// printf("Got:\n");
// printf("  len: %ld\n", len);
// printf("  num: ");
// mpz_out_str(stdout, 10, num);
// printf("\n  start: ");
// mpz_out_str(stdout, 10, start);
// printf("\n\n");
    

    // if(test_range(num, start, len)) {
    //     printf("Inconclusive\n");
    // } else {
    //     printf("Number not prime\n");
    // }


    return test_range(num, start, len);
}

