#ifndef COURSEWORK_MODULE_H
#define COURSEWORK_MODULE_H

#include <string>

using namespace std;

// represent the info of one module
class Module {
private:
    string module_name; // store module name
    string module_code; // store module code
    int credit = 0; // store module credit value

public:
    // initialise an empty module
    Module();
    // add parameters
    Module(const string &code, int credit_val, const string &name);
    // access and return module name, code, credit value
    string getName();
    string getCode();
    int getCredit() const;
};

#endif //COURSEWORK_MODULE_H