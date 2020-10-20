#include <iostream>
#include <cmath>
#include "utility.h"
#include "Stack.h"
#include <sstream>
#include <algorithm>
using namespace std;

void introduction();
void instructions();
bool do_command(char command, Stack &numbers);
char get_command_prompts();
double sum(Stack &numbers);
void convert(string str, Stack &s);
char get_command_noprompts(string &str, Stack &numbers);
void program_handle(string &str, Stack &numbers);
void run_program(bool switch_ui, string &str, Stack &numbers);

int main() {
    /*
     Post: The program has executed simple arithmetic commands entered by the user.
     Uses: The class Stack and the functions introduction, instructions, do_command, and get_command.
     */
    Stack stored_numbers;
    string str;

    program_handle(str, stored_numbers);

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
    cout << "[C]lear all saved entries in the stack." << endl;
    cout << "S[w]itch to no prompts ui." << endl;
    cout << "[Q]uit" << endl;
}

char get_command_noprompts(string &str, Stack &numbers) {
    char command = '\0';
    string temp;

    // Replace all '_' into '-' if it means negative
    int index = -1;
    replace_if(str.begin(), str.end(), [&str, &index](char c) {
        ++index;
        return (c == '_' && isdigit(str[index+1]));
    }, '-');

    // Take out each numbers/command
    if (any_of(str.begin(), str.end(), [](char c){
        return (c == ' ');
    })) {
        size_t pos = str.find(' ');
        temp = str.substr(0, pos);
        str.erase(0, pos + 1);
    } else {
        temp = str;
        str.clear();
    }

    if (temp == "p" || temp == "+" ||
        temp == "-" || temp == "*" || temp == "/" || temp == "q" ||
        temp == "x" || temp == "s" || temp == "a" ||
        temp == "%" || temp == "^" || temp == "v" || temp == "c") {
        command = tolower(temp[0]);
        if (command == 'p')
            command = '=';
    } else if (!str.empty() && all_of(temp.begin(), temp.end(), [](char c) {
        return (c == '-' || isdigit(c));
    })){
        convert(temp, numbers);
    } else if (temp == "-p") {
        cout << "Warning: -p is an invalid command in calculation." << endl
            << R"(If you mean "open prompts ui", please use standalone "-p" command again.)" << endl;
    } else if (!temp.empty()){
        cout << "Warning: " << temp << " is an invalid command." << endl;
    }

    return command;
}

char get_command_prompts() {
    char command = '\0';
    bool waiting = true;
    cout << "Select command and press <Enter>: ";

    while (waiting) {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
        command == '-' || command == '*' || command == '/' || command == 'q' ||
        command == 'x' || command == 's' || command == 'a' || command == 'w' ||
        command == '%' || command == '^' || command == 'v' || command == 'c') {
            waiting = false;
        } else {
            cout << "Please enter a valid command: " << endl
                << "[?]push to stack\t[=]print top" << endl
                << "[+] [-] [*] [/] are arithmetic operations" << endl
                << "E[x]change two top numbers in the stack" << endl
                << "[S]um all the numbers in the stack" << endl
                << "[A]verage all the numbers in the stack" << endl
                << "[C]lear all the numbers in the stack" << endl
                << "S[w]itch to no prompts ui." << endl
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
        case 'c':
            clear(numbers);
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
        case 'w':
            cout << "UI: turned off\n" << endl;
            return false;
        case 'q':
            cout << "Calculation finished." << endl;
            exit(0);
    }
    return true;
}

double sum(Stack &numbers) {
    /*
     Post: The sum of all entries in the stack is returned.
     Uses: The class Stack
     */
    double p, sum = 0.0;
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

void convert(string str, Stack &s) {
    stringstream ss;
    ss << str;

    int temp;
    while (!ss.eof()) {
        ss >> temp;
        if (s.push(temp) == overflow) {
            cout << "Warning: Stack full, lost input" << endl;
            break;
        }
    }
}

void program_handle(string &str, Stack &numbers) {
    bool ui = false;

    getline(cin, str);

    if (str == "-p") {
        ui = true;
        run_program(ui, str, numbers);
    } else {
        ui = false;
        run_program(ui, str, numbers);
    }

    program_handle(str, numbers);
}

void run_program(bool switch_ui, string &str, Stack &numbers) {
    if (switch_ui) {
        introduction();
        instructions();
        while(do_command(get_command_prompts(), numbers));
    } else {
        do {
            do_command(get_command_noprompts(str, numbers), numbers);
        } while (!str.empty());
    }
}