#include <stdio.h>
#include <gmp.h>
#include <unistd.h>
#include <sys/file.h>


typedef unsigned long int len_t;


FILE *
get_file() {
    FILE *log_file;
    log_file = fopen("prime.log", "a+");
    flock(fileno(log_file), LOCK_EX);
    fseek(log_file, 0, SEEK_END);
    return log_file;
}

void
close_file(FILE *fp) {
    flock(fileno(fp), LOCK_UN);
    fclose(fp);
}




int
test_range(mpz_t num, mpz_t start, len_t len) {
    FILE *fp;
	mpz_t t, cur1, cur2;
    len_t i;

printf("len: %ld\n", len);

printf("In func\n");
	mpz_init(t);
printf("after t\n");
	mpz_init_set(cur1, start);  // cur1 = args->s
printf("After cur\n");
	mpz_init_set(cur2, cur1);	// cur2 = cur1
	mpz_add_ui(t, cur2, 2);		// t = cur2 + 2
	mpz_set(cur2, t);			// cur2 = t
printf("After init\n");


	for(i = 0; i < len; i++) {
// printf("iter: %d\n", i);
		mpz_mod(t, num, cur1);	// t = num % curl1
		if (mpz_sgn(t) == 0) {  // if t == 0
            fp = get_file();
            fprintf(fp, "Number is NOT PRIME\n");
			mpz_out_str(fp, 10, num);
			fprintf(fp, " %% ");
			mpz_out_str(fp, 10, cur1);
			fprintf(fp, " == 0\n");
            close_file(fp);
			return 0;
		}
		mpz_mod(t, num, cur2);	// t = num % curl2
		if (mpz_sgn(t) == 0) {	// if t == 0
            fp = get_file();
            fprintf(fp, "Number is NOT PRIME\n");
			mpz_out_str(fp, 10, num);
			fprintf(fp, " %% ");
			mpz_out_str(fp, 10, cur2);
			fprintf(fp, " == 0\n");
            close_file(fp);
			return 0;
		}
		
mpz_out_str(stdout, 10, cur1);
printf(", ");
		mpz_add_ui(t, cur1, 6);	// t = cur1 + 6
		mpz_set(cur1, t);		// cur1 = t
		mpz_add_ui(t, cur2, 6);	// t = cur2 + 6
		mpz_set(cur2, t);		// cur2 = t
	}
printf("\n");
	
    mpz_add_ui(t, start, len);  // t = start + len
    fp = get_file();
	fprintf(fp, "Finished range (");
    mpz_out_str(fp, 10, start);
    fprintf(fp, ", ");
    mpz_out_str(fp, 10, t);
    fprintf(fp, ")\nPrimality not detected\n");
    close_file(fp);
	return 1;
}

int
main() {

    
    mpz_t num;
    mpz_t start;
    len_t len;
    mpz_init_set_str(num, "12848751825131232133313313131318907819791", 10);
    mpz_init_set_str(start, "101", 10); // 5 + 6*16
    len = 100;
    // 100489 = 317^2

printf("After main init\n");
    

    if(test_range(num, start, len)) {
        printf("Number prime\n");
    } else {
        printf("Number not prime\n");
    }


	return 0;
}

