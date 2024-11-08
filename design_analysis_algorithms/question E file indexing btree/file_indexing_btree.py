class BTree:
    class Node:
        def __init__(self, is_leaf=True):
            self.is_leaf = is_leaf
            self.keys = []  # List of file names (keys)
            self.children = []  # List of children nodes

    def __init__(self, t=3):  # Default B-tree of minimum degree 3
        self.root = self.Node()
        self.t = t  # Minimum degree (defines the range of keys per node)

    def insert(self, file_name, location):
        root = self.root
        if len(root.keys) == (2 * self.t) - 1:
            # Root is full, split it
            new_node = self.Node(is_leaf=False)
            new_node.children.append(self.root)
            self._split(new_node, 0)
            self.root = new_node

        self._insert_non_full(self.root, file_name, location)

    def _insert_non_full(self, node, file_name, location):
        i = len(node.keys) - 1
        if node.is_leaf:
            # Insert the file directly into the leaf node
            while i >= 0 and file_name < node.keys[i]:
                i -= 1
            node.keys.insert(i + 1, file_name)
            node.children.insert(i + 1, location)
        else:
            # Find the child node to insert into
            while i >= 0 and file_name < node.keys[i]:
                i -= 1
            i += 1
            child = node.children[i]
            if len(child.keys) == (2 * self.t) - 1:
                self._split(node, i)
                if file_name > node.keys[i]:
                    i += 1
            self._insert_non_full(node.children[i], file_name, location)

    def _split(self, parent, i):
        node = parent.children[i]
        new_node = self.Node(is_leaf=node.is_leaf)
        mid_index = len(node.keys) // 2
        parent.keys.insert(i, node.keys[mid_index])
        parent.children.insert(i + 1, new_node)

        new_node.keys = node.keys[mid_index + 1:]
        node.keys = node.keys[:mid_index]

        if not node.is_leaf:
            new_node.children = node.children[mid_index + 1:]
            node.children = node.children[:mid_index + 1]

    def search(self, file_name):
        return self._search(self.root, file_name)

    def _search(self, node, file_name):
        i = 0
        while i < len(node.keys) and file_name > node.keys[i]:
            i += 1
        if i < len(node.keys) and node.keys[i] == file_name:
            return node.children[i]  # Return the location of the file

        if node.is_leaf:
            return None
        return self._search(node.children[i], file_name)

# Example Usage
btree = BTree(t=3)

# Insert files into the B-tree
btree.insert("file1.txt", "Location 1")
btree.insert("file2.txt", "Location 2")
btree.insert("file3.txt", "Location 3")
btree.insert("file4.txt", "Location 4")

# Search for a file by name
location = btree.search("file2.txt")
print(f"File found at: {location}")
