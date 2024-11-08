#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BTree {
private:
    struct Node {
        vector<string> keys;  // File names (keys)
        vector<string> children;  // Locations (file locations)
        vector<Node*> child_nodes;  // Child nodes (pointers to child nodes)
        bool is_leaf;

        Node(bool leaf = true) : is_leaf(leaf) {}
    };

    Node* root;
    int t;  // Minimum degree (defines the range of keys per node)

    void insertNonFull(Node* node, const string& file_name, const string& location);
    void split(Node* parent, int i);
    Node* search(Node* node, const string& file_name);

public:
    BTree(int degree = 3);
    void insert(const string& file_name, const string& location);
    string search(const string& file_name);
};

BTree::BTree(int degree) : t(degree), root(new Node()) {}

void BTree::insert(const string& file_name, const string& location) {
    Node* root = this->root;
    if (root->keys.size() == (2 * t) - 1) {
        Node* new_node = new Node(false);
        new_node->child_nodes.push_back(root);
        split(new_node, 0);
        this->root = new_node;
    }
    insertNonFull(this->root, file_name, location);
}

void BTree::insertNonFull(Node* node, const string& file_name, const string& location) {
    int i = node->keys.size() - 1;
    if (node->is_leaf) {
        while (i >= 0 && file_name < node->keys[i]) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, file_name);
        node->children.insert(node->children.begin() + i + 1, location);
    } else {
        while (i >= 0 && file_name < node->keys[i]) {
            i--;
        }
        i++;
        Node* child = node->child_nodes[i];
        if (child->keys.size() == (2 * t) - 1) {
            split(node, i);
            if (file_name > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->child_nodes[i], file_name, location);
    }
}

void BTree::split(Node* parent, int i) {
    Node* node = parent->child_nodes[i];
    Node* new_node = new Node(node->is_leaf);
    int mid_index = node->keys.size() / 2;
    parent->keys.insert(parent->keys.begin() + i, node->keys[mid_index]);
    parent->child_nodes.insert(parent->child_nodes.begin() + i + 1, new_node);

    new_node->keys = vector<string>(node->keys.begin() + mid_index + 1, node->keys.end());
    node->keys.resize(mid_index);

    if (!node->is_leaf) {
        new_node->child_nodes = vector<Node*>(node->child_nodes.begin() + mid_index + 1, node->child_nodes.end());
        node->child_nodes.resize(mid_index + 1);
    }
}

BTree::Node* BTree::search(Node* node, const string& file_name) {
    int i = 0;
    while (i < node->keys.size() && file_name > node->keys[i]) {
        i++;
    }
    if (i < node->keys.size() && node->keys[i] == file_name) {
        return node;
    }
    if (node->is_leaf) {
        return nullptr;
    }
    return search(node->child_nodes[i], file_name
