#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        // Map to hold the events on each day
        unordered_map<int, vector<int>> eventsByStartDay;
        // Initialize the minimum and maximum days across all events
        int minDay = INT_MAX;
        int maxDay = 0;

        // Iterate through all the events
        for (auto& event : events) {
            int startDay = event[0];
            int endDay = event[1];
            // Map the end day of each event to its start day
            eventsByStartDay[startDay].push_back(endDay);
            // Update the minimum and maximum days
            minDay = min(minDay, startDay);
            maxDay = max(maxDay, endDay);
        }

        // Min-heap (priority queue) to keep track of the events' end days, prioritised by earliest end day
        priority_queue<int, vector<int>, greater<int>> minHeap;
        // Counter to hold the maximum number of events we can attend
        int maxEventsAttended = 0;

        // Iterate through each day from the earliest start day to the latest end day
        for (int day = minDay; day <= maxDay; ++day) {
            // Remove events that have already ended
            while (!minHeap.empty() && minHeap.top() < day) {
                minHeap.pop();
            }
            // Add all events starting on the current day to the min-heap
            for (int endDay : eventsByStartDay[day]) {
                minHeap.push(endDay);
            }
            // If we can attend an event, remove it from the heap and increase the count
            if (!minHeap.empty()) {
                maxEventsAttended++;
                minHeap.pop();
            }
        }
      
        // Return the maximum number of events that can be attended
        return maxEventsAttended;
    }
};