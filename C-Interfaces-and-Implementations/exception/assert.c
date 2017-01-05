#include "assert.h"

const except_t assert_failure = {"Assertion failed"};

void (assert)(int e) {
    assert(e);
}
