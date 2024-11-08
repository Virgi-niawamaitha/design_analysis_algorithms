#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

using namespace std;

class UserHashTable {
private:
    // Hash table using separate chaining with linked lists
    vector<list<pair<string, unordered_map<string, string>>>> table;
    int size;

    // Hash function to convert username to an index
    int hash(const string& username) {
        int hashValue = 0;
        for (char c : username) {
            hashValue += c;
        }
        return hashValue % size;
    }

public:
    UserHashTable(int size = 100) : size(size) {
        table.resize(size);  // Initialize the table with empty lists
    }

    // Add or update user profile
    void addUser(const string& username, const unordered_map<string, string>& profileData) {
        int index = hash(username);

        // Search for the username in the list at the calculated index
        for (auto& entry : table[index]) {
            if (entry.first == username) {
                // Username found, update the profile data
                entry.second = profileData;
                return;
            }
        }

        // If username not found, add a new entry
        table[index].push_back(make_pair(username, profileData));
    }

    // Get user profile data by username
    unordered_map<string, string> getUser(const string& username) {
        int index = hash(username);

        // Search for the username in the list at the calculated index
        for (auto& entry : table[index]) {
            if (entry.first == username) {
                return entry.second;  // Return the profile data
            }
        }

        // If not found, return an empty map
        return unordered_map<string, string>();
    }
};

// Example Usage
int main() {
    UserHashTable userTable;

    unordered_map<string, string> aliceProfile = {{"age", "25"}, {"location", "NYC"}};
    unordered_map<string, string> bobProfile = {{"age", "30"}, {"location", "LA"}};

    userTable.addUser("alice", aliceProfile);
    userTable.addUser("bob", bobProfile);

    unordered_map<string, string> alice = userTable.getUser("alice");
    unordered_map<string, string> bob = userTable.getUser("bob");

    cout << "Alice's profile: ";
    for (const auto& pair : alice) {
        cout << pair.first << ": " << pair.second << ", ";
    }
    cout << endl;

    cout << "Bob's profile: ";
    for (const auto& pair : bob) {
        cout << pair.first << ": " << pair.second << ", ";
    }
    cout << endl;

    return 0;
}
