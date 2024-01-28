#include "Utils.h"

  std::string Str::tolower(std::string str)
    {         
        std::string temp = "";
        for(int i=0;i<str.size();i++)
        {
            temp+=std::tolower(str[i]);
        }
        //std::cout<< " lower register stroka: "<<temp << "\n";
        // //logger::WriteMsg(" lower register stroka: "+temp);
        return temp;
    }

    int Str::contains(std::string str, std::string substr)    
    {
       size_t pos = str.find(substr);
       if (pos != std::string::npos) return pos;
       else return -1;
    }
    
    std::string Str::RandomName(int numSymbols, std::string type1, std::string type2)
    {
      // srand( (unsigned)time(NULL) );
      std::string str = "";
      for(int i=0; i<numSymbols;i++)
      {
        //str+=(char)(((rand()%2)==0)?(65+rand()%26):(rand()%2)*(97+rand()%26));
        //str+=(char)(((rand()%2)==0)?(66+rand()%24):(rand()%2)*(98+rand()%24));
        if(((rand()%2)==0))
        {
            str+=(char)(67+rand()%24);            
        }
        else
        {
           str+=(char)(98+rand()%24);            
        }
        //str+=(char)(((rand()%2)==0)?(66+rand()%24):(rand()%2)*(98+rand()%24));
      }
      return type1 + str + type2;
    }

  struct stat sb; 

  int FD::CreateDir(std::string pathFolderDB)
  {
     //logger::WriteMsg("<<<DeleteFiles>>>");

    if (stat(pathFolderDB.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
    {
       //logger::WriteMsgError("Folder <<<"+pathFolderDB+">>> exists !!!!!!!!!!!!");
       return 0;
    }

    std::string mkdir_create = "mkdir -p "+pathFolderDB;
    const int dir_err = system(mkdir_create.c_str());
    if (-1 == dir_err)
    {
        //logger::WriteMsgError("Folder <<<"+pathFolderDB+">>> NOT Created");
        return dir_err;
       
    }

    ////logger::WriteMsg("Folder <<<"+pathFolderDB+">>> was Created!!!!!!");
    return dir_err;
  }

  int FD::DeleteFiles(std::string pathFolderDB)
  {
    if (stat(pathFolderDB.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
    {
       ////logger::WriteMsg("Folder <<<"+pathFolderDB+">>> exists !!!!!!!!!!!!");
       //return 0;
    }
    else
    {
      ////logger::WriteMsgError("Folder <<<"+pathFolderDB+">>> NOT EXISTS ?????!!!!!!");
       return 0;
    }

    //std::string delete_files = "rm -r "+pathFolderDB+"/{*.*}";
    std::string delete_files = "rm -r "+pathFolderDB+"/*";
    //logger::WriteMsg("Cmd: <<<"+delete_files+">>> exists !!!!!!!!!!!!");
    const int dir_err = system(delete_files.c_str());
    if (-1 == dir_err)
    {
        //logger::WriteMsgError("Files from dir <<<"+pathFolderDB+">>> NOT Deleted ??????");
        return dir_err;
       
    }

    //logger::WriteMsg("Files from dir <<<"+pathFolderDB+">>> was Deleted!!!!!!");
    return dir_err;
  }

  int FD::DeleteFiles2(std::string pathFolderDB)
  {
    return 0;
  }

