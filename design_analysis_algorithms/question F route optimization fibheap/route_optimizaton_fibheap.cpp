#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

class FibHeap {
private:
    struct Node {
        int key;
        int degree;
        Node* parent;
        Node* child;
        bool mark;
        Node* next;
        Node* prev;

        Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), mark(false), next(nullptr), prev(nullptr) {}
    };

    Node* minNode;
    int nodeCount;

public:
    FibHeap() : minNode(nullptr), nodeCount(0) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        if (!minNode) {
            minNode = newNode;
            newNode->next = newNode->prev = newNode;
        } else {
            link(minNode, newNode);
            if (key < minNode->key) {
                minNode = newNode;
            }
        }
        nodeCount++;
    }

    void link(Node* minNode, Node* newNode) {
        newNode->next = minNode;
        newNode->prev = minNode->prev;
        minNode->prev->next = newNode;
        minNode->prev = newNode;
    }

    int extractMin() {
        Node* minNode = this->minNode;
        if (minNode) {
            if (minNode->child) {
                Node* child = minNode->child;
                while (child) {
                    Node* nextChild = child->next;
                    child->prev = minNode->prev;
                    minNode->prev->next = child;
                    child->prev->next = child;
                    child = nextChild;
                }
            }
            minNode->prev->next = minNode->next;
            minNode->next->prev = minNode->prev;
            if (minNode == minNode->next) {
                this->minNode = nullptr;
            } else {
                this->minNode = minNode->next;
                consolidate();
            }
            nodeCount--;
            int minKey = minNode->key;
            delete minNode;
            return minKey;
        }
        return INT_MAX;
    }

    void consolidate() {
        int maxDegree = log2(nodeCount);
        Node* arr[maxDegree + 1] = {nullptr};

        Node* current = minNode;
        while (current) {
            int degree = current->degree;
            while (arr[degree]) {
                Node* other = arr[degree];
                if (current->key > other->key) {
                    swap(current, other);
                }
                link(minNode, other);
                arr[degree] = nullptr;
                degree++;
            }
            arr[degree] = current;
            current = current->next;
        }

        minNode = nullptr;
        for (int i = 0; i <= maxDegree; i++) {
            if (arr[i]) {
                if (!minNode || arr[i]->key < minNode->key) {
                    minNode = arr[i];
                }
            }
        }
    }

    void decreaseKey(Node* node, int newKey) {
        if (newKey > node->key) return;  // Error: new key is greater than current key
        node->key = newKey;
        Node* parent = node->parent;
        if (parent && node->key < parent->key) {
            cut(node, parent);
            cascadingCut(parent);
        }
    }

    void cut(Node
