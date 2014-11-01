#include "IndexFile.h"

using namespace std;

int main(int argc, const char** argv){
    string filename = "../instr/prog5.dat";
    IndexFile indexFile;
    indexFile.initialBuild(filename);
    indexFile.search(argv[1]);
    return 0;
}
