class UserHashTable:
    def __init__(self, size=100):
        # Initialize hash table with a given size
        self.size = size
        self.table = [[] for _ in range(size)]  # Create a list of empty lists for separate chaining

    def _hash(self, username: str) -> int:
        # Simple hash function: sum of ASCII values of the characters mod table size
        return sum(ord(c) for c in username) % self.size

    def add_user(self, username: str, profile_data: dict):
        # Hash the username to find the index in the table
        index = self._hash(username)
        
        # Check if the username already exists; if so, update the profile
        for entry in self.table[index]:
            if entry[0] == username:
                entry[1] = profile_data
                return
        
        # If the username doesn't exist, add a new entry
        self.table[index].append((username, profile_data))

    def get_user(self, username: str) -> dict:
        # Hash the username to find the index
        index = self._hash(username)
        
        # Look for the username in the corresponding chain (linked list)
        for entry in self.table[index]:
            if entry[0] == username:
                return entry[1]  # Return the profile data
        
        # If not found, return an empty dictionary (or could raise an exception)
        return {}

# Example Usage
user_table = UserHashTable()
user_table.add_user("alice", {"age": 25, "location": "NYC"})
user_table.add_user("bob", {"age": 30, "location": "LA"})

print(user_table.get_user("alice"))  # Output: {'age': 25, 'location': 'NYC'}
print(user_table.get_user("bob"))  # Output: {'age': 30, 'location': 'LA'}
print(user_table.get_user("charlie"))  # Output: {}
