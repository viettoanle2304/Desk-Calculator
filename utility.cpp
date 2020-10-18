//
// Created by Viet Toan Le on 18.10.2020.
//

#include <iostream>
#include "Stack.h"
#include "utility.h"
using namespace std;

bool full(Stack &s) {
    /*
     Pre: None.
     Post: Leaves the Stack s unchanged and returns a value of true or false according to
        whether the Stack is or is not full.
     */
    Stack_entry test = 5;
    Error_code outcome;
    outcome = s.push(test);
    if (outcome == success) {
        s.pop();
        return false;
    } else return true;
}

Error_code pop_top(Stack &s, Stack_entry &t) {
    /*
     Pre: None.
     Post: Removes the top entry from the Stack s and returns its value as the output parameter t.
     */
    if (s.empty()) {
        return underflow;
    }
    s.top(t);
    s.pop();
    return success;
}

void clear(Stack &s) {
    /*
     Pre: None.
     Post: Delete all entries and returns Stack s as an empty Stack.
     */
    while (!s.empty()) {
        s.pop();
    }
}

int size(Stack &s) {
    /*
     Pre: None.
     Post: Leaves the Stack s unchanged and returns a count of the number of entries in the Stack.
     */
    int count = 0;
    Stack temp;
    Stack_entry item;
    while (!s.empty()) {
        s.top(item);
        s.pop();
        temp.push(item);
        ++count;
    }

    while (!temp.empty()) {
        temp.top(item);
        temp.pop();
        s.push(item);
    }

    return count;
}

void delete_all(Stack &s, Stack_entry x) {
    /*
     Pre: None.
     Post: Delete all occurrences (if any) of x from Stack s and leaves the remaining entries in
        Stack s in the same relative order.
     */
    Stack temp;
    Stack_entry item;

    while (!s.empty()) {
        s.top(item);
        s.pop();
        if (item != x) {
            temp.push(item);
        }
    }

    while (!temp.empty()) {
        temp.top(item);
        temp.pop();
        s.push(item);
    }
}

Error_code copy_stack_a(Stack &dest, Stack &source) {
    /*
     Pre: None.
     Post: Stack dest has become an exact copy of Stack source; source is unchanged.
     */
    dest = source;
    return success;
}

Error_code copy_stack_b(Stack &dest, Stack &source) {
    /*
     Pre: None.
     Post: Stack dest has become an exact copy of Stack source; source is unchanged.
     */
    Error_code detected = success;
    Stack temp;
    Stack_entry item;

    while (detected == success && !source.empty()) {
        detected = source.top(item);
        source.pop();
        if (detected == success) {
            detected = temp.push(item);
        }
    }

    while (detected == success && !temp.empty()) {
        detected = temp.top(item);
        temp.pop();
        if (detected == success) {
            detected = dest.push(item);
            detected = source.push(item);
        }
    }

    return detected;
}

void showStack(Stack &s) {
    Stack_entry item;
    Stack temp;

    if (s.empty()) {
        cout << "The stack is empty." << endl;
    }

    while (!s.empty()) {
        s.top(item);
        cout << item << " ";
        s.pop();
        temp.push(item);
    }

    cout << "\n";

    while(!temp.empty()) {
        temp.top(item);
        temp.pop();
        s.push(item);
    }
}