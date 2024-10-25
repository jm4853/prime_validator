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


void
handle_threads(mpz_t num, mpz_t start, len_t len, unsigned int threads) {
printf("In handle threads\n");
    pthread_t tids[threads];
    func_arg_t a;
    mpz_t t;
    unsigned int i;
    unsigned int seg = len / threads;

    mpz_init(t);
printf("num: ");
mpz_out_str(stdout, 10, num);
printf("\n");

    for(i = 0; i < threads; i++) {
printf("it: %d\n", i);
        pthread_mutex_lock(&arg_lock);
        a.l = seg;
        a.n = (mpz_t *)(&num);
        a.s = (mpz_t *)(&start);
printf("l: %d\n", seg);
printf("n: ");
mpz_out_str(stdout, 10, (*((mpz_t *)(a.n))));
printf("\ns: ");
mpz_out_str(stdout, 10, *(a.s));
printf("\n");
        pthread_mutex_unlock(&arg_lock);

        if(pthread_create(&(tids[i]), NULL, test_range, (void *)(&a)) != 0) {
            printf("Could not create thread\n");
            return;
        }
printf("Thread created\n");
        pthread_mutex_lock(&arg_lock);
		mpz_add_ui(t, start, seg);
		mpz_set(start, t);
        pthread_mutex_unlock(&arg_lock);
    }
printf("Collecting threads\n");
    for(i = 0; i < threads; i++) {
        pthread_join(tids[i], NULL);
    }

}

handle_threads(mpz_t num, mpz_t start, len_t len, unsigned int threads) {


int
test_range(mpz_t num, mpz_t start, len_t len) {
    FILE *fp;
	mpz_t t, cur1, cur2;

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
            finished = 1;
			return NULL;
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
            finished = 1;
			return NULL;
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
	return NULL;
}

int
main() {
	// printf("Passed %d tests\n", test(1000));

    
	// pthread_t tid;
    // func_arg_t args;
    // args.l = 100;
    // printf("args addr: %p\n", &args);
    // printf("l addr:    %p\n", &(args.l));
    // printf("Thing going\n");
    // Starts must be in the form 6n + 5
    // mpz_init_set_str(args.s, "5", 10);
    mpz_t num;
    mpz_t start;
    mpz_init_set_str(num, "12848751825131232133313313131318907819791", 10);
    mpz_init_set_str(start, "101", 10); // 5 + 6*16
    // 100489 = 317^2
printf("Before handle_threads\n");
    handle_threads(num, start, 100, 1);
printf("After handle_threads\n");

    // printf("Init-ed\n");
    // if(pthread_create(&tid, NULL, test_range, (void *)(&args)) != 0) {
    //     printf("Could not create thread\n");
    //     return 1;
    // }
    // printf("Waiting\n");
    // pthread_join(tid, NULL);
    // printf("Thread Exited\n");

	



	return 0;
}

