#include "IndexFile.h"
#include "Record.cpp"
#ifndef BUFFSIZE 
#define BUFFSIZE 20
#endif


using namespace std;

IndexFile::IndexFile() {

}

void IndexFile::initialBuild(string filename){
    fstream RawFile(filename.c_str(), fstream::in), BinFile("prog5.bin", fstream::out | fstream::binary);
    char * buffer = new char[BUFFSIZE];
    char blank[] = "blank  ";
    Record record;
    map<int, int> indexList;
    if(RawFile.is_open()){
	RawFile.getline(buffer, BUFFSIZE); //needs to be broken up then reinterpret_cast
	int size = record.key = atoi(buffer);
	memcpy(record.str, blank, strlen(blank) + 1);
	record.count = 0;
	record.cost = 0.0;
	BinFile.write(reinterpret_cast<char *>(&record), sizeof(record));
	for(int i = 1; i <= size; i++){
	    RawFile >> record.key >> record.str >> record.count >> record.cost;
	    BinFile.write(reinterpret_cast<char *>(&record), sizeof(record)); 
	    //cout << "record added\n";
	    indexList[record.key] = i;
	}
        write(indexList);
	cout << size << " records added"<<endl;
        RawFile.close();
	BinFile.close();
    } else
	cout << "error opening file in initialIndexFileBuild"<<endl;;
}

map<int,int> IndexFile::loadList(string filename){
    fstream OGFile;
    OGFile.open(filename.c_str(), fstream::in | fstream::binary);
    int key, rrn;
    map<int, int> indexList;
    if(OGFile.is_open()){
	while(!OGFile.eof()){
	   OGFile.read(reinterpret_cast<char *>(&key), sizeof(key));
	   OGFile.read(reinterpret_cast<char *>(&rrn), sizeof(rrn));
	   indexList[key] = rrn;
	}	
        OGFile.close();
    } else
	cout << "error opening file" << endl;
    return indexList;
}

void IndexFile::write(map<int,int> indexList){
    fstream output;
    output.open("prog5.idx", fstream::out | fstream::binary);
    if(output.is_open()){
        for( map<int, int>::iterator it = indexList.begin(); it != indexList.end(); ++it ){
	    int first = it->first, second = it->second;
	    output.write(reinterpret_cast<const char *>(&first), sizeof(first));
	    output.write(reinterpret_cast<const char *>(&second), sizeof(second));
	}
    } else
	cout << "error opening file in indexBuilder::write\n";
    output.close();
}




void IndexFile::search(const char* strKey){

    fstream BinFile;
    map<int,int> indexList =loadList("../instr/prog5.dat");

    //open original file then get the header size
    BinFile.open("./prog5.bin", fstream::in | fstream::binary);
    char * buffer = new char[BUFFSIZE+1];

    //finds record position, reads in record
    Record record;
    int rrn = indexList[atoi(strKey)];//auto bin search. may need manual search of array from up there^^
    BinFile.seekg(rrn * sizeof(record));
    BinFile.read(reinterpret_cast<char *>(&record), sizeof(record));

    cout << record.key << " " << record.str << " " << record.count << " " << record.cost << endl;

    BinFile.close();
    delete[] buffer;
}
