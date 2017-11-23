#include "../include/termExp.h"

TermExp::TermExp(Term* term): _term(term) {
    this->term = term;
    this->payload = "TERM";
}

bool TermExp::evaluate() {
    return true;
}
