#include "Module.h"

using namespace std;

// set all the variables to zero/empty
Module::Module() {
    module_name = "";
    module_code = "";
    credit = 0;
}

// initialise the constructor with given values
Module::Module(const string &code, int credit_val, const string &name) {
    module_name = name;
    module_code = code;
    credit = credit_val;
}

// return module name
string Module::getName() {
    return module_name;
}

// return module code
string Module::getCode() {
    return module_code;
}

// return module credit value
int Module::getCredit() const {
    return credit;
}
