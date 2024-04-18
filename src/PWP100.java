import java.math.BigInteger;

/**
 * This program prints the first 100 palindrome wing prime.
 * A wing number consists of one central digit surrounded by two wings having an equal
 * amount of identical digits and different from the central one
 * The numbers up to the 37th are certainly primes, the subsequent ones are probable primes
 * @author Matteo Zapparoli
 * 2024-3-26
 */
public class PWP100 {
	
	static final int MAX_LENGTH = 169; // Increase to print more PWP

	public static final void main(String[] args) {
		int counter = 1;
		char[] digits = {'1', '3', '7', '9'};
		for(int len = 1; len < MAX_LENGTH; len++) {
			for(char c : digits) {
				
				String num = "";
				for(int i = 0; i < len; i++)
					num += c;
				
				for(char pivot = '0'; pivot <= '9'; pivot++) {
					if(pivot != c) {
						String palindromeWing = num + pivot + num;
						BigInteger bi = new BigInteger(palindromeWing);
						if(bi.isProbablePrime(Integer.MAX_VALUE)) {
							System.out.println(counter++ + " " + palindromeWing);
						}
					}
				}
			}
 		}
	}
	
}
