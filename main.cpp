#include <iostream>
#include <math.h>
#include "utility.h"
#include "Stack.h"
using namespace std;

void introduction();
void instructions();
bool do_command(char command, Stack &numbers);
char get_command();
double sum(Stack &numbers);

int main() {
    /*
     Post: The program has executed simple arithmetic commands entered by the user.
     Uses: The class Stack and the functions introduction, instructions, do_command, and get_command.
     */
    Stack stored_numbers;
    introduction();
    instructions();
    while(do_command(get_command(), stored_numbers));
    return 0;
}

void introduction() {
    cout << "Desk Calculation Program" << endl;
    cout << "**************************************\n\n" << endl;
}

void instructions() {
    cout << "Use commands to read in and operate on integers." << endl;
    cout << "Valid commands are listed below: " << endl;
    cout << "[?]to enter an integer onto the stack." << endl;
    cout << "[=] to print the top integer in the stack." << endl;
    cout << "[+] [-] [*] [/] are arithmetic operations." << endl;
    cout << "[%] is remainder operation" << endl;
    cout << "[^] is power increase operation" << endl;
    cout << "[v] is square root operation" << endl;
    cout << "E[x]change two top numbers in the stack." << endl;
    cout << "[S]um all the numbers in the stack." << endl;
    cout << "[A]verage all numbers in the stack." << endl;
    cout << "[Q]uit" << endl;
}

char get_command() {
    char command;
    bool waiting = true;
    cout << "Select command and press <Enter>: ";

    while (waiting) {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
        command == '-' || command == '*' || command == '/' || command == 'q' ||
        command == 'x' || command == 's' || command == 'a' ||
        command == '%' || command == '^' || command == 'v') {
            waiting = false;
        } else {
            cout << "Please enter a valid command: " << endl
                << "[?]push to stack\t[=]print top" << endl
                << "[+] [-] [*] [/] are arithmetic operations" << endl
                << "E[x]change two top numbers in the stack." << endl
                << "[S]um all the numbers in the stack." << endl
                << "[A]verage all the numbers in the stack" << endl
                << "[Q]uit." << endl;
        }
    }
    return command;
}

bool do_command(char command, Stack &numbers) {
    /*
     Pre: The first parameter specifies a valid calculator command.
     Post: The command specified by the first parameter has been applied
        to the Stack of numbers given by the second parameter.
        A result of true is returned unless command == 'q'.
    Uses: The class Stack.
     */
    double p, q;
    int count;
    switch(command) {
        case '?':
            cout << "Enter a real number: ";
            cin >> p;
            if (numbers.push(p) == overflow) {
                cout << "Warning: Stack full, lost number" << endl;
            }
            break;
        case '=':
            if (numbers.top(p) == underflow) {
                cout << "Stack empty" << endl;
            } else {
                cout << p << endl;
            }
            break;
        case '+':
            if (numbers.top(p) ==underflow) {
                cout << "Stack empty" << endl;
            } else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(q + p) == overflow) {
                        cout << "Warning: Stack full, lost result" << endl;
                    }
                }
            }
            break;
        case '-':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(q - p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case '*':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(q * p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case '/':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(q / p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case '%':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push((int) q % (int) p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case '^':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(pow(q, p)) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case 'v':
            if(numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.push(sqrt(p)) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
            break;
        case 'x':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                } else {
                    numbers.pop();
                    if (numbers.push(p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                    if (numbers.push(q) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;
        case 's':
            p = sum(numbers);
            while (!numbers.empty()) {
                numbers.pop();
            }
            if (numbers.push(p) == overflow)
                cout << "Warning: Stack full, lost result" << endl;
            break;
        case 'a':
            p = sum(numbers);
            count = size(numbers);
            if (count <= 0)
                cout << "Stack empty" << endl;
            else {
                while(!numbers.empty()) {
                    numbers.pop();
                }
                if (numbers.push(p / (double) count) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
            break;
        case 'q':
            cout << "Calculation finished." << endl;
            return false;
    }
    return true;
}

double sum(Stack &numbers) {
    /*
     Post: The sum of all entries in the stack is returned.
     Uses: The class Stack
     */
    double p, sum;
    Stack temp;
    while (!numbers.empty()) {
        numbers.top(p);
        temp.push(p);
        sum += p;
        numbers.pop();
    }

    while (!temp.empty()) {
        temp.top(p);
        numbers.push(p);
        temp.pop();
    }

    return sum;
}

