#include <climits> // For INT_MIN and INT_MAX

class Solution {
public:
    int reverse(int x) {
        int reversedNumber = 0;
      
        // Loop until all digits are processed
        while (x != 0) {
            // Check if multiplying by 10 will cause overflow
            if (reversedNumber < INT_MIN / 10 || reversedNumber > INT_MAX / 10) {
                return 0;  // Return 0 if overflow would occur
            }
          
            // Pop the last digit from 'x' using modulus and add it to 'reversedNumber'
            reversedNumber = reversedNumber * 10 + x % 10;
          
            // Remove the last digit from 'x' by dividing it by 10
            x /= 10;
        }
      
        return reversedNumber;  // Return the reversed number
    }
};