#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<vector<string>> allPaths; // List of paths from beginWord to endWord
    unordered_map<string, unordered_set<string>> predecessorsMap; // Map to track the predecessors of each word in the shortest paths

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        allPaths.clear();
        unordered_set<string> wordSet(wordList.begin(), wordList.end()); // Convert word list to a set for efficient lookups
        if (wordSet.find(endWord) == wordSet.end()) {
            return allPaths; // If endWord is not in the word set, return empty list
        }
      
        wordSet.erase(beginWord); // Remove beginWord from the set to prevent cycles
        unordered_map<string, int> distanceMap; // Map to track the shortest path distances for words
        distanceMap[beginWord] = 0; // Distance from beginWord to itself is 0
        predecessorsMap.clear(); // Initialize the predecessors map
        queue<string> queue; // Queue for BFS
        queue.push(beginWord);
        bool isEndWordFound = false; // Flag to check if endWord is found
        int steps = 0; // Step counter for BFS

        while (!queue.empty() && !isEndWordFound) {
            ++steps;
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; ++i) {
                string currentWord = queue.front();
                queue.pop();
                string originalWord = currentWord;

                for (int j = 0; j < currentWord.size(); ++j) {
                    char originalChar = currentWord[j];
                    for (char c = 'a'; c <= 'z'; ++c) { // Try all possible one-letter mutations
                        currentWord[j] = c;
                        if (distanceMap.find(currentWord) != distanceMap.end() && distanceMap[currentWord] == steps) {
                            predecessorsMap[currentWord].insert(originalWord);
                        }
                        if (wordSet.find(currentWord) == wordSet.end()) { 
                            continue; // If the new word isn't in the set, skip it
                        }
                        // Update distance map and predecessors map for new words
                        predecessorsMap[currentWord].insert(originalWord);
                        wordSet.erase(currentWord); // Remove new word to prevent revisiting
                        queue.push(currentWord);
                        distanceMap[currentWord] = steps;

                        if (endWord == currentWord) {
                            isEndWordFound = true; // Found the endWord; will finish after this level
                        }
                    }
                    currentWord[j] = originalChar; // Restore original character before next iteration
                }
            }
        }

        if (isEndWordFound) { // If the end word has been reached
            deque<string> path; // Path stack for reconstructing paths
            path.push_back(endWord);
            backtrackPath(path, beginWord, endWord); // Perform DFS to build all shortest paths
        }

        return allPaths; // Return the list of all shortest paths
    }

private:
    void backtrackPath(deque<string> path, const string& beginWord, const string& currentWord) {
        if (currentWord == beginWord) { // If the beginning of the path is reached, add it to allPaths
            allPaths.push_back(vector<string>(path.begin(), path.end()));
            return;
        }
      
        // Recursively go through all predecessors of the current word, adding them to the path
        for (const auto& predecessor : predecessorsMap[currentWord]) {
            path.push_front(predecessor); // Push the predecessor onto the path
            backtrackPath(path, beginWord, predecessor); // Continue backtracking
            path.pop_front(); // Remove the predecessor to backtrack
        }
    }
};