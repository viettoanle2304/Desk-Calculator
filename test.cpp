for (int i = 0; i < str.length() + 1; ++i) {
if (str[i] == '_' && isdigit(str[i+1])){
str[i] = '-';
i += 2;
}
if ((str[i] == ' ' || str[i] == '\0') && isdigit(str[i-1])) {
temp = str.substr(0, i + 1);
convert(temp, numbers);
str.erase(0, i + 1);
i = 0;
} else if (str[i] != ' ' && !isdigit(str[i])) {
if (str[i+1] == ' ' || str[i+1] == '\0'){
if (str[i] == '?' || str[i] == 'p' || str[i] == '+' ||
str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == 'q' ||
str[i] == 'x' || str[i] == 's' || str[i] == 'a' ||
str[i] == '%' || str[i] == '^' || str[i] == 'v' || str[i] == 'c') {
command = tolower(str[i]);
str.erase(0, i+1);
if (command == 'p')
command = '=';
break;
} else {
cout << "Warning: " << str[i] << " is an invalid command." << endl;
str.erase(0, i+2);
}
} else if (str[i] == '-' && str[i+1] == 'p'){
cout << "Warning: "<< str[i] << str[i+1] << " is an invalid command in calculation." << endl
<< R"(If you mean "open prompts ui", please use standalone "-p" command again.)" << endl;
str.erase(0, i+3);
} else {
cout << "Warning: "<< str[i] << str[i+1] << " is an invalid command." << endl;
str.erase(0, i+3);
}
}
}