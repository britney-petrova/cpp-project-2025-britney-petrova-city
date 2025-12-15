#ifndef COURSEWORK_TRANSCRIPTS_H
#define COURSEWORK_TRANSCRIPTS_H

#include <string>
#include <map>
#include "Module.h"
#include "StudentRecord.h"

using namespace std;

// manage all transcripts
class TranscriptSystem {
private:
    map<string, Module> modules; // all modules
    map<string, StudentRecord> records; // all student records

public:
    // load modules from file
    bool load_modules(const string &filename);
    // load student marks from file
    bool load_marks(const string &filename);
    // process requests and print transcripts
    bool process_reqs(const string &filename);
    // print a student transcript
    void Transcript(const StudentRecord &student, int term = -1) const;
};

#endif //COURSEWORK_TRANSCRIPTS_H