class BST:
    class Node:
        def __init__(self, isbn, book_data):
            self.isbn = isbn
            self.book_data = book_data
            self.left = None
            self.right = None

    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        # Insert a new node with the given ISBN and book data
        if not self.root:
            self.root = self.Node(isbn, book_data)
        else:
            self._insert(self.root, isbn, book_data)

    def _insert(self, node, isbn, book_data):
        if isbn < node.isbn:
            if node.left is None:
                node.left = self.Node(isbn, book_data)
            else:
                self._insert(node.left, isbn, book_data)
        elif isbn > node.isbn:
            if node.right is None:
                node.right = self.Node(isbn, book_data)
            else:
                self._insert(node.right, isbn, book_data)
        else:
            # ISBN already exists, update the book data (optional)
            node.book_data = book_data

    def search(self, isbn):
        # Search for a book by ISBN
        return self._search(self.root, isbn)

    def _search(self, node, isbn):
        if node is None:
            return None  # Book not found
        if isbn == node.isbn:
            return node.book_data  # Book found
        elif isbn < node.isbn:
            return self._search(node.left, isbn)  # Search in left subtree
        else:
            return self._search(node.right, isbn)  # Search in right subtree

    def delete(self, isbn):
        # Delete a book by ISBN
        self.root = self._delete(self.root, isbn)

    def _delete(self, node, isbn):
        if node is None:
            return node  # Book not found
        
        if isbn < node.isbn:
            node.left = self._delete(node.left, isbn)  # Search in left subtree
        elif isbn > node.isbn:
            node.right = self._delete(node.right, isbn)  # Search in right subtree
        else:
            # Node to be deleted found
            if node.left is None:
                return node.right  # No left child, return right subtree
            elif node.right is None:
                return node.left  # No right child, return left subtree
            else:
                # Node with two children: Get the inorder successor (smallest in the right subtree)
                node.isbn, node.book_data = self._min_value_node(node.right).isbn, self._min_value_node(node.right).book_data
                node.right = self._delete(node.right, node.isbn)  # Delete the successor

        return node

    def _min_value_node(self, node):
        # Find the node with the smallest ISBN (leftmost node)
        current = node
        while current.left:
            current = current.left
        return current

# Example Usage
library_bst = BST()

# Insert books
library_bst.insert("978-3-16-148410-0", {"title": "Book A", "author": "Author A"})
library_bst.insert("978-1-4028-9462-6", {"title": "Book B", "author": "Author B"})
library_bst.insert("978-0-596-52068-7", {"title": "Book C", "author": "Author C"})

# Search for a book by ISBN
book_data = library_bst.search("978-1-4028-9462-6")
print(f"Book found: {book_data}")

# Delete a book by ISBN
library_bst.delete("978-1-4028-9462-6")

# Try searching for the deleted book
book_data = library_bst.search("978-1-4028-9462-6")
print(f"Book found after deletion: {book_data}")
