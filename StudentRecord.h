#ifndef COURSEWORK_STUDENTRECORD_H
#define COURSEWORK_STUDENTRECORD_H

#include <string>
#include <map>
#include <vector>

#include "Module.h"

using namespace std;

// store the grades of one student
class StudentRecord {
public:
    // represent one module mark
    class Mark {
    public:
        string module_code; // module code
        int mark; // module mark
        // constructor to build a mark entry
        Mark(const string &code, int m) {
            module_code = code;
            mark = m;
        }
    };

    string student_id; // unique student ID
    map<int, vector<Mark>> records; // connect term code to student marks

    StudentRecord();
    explicit StudentRecord(const string &id); // set student ID

    // store mark inside map for respective term
    void addMark(int term_code, const string &module_code, int mark);

    // return all terms of a student
    vector<int> getTerms() const;
    // return vector of term marks
    vector<Mark> getTermMarks(int term_code) const;

    // calculate the credit-weighted term average
    double termAvg(int term_code, const map<string, Module> &module) const;
    // calculate the total credit-weighted average for all terms
    double totalAvg(const map<string, Module> &module) const;

    string getID() const; // return student ID
};

#endif //COURSEWORK_STUDENTRECORD_H