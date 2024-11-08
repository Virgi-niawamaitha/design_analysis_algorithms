#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// PatientQueue for managing normal patient arrivals
class PatientQueue {
private:
    queue<string> q;  // Queue to store patients

public:
    void enqueue(const string& patient) {
        q.push(patient);  // Add patient to the queue
    }

    string dequeue() {
        if (isEmpty()) {
            return "";
        }
        string patient = q.front();
        q.pop();  // Remove and return the front patient
        return patient;
    }

    bool isEmpty() const {
        return q.empty();  // Check if the queue is empty
    }

    int size() const {
        return q.size();  // Return the size of the queue
    }
};

// EmergencyStack for handling emergency patients
class EmergencyStack {
private:
    stack<string> s;  // Stack to store emergency patients

public:
    void push(const string& patient) {
        s.push(patient);  // Add emergency patient to the stack
    }

    string pop() {
        if (isEmpty()) {
            return "";
        }
        string patient = s.top();
        s.pop();  // Remove and return the top emergency patient
        return patient;
    }

    bool isEmpty() const {
        return s.empty();  // Check if the stack is empty
    }

    int size() const {
        return s.size();  // Return the size of the stack
    }
};

// Example usage
int main() {
    // Create instances of PatientQueue and EmergencyStack
    PatientQueue patientQueue;
    EmergencyStack emergencyStack;

    // Add normal patients to the queue
    patientQueue.enqueue("Patient A");
    patientQueue.enqueue("Patient B");
    patientQueue.enqueue("Patient C");

    // Add emergency patients to the stack
    emergencyStack.push("Emergency Patient X");
    emergencyStack.push("Emergency Patient Y");

    // Process emergency patients first (stack)
    cout << "Treating: " << emergencyStack.pop() << endl;  // Emergency Patient Y
    cout << "Treating: " << emergencyStack.pop() << endl;  // Emergency Patient X

    // Now process normal patients (queue)
    cout << "Treating: " << patientQueue.dequeue() << endl;  // Patient A
    cout << "Treating: " << patientQueue.dequeue() << endl;  // Patient B
    cout << "Treating: " << patientQueue.dequeue() << endl;  // Patient C

    return 0;
}
