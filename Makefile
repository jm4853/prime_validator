# Environment variable for root directory of git repo
PRIME_ROOT_DIR=$(PRIME_VALIDATOR_ROOT_DIR)
# You'll have to configure the vars below based on your set
# up for now. This should be handled by python later
GMP_DIR=$(PRIME_ROOT_DIR)/gmp-6.3.0
GMP_LIB_DIR=$(GMP_DIR)/.libs

test: algo_tester.c
	cc algo_tester.c -o algo_test.out

all: prime_search.c
	cc prime_search.c -o prime_search.out -I$(GMP_DIR) -L$(GMP_LIB_DIR) -lgmp

clean:
	rm *.out
