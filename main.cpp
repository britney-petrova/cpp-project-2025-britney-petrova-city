#include <iostream>
#include "TranscriptSys.h"

using namespace std;

// place the input files in the same directory where you run the program!
int main() {
    TranscriptSystem system;

    // load modules
    if (!system.load_modules("modules.txt")) return 1;

    // load student grades
    if (!system.load_marks("grades.txt")) return 1;

    // process requests and print transcripts
    if (!system.process_reqs("requests.txt")) return 1;

    return 0;
}
