# mzpp19
**High performance palindromic primes number generator**

It finds and prints all palindrome prime between 0 and 2^64-1<br>
The output is in according b-files format (https://oeis.org/)<br>
In order to generate the prime numbers it uses an efficient implementation of the Sieve of Eratosthenes.

## About palindrome primes numbers
All palindromic prime numbers have odd lengths, except the prime number 11.<br>
Since 2^64-1 == 18446744073709551615 which is 20 digits long, we have that 64-bit palindromic prime numbers are at most 19 digits long.<br>
Furthermore, since no prime number (except 5) ends with 5, all palindromic prime numbers begin with 1 or 3 or 7 or 9.

## Palindrome wing primes number
Palindromic Wing Primes (PWP) are numbers that are primes, palindromic in base 10, and consisting of one central digit surrounded by two wings having an equal amount of identical digits and different from the central one.
The first 34 PWP are:
101
131
151
181
191
313
353
373
383
727
757
787
797
919
929
11311
11411
33533
77377
77477
77977
1114111
1117111
3331333
3337333
7772777
7774777
7778777
111181111
111191111
777767777
77777677777
99999199999
1111118111111

The program mzpp23 is a optimized and fast generator of PWP, derived from mzpp19
