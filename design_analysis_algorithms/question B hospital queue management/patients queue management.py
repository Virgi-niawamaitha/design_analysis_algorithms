from collections import deque

# PatientQueue for managing normal patient arrivals
class PatientQueue:
    def __init__(self):
        self.queue = deque()  # Using deque to implement queue
    
    def enqueue(self, patient):
        """Add a patient to the end of the queue."""
        self.queue.append(patient)
    
    def dequeue(self):
        """Remove and return the first patient from the queue."""
        if self.is_empty():
            return None
        return self.queue.popleft()
    
    def is_empty(self):
        """Check if the queue is empty."""
        return len(self.queue) == 0
    
    def size(self):
        """Return the size of the queue."""
        return len(self.queue)

# EmergencyStack for handling priority emergency patients
class EmergencyStack:
    def __init__(self):
        self.stack = []  # Using a list to implement stack
    
    def push(self, patient):
        """Add an emergency patient to the top of the stack."""
        self.stack.append(patient)
    
    def pop(self):
        """Remove and return the most recent emergency patient."""
        if self.is_empty():
            return None
        return self.stack.pop()
    
    def is_empty(self):
        """Check if the stack is empty."""
        return len(self.stack) == 0
    
    def size(self):
        """Return the size of the stack."""
        return len(self.stack)

# Example usage
if __name__ == "__main__":
    # Creating instances of PatientQueue and EmergencyStack
    patient_queue = PatientQueue()
    emergency_stack = EmergencyStack()

    # Adding patients to the queue
    patient_queue.enqueue("Patient A")
    patient_queue.enqueue("Patient B")
    patient_queue.enqueue("Patient C")
    
    # Adding emergency patients to the stack
    emergency_stack.push("Emergency Patient X")
    emergency_stack.push("Emergency Patient Y")

    # Process emergency patients first (stack)
    print("Treating:", emergency_stack.pop())  # Emergency Patient Y
    print("Treating:", emergency_stack.pop())  # Emergency Patient X

    # Now process normal patients (queue)
    print("Treating:", patient_queue.dequeue())  # Patient A
    print("Treating:", patient_queue.dequeue())  # Patient B
    print("Treating:", patient_queue.dequeue())  # Patient C
