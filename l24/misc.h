#ifndef MISC_H
#define MISC_H


int char_is_operation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int char_is_number(char c) {
    return '0' <= c && c <= '9';
}

int char_is_bracket(char c) {
    return c == '(' || c == ')';
}

#endif