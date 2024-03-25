/*******************************************************************
 * Matteo Zapparoli <zapparoli.matteo@gmail.com>
 * 2024-03-25
 * mzpp23.c
 * Find and print the palindome wing primes from 0 and 2^64 - 1
 * (from 3 to 19 digit length)
 * It prints the output according b-files format (https://oeis.org/)
 * A number is wing if it has one central digit surrounded by two 
 * wings having an equal amount of identical digits and different 
 * from the central one. Example: 101, 131, 1114111, 7778777 ...
 *******************************************************************/
 
#include <stdio.h>  // printf
#include <stdint.h> // uint64_t

// Function prototypes
uint32_t sqrt64(uint64_t num);
int isPalindromeWing(uint64_t n);
void sieveOfErastostheneses(void);
void findPalindromeWing64(void);
void checkPalindromeWing(uint64_t n);

// The sieve: every bit is a odd number, so the first bit is 1 the last bit 2^32-1
static uint8_t sieve[268435456];

// Counter of palindrome prime; the first 5 are pre-calculated
static uint32_t counter = 1; 

int main(char *argv[], int argc)
{
	sieveOfErastostheneses();
	findPalindromeWing64();
}

/**
 * uint32_t sqrt64(uint64_t num)
 * Return the square root of num; the result is tronced if there are decimals
 */
uint32_t sqrt64(uint64_t num) 
{
	uint32_t res = 0; // result
	uint32_t add = 1 << 31;

	do { // 32x test and shift right
		uint32_t temp = res + add;
		uint64_t quad = temp;
		quad *= temp;

		if(num >= quad)
			res = temp;

		add >>= 1; // shift right the 'additional' bit
	}
	while(add > 0);

	return res;
}

/**
 * int isPalindromeWing(uint64_t n)
 * Return !=0 if n is palindrome and wing, 
 *          0 otherwise
 */
int isPalindromeWing(uint64_t n)
{
	uint64_t reverse = 0;
	uint64_t original = n;
	uint64_t prec = n % 10;
	int d = 0;
	do {
		uint64_t r = n % 10;
		n /= 10;
		reverse = reverse * 10 + r;
		if(r != prec) {
			d++;
			prec = r;
			r = n % 10;
			n /= 10;
			reverse = reverse * 10 + r;
			if(r != prec) {
				d++;
			}
			else {
				return 0;
			}
		}
		prec = r;
	}
	while(n);
	
	return d == 2 && reverse == original;
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
void findPalindromeWing64(void)
{
	// Print the rest of 64 bit palindrome wing numbers
	// 2^64-1 == 18446744073709551615 : it is 20 digit length, so the biggest palindrome prime
	// 64 bit is at least length 19 digit

	uint64_t number = 100;
	for(int len = 3; len <= 19; len += 2) {
		// Calculate the smallest odd number length len
		uint64_t n = number + 1;

		// Find palindrome prime starting with 1
		uint64_t d = number << 1;
		do {
			checkPalindromeWing(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 3
		n += number + 2;
		d = number << 2;
		do {
			checkPalindromeWing(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 7
		n += 3 * number + 4;
		d = number << 3;
		do {
			checkPalindromeWing(n);
			n += 10;
		}
		while(n < d);

		// Find palindrome prime starting with 9
		n += number + 2;
		d = number * 10;
		do {
			checkPalindromeWing(n);
			n += 10;
		}
		while(n < d);

		number *= 100;
	}
}

void checkPalindromeWing(uint64_t n)
{
	if(isPalindromeWing(n)) {
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
					// Goal: n is palindrome, wing and prime!
					printf("%u %llu\n", counter++, n); // b-file format
					fflush(stdout);
					return;
				}
			}
		}
	}
}
