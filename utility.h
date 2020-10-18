#ifndef DESK_CALCULATOR_UTILITY_H
#define DESK_CALCULATOR_UTILITY_H
#include "Stack.h"

bool full(const Stack &s);
Error_code pop_top(Stack &s, Stack_entry &t);
void clear(Stack &s);
int size(Stack &s);
void delete_all(Stack &s, Stack_entry x);
Error_code copy_stack_a(Stack &dest, Stack &source);
Error_code copy_stack_b(Stack &dest, Stack &source);
void showStack(Stack &s);
#endif //DESK_CALCULATOR_UTILITY_H
