/*******************************************************************
 * Matteo Zapparoli <zapparoli.matteo@gmail.com>
 * 2023-11-02
 * mzpp19.c
 * Find and print the palindome primes from 0 and 2^64 - 1
 * (from 1 to 19 digit length)
 * It prints the output according b-files format (https://oeis.org/)
 *******************************************************************/
 
#include <stdio.h>  // printf
#include <stdint.h> // uint64_t

// Function prototypes
uint32_t sqrt64(uint64_t num);
int isPalindrome(uint64_t n);
void sieveOfErastostheneses(void);
void findPalindrome64(void);
void checkPalindrome(int64_t n);

// The sieve: every bit is a odd number, so the first bit is 1 the last bit 2^32-1
static uint8_t sieve[268435456];

// Counter of palindrome prime; the first 5 are pre-calculated
static uint32_t counter = 6; 

int main(char *argv[], int argc)
{
	sieveOfErastostheneses();
	findPalindrome64();
}

/**
 * uint32_t sqrt64(uint64_t num)
 * Return the square root of num; the result is tronced if there are decimals
 */
uint32_t sqrt64(uint64_t num) 
{
	uint32_t res = 0; // result
	uint32_t add = 1 << 31;

	while(add > 0) { // 32x test and shift right
		uint32_t temp = res + add;
		uint64_t quad = temp;
		quad *= temp;

		if(num >= quad)
			res = temp;

		add >>= 1; // shift right the 'additional' bit
	}
	return res;
}

/**
 * int isPalindrome(uint64_t n)
 * Return !=0 if n is palindrome, 
 *          0 if n is not palindrome
 */
int isPalindrome(uint64_t n)
{
	uint64_t reverse = 0;
	uint64_t original = n;
	while(n) {
		uint64_t r = n % 10;
		reverse = reverse * 10 + r;
		n /= 10;
	}
	return reverse == original;
}

/**
 * Find all primes using the sieve Of Erastostheneses algorithm
 * It writes sieve[] global variable bit=0 is prime, bit=1 is not prime
 */
void sieveOfErastostheneses(void)
{
	sieve[0] = 0x01; // 1 is not prime

	// The condition shuld be (i <= 32768) but (i <=32760) product same result
	for(uint32_t i = 1; i <= 32760; i++) {
		uint32_t index = (i >> 3);
		uint32_t bitIndex = (i & 0x07);

		if(((sieve[index] >> bitIndex) & 0x01) == 0) {
			uint32_t prime = 1 + (i << 1);
			// Condition (j > i) prevent overflow
			for(uint32_t j = i + prime; j > i && j < 2147483648U; j += prime) {
				index = (j >> 3);
				bitIndex = (j & 0x07);
				sieve[index] |= (0x01 << bitIndex);
			}
		}
	}
}

/**
 * Find and print the palindrome prime 64 bit.
 * It uses sieve[] static variable  
 */
void findPalindrome64(void)
{
	// Print the first 5 palindrome numbers
	printf("1 2\n");
	printf("2 3\n");
	printf("3 5\n");
	printf("4 7\n");
	printf("5 11\n");

	// Print the rest of 64 bit palindrome numbers
	// 11 is the only palindrome prime length even, the others have odd length.
	// 2^64-1 == 18446744073709551615 : it is 20 digit length, so the biggest palindrome prime
	// 64 bit is at least length 19 digit

	int64_t number = 100;
	for(int len = 3; len <= 19; len += 2) {
		// Calculate the smallest odd number length len
		int64_t n = number + 1;

		// Find palindrome prime starting with 1
		int64_t d = number << 1;
		do {
			checkPalindrome(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 3
		n += 2;
		d = number << 2;
		do {
			checkPalindrome(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 7
		n += 4;
		d = number << 3;
		do {
			checkPalindrome(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 9
		n += 2;
		d = number * 10;
		do {
			checkPalindrome(n);
			n += 10;
		}
		while(n < d);

		number *= 100;
	}
}

void checkPalindrome(int64_t n)
{
	if(isPalindrome(n)) {
		// Check if n is also prime
		uint32_t sqrt = sqrt64(n);

		for(uint32_t i = 1; i < 2147483648U; i++) {
			if(((sieve[i >> 3] >> (i & 0x07)) & 0x01) == 0) {
				uint32_t p = 1 + (i << 1);
				if(n % p == 0) {
					// n is divisible by a prime
					return;
				}
				if(p > sqrt) {
					// Goal: n is palindrome and prime!
					printf("%u %llu\n", counter++, n); // b-file format
					fflush(stdout);
					return;
				}
			}
		}
	}
}

