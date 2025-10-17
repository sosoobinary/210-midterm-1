// COMSC 210 | Midterm 1 | Quang Ngo
// IDE used: Visual Studio Code
#include <iostream> // library for cin and cout
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
// Constants used in the demo

class DoublyLinkedList {
private:
    struct Node {
        int data;       // value contained in node
        Node* prev;     // pointer reference to the previous node
        Node* next;     // pointer reference to the next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {   // Constructor with default values for prev and next, val must be given
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // pointer to first node
    Node* tail; // pointer to last node

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // empty list created

    void insert_after(int value, int position) {    // inserts a node in a certain postition, with given (int) value and (int) position
        if (position < 0) { // checks for position validation if under 0
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);    // new node to insert is created
        if (!head) {    // checks for empty list. if so, newNode is both head and tail due to being the only object in list
            head = tail = newNode;
            return;
        }

        Node* temp = head;  // temp value set to head to navigate to position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;  // temp is iterated until it reaches the correct position

        if (!temp) {    // runs when position is not found within list, closes function
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next; // newNode next node is set to temp's next
        newNode->prev = temp;   // newNode prev node is set to temp
        if (temp->next) // checks if temp is not last node
            temp->next->prev = newNode; // change next node's prev node to newNode
        else
            tail = newNode; // set tail if it is the last node
        temp->next = newNode;   // temp next is set to newNode
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}