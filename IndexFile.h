#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>
#include <cstring>

class IndexFile{
    public:
	IndexFile();
	void initialBuild(std::string);
	std::map<int,int> loadList(std::string);
	void write(std::map<int,int>);
	void search(const char*);
};
