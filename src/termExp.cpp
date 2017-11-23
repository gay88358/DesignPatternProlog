#include "../include/termExp.h"


TermExp::TermExp(Term* term): _term(term) {
    this->term = term;
    this->payload = "TERM";
}

void TermExp::interpret(string text) {

}

bool TermExp::evaluate() {
    return true;
}

void TermExp::clear() {

}
