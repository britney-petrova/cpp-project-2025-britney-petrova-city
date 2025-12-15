#include "TranscriptSys.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

// load modules from file
bool TranscriptSystem::load_modules(const string &filename) {
    ifstream file(filename); // open file

    // check if opened
    if (!file) {
        cout << "Error opening " << filename << "\n";
        return false;
    }

    // declare module info
    string code, name;
    int credit;

    // read each line
    while (file >> code >> credit >> name) {
        modules[code] = Module(code, credit, name);  // store module in map
    }

    file.close(); // close file
    return true;
}

// load student marks from file
bool TranscriptSystem::load_marks(const string &filename) {
    ifstream file(filename); // open file

    // check if opened
    if (!file) {
        cout << "Error opening " << filename << "\n";
        return false;
    }

    // declare student info
    string student_id, module_code;
    int term, mark;

    // read each line
    while (file >> student_id >> term >> module_code >> mark) {
        // check if student record exists
        if (records.count(student_id) == 0) {
            // create new record if non-existent
            records[student_id] = StudentRecord(student_id);
        }
        // add mark to student record
        records[student_id].addMark(term, module_code, mark);
    }

    file.close(); // close file
    return true;
}

// process requests and print transcripts
bool TranscriptSystem::process_reqs(const string &filename) {
    ifstream file(filename); // open file

    // check if opened
    if (!file) {
        cout << "Error opening " << filename << "\n";
        return false;
    }

    // declare requests info
    string line, student_id;
    int term;

    // read each request line
    while (getline(file, line)) {
        // check if line is empty
        if (line.empty()) {
            continue; // skip empty lines
        }

        istringstream iss(line); // read line as input
        iss >> student_id; // read student ID

        // flag for term-specific requests
        bool hasTerm = false;
        if (iss >> term) hasTerm = true;

        // check if student exists
        if (records.count(student_id) == 0) {
            cout << "No records found for " << student_id << "\n\n";
            continue;
        }

        StudentRecord &student = records[student_id];  // reference to record

        // print transcript
        if (hasTerm) {
            Transcript(student, term); // print only one term
        } else {
            Transcript(student, -1); // print full transcript
        }
    }

    file.close(); // close file
    return true;
}

// print transcript (full or term-specific)
void TranscriptSystem::Transcript(const StudentRecord &student, int term) const {
    cout << "Student ID: " << student.getID() << "\n"; // output student ID

    vector<int> terms; // store terms

    if (term == -1) {
        // get all terms for full transcript
        terms = student.getTerms();
    } else {
        // get only requested term for ter-specific transcript
        terms.push_back(term);
    }

    // loop through terms
    for (int t : terms) {
        cout << "  Term " << t << ":\n"; // out term

        // store student marks
        const vector<StudentRecord::Mark> &marks = student.getTermMarks(t);

        // print each module mark
        for (const auto &entry : marks) {
            Module m = modules.at(entry.module_code); // lookup module
            cout << "    "
            << entry.module_code << " "
            << m.getName() << " ("
            << m.getCredit()
            << " credits): "
            << entry.mark << "\n";
        }

        // print term average
        double avg = student.termAvg(t, modules);
        cout << "  Term Average: " << fixed << setprecision(2) << avg << "\n";
    }

    // print overall average only if full transcript
    if (term == -1) {
        double overall = student.totalAvg(modules);
        cout << "  Overall Average: " << fixed << setprecision(2) << overall << "\n\n";
    } else {
        cout << "\n"; // blank line after term-specific transcript
    }
}
