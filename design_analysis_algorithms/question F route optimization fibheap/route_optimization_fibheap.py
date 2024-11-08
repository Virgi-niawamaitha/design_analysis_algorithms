import math

class FibHeap:
    class Node:
        def __init__(self, key):
            self.key = key
            self.degree = 0
            self.parent = None
            self.child = None
            self.mark = False
            self.next = None
            self.prev = None

    def __init__(self):
        self.min_node = None
        self.node_count = 0

    def insert(self, key):
        new_node = self.Node(key)
        if not self.min_node:
            self.min_node = new_node
            new_node.next = new_node.prev = new_node
        else:
            self._link(self.min_node, new_node)
            if key < self.min_node.key:
                self.min_node = new_node
        self.node_count += 1

    def _link(self, min_node, new_node):
        new_node.next = min_node
        new_node.prev = min_node.prev
        min_node.prev.next = new_node
        min_node.prev = new_node

    def extract_min(self):
        min_node = self.min_node
        if min_node:
            if min_node.child:
                child = min_node.child
                while child:
                    next_child = child.next
                    child.prev = min_node.prev
                    min_node.prev.next = child
                    child.prev.next = child
                    child = next_child
            min_node.prev.next = min_node.next
            min_node.next.prev = min_node.prev
            if min_node == min_node.next:
                self.min_node = None
            else:
                self.min_node = min_node.next
                self._consolidate()
            self.node_count -= 1
            return min_node.key
        return None

    def _consolidate(self):
        max_degree = int(math.log(self.node_count) / math.log(2))
        arr = [None] * (max_degree + 1)
        current = self.min_node
        while current:
            degree = current.degree
            while arr[degree]:
                other = arr[degree]
                if current.key > other.key:
                    current, other = other, current
                self._link(self.min_node, other)
                arr[degree] = None
                degree += 1
            arr[degree] = current
            current = current.next

        self.min_node = None
        for node in arr:
            if node:
                if not self.min_node or node.key < self.min_node.key:
                    self.min_node = node

    def decrease_key(self, node, new_key):
        if new_key > node.key:
            return  # Error: new key is greater than current key
        node.key = new_key
        parent = node.parent
        if parent and node.key < parent.key:
            self._cut(node, parent)
            self._cascading_cut(parent)

    def _cut(self, node, parent):
        if node.next:
            node.prev.next = node.next
            node.next.prev = node.prev
        if parent.child == node:
            parent.child = node.next
        parent.degree -= 1
        node.parent = None
        node.mark = False
        self._link(self.min_node, node)

    def _cascading_cut(self, node):
        parent = node.parent
        if parent:
            if not node.mark:
                node.mark = True
            else:
                self._cut(node, parent)
                self._cascading_cut(parent)

# Example Usage
fib_heap = FibHeap()

# Insert distances (representing locations in route optimization)
fib_heap.insert(10)
fib_heap.insert(20)
fib_heap.insert(5)

# Extract the minimum distance (location with shortest distance)
min_distance = fib_heap.extract_min()
print(f"The node with the smallest distance is {min_distance}")

# Decrease the key of a node (updating distance to a new smaller value)
fib_heap.decrease_key(fib_heap.min_node, 3)
min_distance = fib_heap.extract_min()
print(f"The node with the updated smallest distance is {min_distance}")
