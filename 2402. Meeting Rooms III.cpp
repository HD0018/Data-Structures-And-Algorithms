#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::priority_queue;
using std::pair;
using std::sort;
using std::greater;

using ll = long long;
using RoomTimePair = pair<ll, int>; // A pair of time to room mapping.

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        priority_queue<int, vector<int>, greater<int>> availableRooms; // Min-heap for idle rooms, sorted by room index.
        priority_queue<RoomTimePair, vector<RoomTimePair>, greater<RoomTimePair>> occupiedRooms; // Min-heap for busy rooms, sorted by ending time.
      
        // Initialize all rooms as available.
        for (int i = 0; i < n; ++i) {
            availableRooms.push(i);
        }
      
        vector<int> bookingCount(n, 0); // Count of bookings for each room.
      
        // Sort meetings based on their start time.
        sort(meetings.begin(), meetings.end());
      
        // Process each meeting.
        for (auto& meeting : meetings) {
            ll startTime = meeting[0];
            ll endTime = meeting[1];
          
            // Free up rooms that are no longer busy.
            while (!occupiedRooms.empty() && occupiedRooms.top().first <= startTime) {
                availableRooms.push(occupiedRooms.top().second);
                occupiedRooms.pop();
            }
          
            int roomIndex;
            if (!availableRooms.empty()) {
                // If there is an available room, assign the meeting to the room with the smallest index.
                roomIndex = availableRooms.top();
                availableRooms.pop();
                occupiedRooms.push({endTime, roomIndex});
            } else {
                // If no rooms are available, wait for the next room to become free.
                auto nextAvailableRoom = occupiedRooms.top();
                occupiedRooms.pop();
                roomIndex = nextAvailableRoom.second;
                occupiedRooms.push({nextAvailableRoom.first + (endTime - startTime), roomIndex});
            }
          
            // Increment the booking count for the selected room.
            bookingCount[roomIndex]++;
        }
      
        // Find the room with the maximum number of bookings.
        int mostBookedRoomIndex = 0;
        for (int i = 0; i < n; ++i) {
            if (bookingCount[mostBookedRoomIndex] < bookingCount[i]) {
                mostBookedRoomIndex = i;
            }
        }
        return mostBookedRoomIndex; // Return the index of the room that's been most booked.
    }
};
