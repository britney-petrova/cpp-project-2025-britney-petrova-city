#include "StudentRecord.h"
#include "Module.h"

using namespace std;

// default constructor
StudentRecord::StudentRecord() {
    student_id = ""; // empty map
}

StudentRecord::StudentRecord(const string &id) {
    student_id = id; // assign student ID
}

// add mark for one term
void StudentRecord::addMark(int term_code, const string &module_code, int mark) {
    // create and add a mark to the vector for term
    records[term_code].emplace_back(module_code, mark);
}

string StudentRecord::getID() const {
    return student_id; // return student ID
}

// return vector of all terms of a student
vector<int> StudentRecord::getTerms() const {
    vector<int> terms;

    // pre-allocate vector capacity
    terms.reserve(records.size());

    // loop through the map with term number as key
    for (auto &pair : records) {
        terms.push_back(pair.first); // push term number to vector
    }

    return terms;
}

// return marks for one term
vector<StudentRecord::Mark> StudentRecord::getTermMarks(int term_code) const {
    return records.at(term_code);
}

// calculate weighted average for one term
double StudentRecord::termAvg(int term_code, const map<string, Module> &module) const {
    // all module marks for term
    const auto &entries = records.at(term_code);

    double weighted_sum = 0.0; // sum of mark * credit
    int total_credits = 0; // sum of credits

    // loop through each mark in term
    for (const auto &entry : entries) {
        int credit = module.at(entry.module_code).getCredit(); // look up credit value
        weighted_sum += entry.mark * credit; // add weighted mark
        total_credits += credit; // add credit
    }

    // prevent divide-by-zero
    if (total_credits == 0.0) {
        return 0.0;
    }

    return weighted_sum / total_credits; // weighted average
}

// calculate the total weighted average across all terms
double StudentRecord::totalAvg(const map<string, Module> &module) const {
    double weighted_sum = 0.0;
    int total_credits = 0;

    // loop through each term
    for (const auto &termEntry : records) {
        // loop through each mark in term
        for (const auto &entry : termEntry.second) {
            int credit = module.at(entry.module_code).getCredit();
            weighted_sum += entry.mark * credit;
            total_credits += credit;
        }
    }

    if (total_credits == 0.0) {
        return 0.0;
    }

    return weighted_sum / total_credits; // total weighted average
}
