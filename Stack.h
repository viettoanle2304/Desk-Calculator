#ifndef DESK_CALCULATOR_STACK_H
#define DESK_CALCULATOR_STACK_H
#include "error_code.h"

const int maxstack = 50;
typedef double Stack_entry;

class Stack {
private:
    int count;
    Stack_entry entry[maxstack];
public:
    Stack();
    Error_code pop();
    Error_code push(const Stack_entry &item);
    Error_code top(Stack_entry &item) const;
    bool empty() const;
    friend Error_code copy_stack(Stack &dest, Stack &source);
};

Error_code copy_stack(Stack &dest, Stack &source);
#endif //DESK_CALCULATOR_STACK_H
