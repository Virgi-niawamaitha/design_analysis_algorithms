class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))  # Initially, each element is its own parent
        self.rank = [0] * n  # Initially, the rank (height) of each tree is 0

    def find(self, x):
        if self.parent[x] != x:
            # Path compression: point the current node directly to the root
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x != root_y:
            # Union by rank: attach the tree with smaller rank under the larger one
            if self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            elif self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1  # Increase the rank if both have the same rank

# Example Usage
ds = DisjointSet(5)

# Union some sets
ds.union(0, 1)
ds.union(1, 2)
ds.union(3, 4)

# Find the root of a set
print(ds.find(0))  # Output: Root of the set containing element 0
print(ds.find(3))  # Output: Root of the set containing element 3

# Check if two elements are in the same set (connected in the same network)
print(ds.find(0) == ds.find(2))  # Output: True
print(ds.find(0) == ds.find(3))  # Output: False
