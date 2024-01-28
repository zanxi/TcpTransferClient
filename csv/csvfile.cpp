#include "../csv/csvfile.h"

  
std::vector<std::string> csvfile::ReadFiles(const char* fn)
{
   std::vector<std::string> temp;
   DIR *dpdf;
   struct dirent *epdf;

   dpdf = opendir(fn);
if (dpdf != NULL){
   while (epdf = readdir(dpdf)){       
       if (!epdf->d_name || epdf->d_name[0] != '.'){
              //printf("Filename: %s \n",epdf->d_name);
              temp.push_back(epdf->d_name);           
       }
      // std::cout << epdf->d_name << std::endl;
   }
}
closedir(dpdf);
//std::cout<<" ************** End Read files ********************* "  << '\n';
   return temp;
}

	   
       void csvfile::Read(string fname)
       {
           //string fname="RIndication";
	      //cout<<"Enter the file name: "<<fname<<"\n";
		  map<int,vector<string>> tab_RIndication;
	
	vector<vector<string>> content;
	vector<string> row;
	string line, word;
 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		int w=0;
		while(getline(file, line))
		{
			row.clear(); 
			stringstream str(line); 
			vector<string> vec;
			while(getline(str, word, ';'))
            {
				vec.push_back(word);				
                cout<<" | "<<word;
            }			
            cout<<"\n";
			tab_RIndication.insert ( std::pair<int,vector<string>>(w,vec) );			
			w++;
			//content.push_back(row);
		}
	}
	else
	{

	}
 
   /*
	for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{
			cout<<content[i][j]<<" ";
		}
		cout<<"\n";
	}
    /**/
 
	//return 0;
       }

	   map<int,vector<string>> csvfile::Read_TabMap(string fname)
       {
           //string fname="RIndication";
	       //cout<<"Enter the file name: "<<fname<<"\n";
		   map<int,vector<string>> tab_RIndication;
	
	       vector<vector<string>> content;
	       vector<string> row;
	       string line, word;
 
	       fstream file ("./vartab/"+fname, ios::in);
		   //cout<<"\n ********  Read_TabMap | "<<("./vartab/"+fname)<<"\n";
           //logger::WriteMsg("class csvfile-> method <<<Read_TabMap>>> :  ./vartab/"+fname);
	       if(file.is_open())
	       {
		     int w=0;
		     while(getline(file, line))
		     {
			     row.clear(); 
			     stringstream str(line); 
			     vector<string> vec;
			     while(getline(str, word, ';'))
                 {
				     vec.push_back(word);				
                     //cout<<" | "<<word;
                 }			
                 //cout<<"\n";
			     tab_RIndication.insert ( std::pair<int,vector<string>>(w,vec) );			
			     w++;
				 //logger::WriteMsg(fname+" "+std::to_string(w));
				 //logger::WriteMsg(" &&&&&&&&&&&&&&&&&&&&& class csvread-> method Read_TabMap( " + fname+" "+std::to_string(w));
			     //content.push_back(row);
		    }
     		return tab_RIndication;
		   
	      }
	      else
	      {

		     cout<<"Could not open the file\n";
		     return tab_RIndication;
	      }
        return tab_RIndication;
	   }
 
   
