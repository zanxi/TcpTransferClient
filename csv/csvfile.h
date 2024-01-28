#ifndef CSVFILE_H
#define CSVFILE_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <map>


using namespace std;

class csvfile
{
    public:

       static std::vector<std::string> ReadFiles(const char* fn = "./vartab/");	   
       static void Read(string fname="./tables/RIndication");
	   static map<int,vector<string>> Read_TabMap(string fname="RMilkSettings");
 
   
};

#endif
