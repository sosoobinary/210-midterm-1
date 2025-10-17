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

    void delete_val(int value) {    // deletes node with a given (int) value
        if (!head) return;  // checks for empty list. if so, function is cancelled

        Node* temp = head;  // temp value set to head to navigate to position
        
        while (temp && temp->data != value) // iterates through list, checking for given value
            temp = temp->next;

        if (!temp) return; // runs when value is not found within list, closes function

        if (temp->prev) // checks for head node
            temp->prev->next = temp->next; // used to bypass temp with prev node
        else
            head = temp->next; // set head if head is being deleted

        if (temp->next) // checks for tail node
            temp->next->prev = temp->prev;  // used to bypass temp with next node
        else
            tail = temp->prev; // set tail if tail is being deleted

        delete temp;    // memory clear
    }

    void delete_pos(int pos) {  // deletes node with a given (int) position
        if (!head) {    // checks for empty list. if so, displays error and function is cancelled
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { // if deleting first node, use function pop_front() for simplicity
            pop_front();
            return;
        }
    
        Node* temp = head;  // temp value set to head to navigate to position
    
        for (int i = 1; i < pos; i++){ // iterates through list, checking for insufficient sized list
            if (!temp) {    // runs when list is too small, displays error and closes function
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {    // runs when list is too small, displays error and closes function. checked again to cover the loop's blind spot
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {  // check for tail node. if so, uses pop_back() for simplicity
            pop_back();
            return;
        }
        
        // sets pointers to eventually delete temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;    // memory clear
    }

    void push_back(int v) { // adds node to tail, with given (int) value
        Node* newNode = new Node(v);    // new node to insert is created
        if (!tail)  // check if list is empty
            head = tail = newNode;  // add newNode as only value
        else {
            tail->next = newNode;   // set current tail to newNode
            newNode->prev = tail;   // set newNode prev to previous tail
            tail = newNode; // set tail
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);    // new node to insert is created
        if (!head)  // check if list is empty
            head = tail = newNode;  // add newNode as only value
        else {
            newNode->next = head;   // set current head to newNode
            head->prev = newNode;   // set newNode prev to previous head
            head = newNode; // set head
        }
    }
    
    void pop_front() {  // deletes head node from list

        if (!head) {    // checks for empty list. if so, displays error and function is cancelled
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // temp set to head as dummy

        if (head->next) {   // checks if list has more than one node, else assumes one node
            head = head->next;  // set second node as head
            head->prev = nullptr;   // head prev set to null
        }
        else
            head = tail = nullptr;  // head and tail are set to null due to no remaining nodes after deletion
        delete temp;    // memory clear
    }

    void pop_back() {   // deletes tail node from list
        if (!tail) {    // checks for empty list. if so, displays error and function is cancelled
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {   // checks if list has more than one node, else assumes one node
            tail = tail->prev;  // set second to last node as tail
            tail->next = nullptr;   // tail next set to null
        }
        else
            head = tail = nullptr;  // head and tail are set to null due to no remaining nodes after deletion
        delete temp;    // memory clear
    }

    ~DoublyLinkedList() {   // deconstructor: deletes all nodes
        while (head) {  // iterates through list
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {  // display list from first to last node
        Node* current = head;   // temp value set to head to navigate list
        if (!current) { // check id list is empty, display error and close function
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // iterates through list
            cout << current->data << " ";   // print node
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {  // display list from last to first node
        Node* current = tail;   // temp value set to head to navigate list
        if (!current) { // check id list is empty, display error and close function
            cout << "List is empty." << endl;
            return;
        }
        while (current) {   // iterates through list
            cout << current->data << " ";   // print node
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_element() {
        Node* current = head;
        bool other = false;

        while(current) {
            current = current->next;
            other = !other;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}