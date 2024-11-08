#include <iostream>
#include <vector>
using namespace std;

class DisjointSetUnion {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSetUnion(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Initially, each element is its own parent
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            // Path compression: make the node directly point to the root
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Union by rank: attach the smaller tree to the larger one
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;  // Increase rank if both trees have the same rank
            }
        }
    }
};

// Example Usage
int main() {
    DisjointSetUnion dsu(5);

    // Union some sets
    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);

    // Find the root of a set
    cout << "Root of set containing 0: " << dsu.find(0) << endl;  // Output: Root of set containing 0
    cout << "Root of set containing 3: " << dsu.find(3) << endl;  // Output: Root of set containing 3

    // Check if two elements are in the same set (connected in the same network)
    cout << "Are 0 and 2 connected? " << (dsu.find(0) == dsu.find(2) ? "Yes" : "No") << endl;  // Output: Yes
    cout << "Are 0 and 3 connected? " << (dsu.find(0) == dsu.find(3) ? "Yes" : "No") << endl;  // Output: No

    return 0;
}
