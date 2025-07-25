#include <vector>
#include <unordered_set>
#include <algorithm> // For std::max_element

class Solution {
public:
    // Method to find the maximum sum of unique positive numbers in the vector
    int maxSum(std::vector<int>& nums) {
        // Find the maximum value in nums. Use std::max_element instead of non-standard features.
        int maxVal = *std::max_element(nums.begin(), nums.end());
      
        // If all numbers are non-positive, return the maximum value (which would be the least negative or zero).
        if (maxVal <= 0) {
            return maxVal;
        }

        // Create an unordered set to track unique numbers we've added to the sum
        std::unordered_set<int> uniqueNumbers;
        int totalSum = 0; // Variable to store the sum of unique positive numbers

        // Iterate through each number in the vector
        for (int num : nums) {
            // Skip negative numbers and numbers already added to the sum
            if (num < 0 || uniqueNumbers.count(num) > 0) {
                continue;
            }

            // Add the unique positive number to the sum
            totalSum += num;
            // Insert the number into the set to ensure it's only added once
            uniqueNumbers.insert(num);
        }

        return totalSum; // Return the computed sum
    }
};