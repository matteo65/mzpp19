# mzpp19
**High performance palindromic prime number generator**

It finds and prints all palindrome prime between 0 and 2^64-1<br>
The output is in according b-files format (https://oeis.org/)<br>
In order to generate the prime numbers it uses an efficient implementation of the Sieve of Eratosthenes.

## About palindrome prime numbers
All palindromic prime numbers have odd lengths, except the prime number 11.<br>
Since 2^64-1 == 18446744073709551615 which is 20 digits long, we have that 64-bit palindromic prime numbers are at most 19 digits long.<br>
Furthermore, since no prime number (except 5) ends with 5, all palindromic prime numbers begin with 1 or 3 or 7 or 9.
