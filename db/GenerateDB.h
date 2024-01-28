#ifndef GENERATEDB_H
#define GENERATEDB_H

#include <iostream>

class GenerateDB
{
    public:
    
    static long numColumns; 

    static void CreateFileCsv(std::string pathFolderDB = "vartab2");
    static void CreateFolder(std::string pathFolderDB = "vartab2");
    
    static void CsvGenerateData(std::string tabF, std::vector<std::string> column);
    
    static std::vector<std::string> GenerateVariablesData(int numColumns, std::string pref1, std::string pref2);
    static void CreateFolderDB();

    


};

#endif