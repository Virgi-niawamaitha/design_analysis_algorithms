#include <iostream>
#include <string>

using namespace std;

class BookBST {
private:
    struct Node {
        string isbn;
        unordered_map<string, string> book_data;  // Book information (title, author, etc.)
        Node* left;
        Node* right;

        Node(string isbn, unordered_map<string, string> book_data)
            : isbn(isbn), book_data(book_data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, string isbn, unordered_map<string, string> book_data) {
        if (!node) return new Node(isbn, book_data);

        if (isbn < node->isbn) {
            node->left = insert(node->left, isbn, book_data);
        } else if (isbn > node->isbn) {
            node->right = insert(node->right, isbn, book_data);
        } else {
            // ISBN already exists, update book data
            node->book_data = book_data;
        }

        return node;
    }

    Node* search(Node* node, string isbn) {
        if (!node || node->isbn == isbn) return node;
        if (isbn < node->isbn) return search(node->left, isbn);
        return search(node->right, isbn);
    }

    Node* deleteNode(Node* node, string isbn) {
        if (!node) return node;

        if (isbn < node->isbn) {
            node->left = deleteNode(node->left, isbn);
        } else if (isbn > node->isbn) {
            node->right = deleteNode(node->right, isbn);
        } else {
            // Node with the ISBN found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);
            node->isbn = temp->isbn;
            node->book_data = temp->book_data;
            node->right = deleteNode(node->right, temp->isbn);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

public:
    BookBST() : root(nullptr) {}

    void insert(string isbn, unordered_map<string, string> book_data) {
        root = insert(root, isbn, book_data);
    }

    unordered_map<string, string> search(string isbn) {
        Node* result = search(root, isbn);
        if (result) return result->book_data;
        return {};  // Return empty map if book not found
    }

    void deleteBook(string isbn) {
        root = deleteNode(root, isbn);
    }
};

int main() {
    BookBST library;

    unordered_map<string, string> bookA = {{"title", "Book A"}, {"author", "Author A"}};
    unordered_map<string, string> bookB = {{"title", "Book B"}, {"author", "Author B"}};
    unordered_map<string, string> bookC = {{"title", "Book C"}, {"author", "Author C"}};

    // Insert books
    library.insert("978-3-16-148410-0", bookA);
    library.insert("978-1-4028-9462-6", bookB);
    library.insert("978-0-596-52068-7", bookC);

    // Search for a book
    auto
