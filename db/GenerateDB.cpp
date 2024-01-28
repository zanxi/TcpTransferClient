#include <unistd.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#include "GenerateDB.h"
#include "../Debug/logger.h"
#include "../utils/Utils.h"

long GenerateDB::numColumns=50;

void GenerateDB::CreateFileCsv(std::string pathFolderDB)
{
    
}

void GenerateDB::CreateFolder(std::string pathFolderDB)
{      
    
}

std::vector<std::string> GenerateDB::GenerateVariablesData(
    int numColumns, 
    std::string pref1, 
    std::string pref2)
{
    std::vector<std::string> temp;
    for(int i=0;i<numColumns;i++)
       {
           std::string r_ = 
           Str::RandomName(5,
           pref1+std::to_string(i)+"_",pref2);
           if(rand()%20==0)r_+="Time";
           temp.push_back(r_);
           //logger::WriteMsg("("+std::to_string(numColumns)+") : "+r_);
           //std::cout<<"("<<(i+40)<<") - "<< (char)(i+40)<<" | ";
       }
       return temp;
}

void GenerateDB::CsvGenerateData(std::string tabF, std::vector<std::string> column)
{    
    std::ofstream out;        
    out.open(tabF,std::ios::app);
    //ou+t.open(fn);
    if(out.is_open())
    {       
        if(Str::contains(Str::tolower(column[0]),"time")!=-1)
            {  
                logger::WriteMsg(
                    "Warning - First var in tab <<<<"+tabF+">>>> -> TIME");
            } 

        std::string cols = ""; 
        for(int i=0; i<column.size();i++)
        {
            cols += column[i]+";";
        }
        //cols += column[column.size()-1]+";";        
        //out<< cols <<std::endl;//<<"\r\n";        
        out<< cols <<"\r\n";        

        int nRows = 1+(rand()%150);
        std::string dataRow = ""; 
        for(int j=0;j<nRows;j++)
        {
        std::string dataRow = ""; 
        

                 if(Str::contains(Str::tolower(column[0]),"time")!=-1)
                 {  
                    dataRow += datetime::GenerateTime()+";"; 
                 }
                 else 
                 {
                    dataRow += std::to_string((j+1))+";";
                 }        
        
        for(int i=1; i<column.size();i++)
        {
            dataRow += std::to_string(rand()%20000)+";";
        }
        //cols += column[column.size()-1]+";";
        //out<< dataRow<<std::endl;//<<"\r\n"; 
        out<< dataRow<<"\r\n"; 
        //dataRow += "\n";
        }
        //out<< dataRow<<"\n";        
        
        
    }
    out.close();
}

void GenerateDB::CreateFolderDB()
{

      std::string folder = "./vartab/";

      for(int i=0;i<15;i++)
      {
        CsvGenerateData(
            folder+"tzz_"+std::to_string(i)+"_zij",
            //Str::RandomName(5,"tzz_"+std::to_string(i),"_zij"),
            //"SvodkaData",
            GenerateVariablesData(((i+1)*(1+rand()%10)),
                "Disjj_","_Exz")
        );
      }
 
      /*
        CsvGenerateData(
            folder+"SvodkaData",
            GenerateVariablesData(10,"Data_","_Experiment"));
        
        CsvGenerateData(folder+"Remission",GenerateVariablesData(100,"Mi","_Remission"));
        CsvGenerateData(folder+"Annigilation",GenerateVariablesData(200,"Sub","_Pion"));
        CsvGenerateData(folder+"ActionTime",GenerateVariablesData(130,"Sub","_Recom"));
        CsvGenerateData(folder+"DevPart",GenerateVariablesData(50,"NML","_Particles"));
        CsvGenerateData(folder+"Material",GenerateVariablesData(10,"End_","_Work"));
        //CsvGenerateData("./vartab2/Material",GenerateVariablesData(80,"","_"));
        /**/
}
