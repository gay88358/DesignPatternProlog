#ifndef GLOBAL_H
#define GLOBAL_H

class Global {
public:
    const int NONE = -1; // no tokenValue
    // tokens return by the scanner
    const int EOS = '\0';
    const int NUMBER = 256;
    const int ATOM = 257;
    const int ATOMSC = 258;
    const int VAR = 259;
    const int LIST = 260;
    const int STRUCT = 261;

    char FORMER_PARENTHESES = '(';
    char LATTER_PARENTHESES = ')';
    char FORMER_BRACKET = '[';
    char LATTER_BRACKET = ']';

    bool isSpecialCh(char c) {
        return c == '+'
        // || c == '=' // ... the matching operator
           || c == '-'
           || c == '*'
           || c == '/'
           || c == '<'
           || c == '>'
           || c == '.'
           || c == '&'
           || c == '\\'
           || c == '~'
           || c == '^'
           || c == '$'
           || c == '#'
           || c == '@'
           || c == '?'
           || c == ':';
    }

    bool isFormerPart(char c) {
        return (c == FORMER_PARENTHESES || c == FORMER_BRACKET);
    }

    bool isLatterPart(char c) {
        return (c == LATTER_PARENTHESES || c == LATTER_BRACKET);
    }

    bool misMatch(char former, char latter) {
        return ((former == FORMER_PARENTHESES && latter != LATTER_PARENTHESES)
                || (former == FORMER_BRACKET && latter != LATTER_BRACKET));
    }
private:
 
};


#endif