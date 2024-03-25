# mzpp19
**High performance palindromic prime number generator**

It finds and prints all palindrome prime between 0 and 2^64-1<br>
The output is in according b-files format (https://oeis.org/)<br>
In order to generate the prime numbers it uses an efficient implementation of the Sieve of Eratosthenes.

## About palindrome prime numbers
All palindromic prime numbers have odd lengths, except the prime number 11.<br>
Since 2^64-1 == 18446744073709551615 which is 20 digits long, we have that 64-bit palindromic prime numbers are at most 19 digits long.<br>
Furthermore, since no prime number (except 5) ends with 5, all palindromic prime numbers begin with 1 or 3 or 7 or 9.

## Palindrome wing prime number
Palindromic Wing Primes (PWP) are numbers that are primes, palindromic in base 10, and consisting of one central digit surrounded by two wings having an equal amount of identical digits and different from the central one.
The first 34 PWP are:
1 101
2 131
3 151
4 181
5 191
6 313
7 353
8 373
9 383
10 727
11 757
12 787
13 797
14 919
15 929
16 11311
17 11411
18 33533
19 77377
20 77477
21 77977
22 1114111
23 1117111
24 3331333
25 3337333
26 7772777
27 7774777
28 7778777
29 111181111
30 111191111
31 777767777
32 77777677777
33 99999199999
34 1111118111111

The program mzpp23 is a optimized and fast generator of PWP, derived from mzpp19

