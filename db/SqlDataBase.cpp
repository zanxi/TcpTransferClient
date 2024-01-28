#include "../db/SqlDataBase.h"
#include "../Debug/datetime.h"
#include "../csv/csvfile.h"
#include "../json/json_w.h"
#include "../utils/Utils.h"
#include "./Debug/logger.h"

#include "../dataanimals.h"

#include <QDir>


    std::string SqlDataBase::sql_script_f = "sql_script_"+datetime::utcExample()+".sql";
    std::string SqlDataBase::sql_script_create = "";

    //void SqlDataBase::SearchIdentVars(std::vector<std::string> vars)    
    std::vector<std::string> SqlDataBase::SortVars(std::vector<std::string> vars)    
    {        
        std::string tempmin;
        for(int i=0; i<vars.size();i++)
        {    
            int k=0;
            tempmin = vars[i];        
            for(int j=i; j<vars.size();j++)
            {                            
                if(tempmin > vars[j])
                {
                    tempmin=vars[j];
                    k=j;
                }
            }            
            vars[k]=vars[i];
            vars[i]=tempmin;
        }
        return vars;        
    }

    //void SqlDataBase::SearchIdentVars(std::vector<std::string> vars)    
    std::vector<std::string>  SqlDataBase::SearchIdentVarsAndChange(std::vector<std::string> vars)    
    {       
        std::string temp;
        for(int i=0; i<vars.size();i++)
        {   
            temp = vars[i];        
            for(int j=0; j<vars.size();j++)
            {                            
                if(temp == vars[j]&&(i<j))
                {
                    vars[j]+="__"+std::to_string(j);                    
                }
            }                        
        }

        return vars;

    }

    void  SqlDataBase::CreateTables()
    {
         std::vector<std::string> tabFiles = csvfile::ReadFiles();

        map_json_prop_json mjpj;

         for(auto fn:tabFiles)  {
             std::cout<< "sql: " << fn << "\n";
             //map_json_prop tab_ = libjson::Read_Tab(fn);
             vec_json_prop tab_ = json_w::readJsonFile_all_tables_json(QString::fromStdString(fn));//libjson::Read_Tab(fn);
             //std::cout<<fn<< "; size: " << tab_.size() << "\n";
             //logger::WriteLog(QString::fromStdString(fn + "; size: " + std::to_string(tab_.size())));
             
             std::string sql_script = create_table+ " "+ fn + "(";

             DataSystems::Instance().mjpj[QString::fromStdString(fn)] = tab_;

             for (int i=0; i< tab_.size()-1;i++ )
             {
                 if(Str::contains(Str::tolower(tab_[i].key),"time")!=-1)
                 {
                    sql_script += tab_[i].key+" "+"TIMESTAMP"+",\n";
                 }
                 else 
                 {
                    sql_script += tab_[i].key+" "+tab_[i].value+",\n";
                 }
             }            

             /**/


             /*
             for (int i=0; i< tab_.size()-1;i++ )
             {
                 if(Str::contains(Str::tolower(tab_[i].key),"time")!=-1)
                 {
                    sql_script +=  std::string("QString") + std::string(" ") + fn+"_"+ tab_[i].key+";\n";
                 }
                 else 
                 {
                    sql_script += tab_[i].value+" " + fn+"_"+tab_[i].key+";\n";
                 }
             }
             /**/


             //logger::WriteLog(QString::fromStdString(fn));
             //logger::WriteLog(" ----- ");

             //sql_script +=tab_[tab_.size()-1].key + " " + tab_[tab_.size()-1].value+",\n";
             sql_script +=tab_[tab_.size()-1].key + " " + tab_[tab_.size()-1].value+"\n";
             //std::map<std::string,std::string>::iterator it = tab_.begin();
             //sql_script += " CONSTRAINT "+ fn +"_pkey PRIMARY KEY ("+(tab_[0].key)+"))";
             sql_script += " )";
             sql_script += " " + create_table_end;

             //std::cout << sql_script << "\n\n";
             logger::WriteMsg("   ");
             //logger::WriteMsg(sql_script);             
             sql_script_create+=sql_script;

             //DataSystems::Instance().db_sql[QString::fromStdString(fn+":"+sql_script_f)] = QString::fromStdString(sql_script);
             DataSystems::Instance().db_sql[QString::fromStdString(fn)] = QString::fromStdString(sql_script);

             sql_script_f = "create_table_"+fn+".sql";

             logger::WriteSqlScript(sql_script,QDir().currentPath().toStdString() +"/"+ sql_script_f);
             //logger::WriteLog(QDir().currentPath() +"/"+ QString::fromStdString(sql_script_f));
         }
    }

    std::string SqlDataBase::InsertStrokaFieldsNames(std::vector<std::string> columns_)
    {
        int sz = columns_.size();
        std::string sql_script="(";
        for(int i=1; i<sz-1;i++)
        {     
            sql_script += columns_[i]+",\n";                 
        }      
        sql_script += columns_[sz-1];                 
        sql_script += ")\n";       

        return sql_script;                   
    }

    std::string SqlDataBase::InsertStrokaValues(std::string date_str(),
    std::vector<std::string> columns_Name, std::vector<std::string> columns_)
    {
        int sz = columns_.size();
        std::string sql_script="(";
        //sql_script += columns_[0]+",";
        for(int i=1; i<sz-1;i++)
        {   
            if(Str::contains(Str::tolower(columns_Name[i]),"time")!=-1)
                 {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += date_str() + ",";
                 }
                 else 
                 {
                    sql_script += "'"+columns_[i]+ "', ";                 
                 }
        }      
         
        if(Str::contains(Str::tolower(columns_Name[sz-1]),"time")!=-1)
                 {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += date_str();
                 }
                 else 
                 {
                    sql_script += "'"+columns_[sz-1]+ "'";                 
                 } 

        sql_script += ")\n";       
        return sql_script;                   
    }

    std::string SqlDataBase::InsertStrokaValuesRandom(std::string date_str(),
    std::vector<std::string> columns_Name, std::vector<std::string> columns_)
    {
        //srand( (unsigned)time(NULL) );

        int sz = columns_.size();
        std::string sql_script="(";                            
        //sql_script += std::to_string(rand()%10000)+",";
        for(int i=1; i<sz-1;i++)
        {   
            if(Str::contains(Str::tolower(columns_Name[i]),"time")!=-1)
                 {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += date_str() + ",";
                 }
                 else 
                 {
                    sql_script += "'"+std::to_string(rand()%10000)+ "', ";                 
                 }
        }      

         
        if(Str::contains(Str::tolower(columns_Name[sz-1]),"time")!=-1)
                 {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += date_str();
                 }
                 else 
                 {
                    sql_script += "'"+std::to_string(rand()%10000)+ "'";                 
                 } 

        sql_script += ")\n";       

        return sql_script;                   
    }

    void SqlDataBase::TableInsertValue(std::string tab_fn, std::vector<std::string> columns_Name, std::vector<std::string> columns_value)
    {
        std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);

        std::string sql_script = "INSERT INTO " + tab_fn + InsertStrokaFieldsNames(rows_[0])+ " VALUES " +
                                      ((DataSystems::Instance().db_check==DB_check::SQLITE)?
                                      (InsertStrokaValues(datetime::GenerateTime_sqlite,columns_value, columns_value)+ ","):
                                      (InsertStrokaValues(datetime::GenerateTime,columns_value, columns_value)+ ","));


        //DataSystems::Instance().db_sql_table_insert[QString::fromStdString(tab_fn)]=QString::fromStdString(sql_script);
    }

    std::string SqlDataBase::TableInsertValue__(std::string tab_fn, std::vector<std::string> columns_Name, std::vector<std::string> columns_value)
    {
        //logger::WriteMsg("InsertStrokaFieldsNames(columns_Name): "+ InsertStrokaFieldsNames(columns_Name));
        std::string sql_script = "INSERT INTO " + tab_fn + InsertStrokaFieldsNames(columns_Name)+ " VALUES " +
                                 ((DataSystems::Instance().db_check==DB_check::SQLITE)?
                                      (InsertStrokaValues(datetime::GenerateTime_sqlite,columns_value, columns_value)+ ";"):
                                      (InsertStrokaValues(datetime::GenerateTime,columns_value, columns_value)+ ";"));

        return sql_script;
        //DataSystems::Instance().db_sql_table_insert[QString::fromStdString(tab_fn)]=QString::fromStdString(sql_script);
    }


    void SqlDataBase::TableInsert(std::string tab_fn)
    {         
        std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);         
        //std::cout << "TableInsert - Size column: "<< rows_.size() << "\n\n";
        //std::cout << "TableInsert <<<"+tab_fn+">>> - Size Rows: "<< rows_.size() << "\n\n";
        //logger::WriteMsg("TableInsert <<<"+tab_fn+">>> - Size Rows: "+ std::to_string(rows_.size()));
        std::string sql_script = "INSERT INTO " + tab_fn + InsertStrokaFieldsNames(rows_[0]);
        
        if(rows_.size()<2)
        {
            //sql_script += ";";
            //std::cout << ("    ");
            //std::cout << ("<<<<No DATA>>>> <<< RANDOMIZE DATA>>>:" + sql_script);

            //logger::WriteMsg("    ");
            //logger::WriteMsg("<<<<No DATA>>>> <<< RANDOMIZE DATA>>>:");

            sql_script += " VALUES ";
            for(int n=1;n<50;n++){
                    sql_script += (DataSystems::Instance().db_check==DB_check::SQLITE)?
                                      (InsertStrokaValuesRandom(datetime::GenerateTime_sqlite,rows_[0], rows_[0])+ ","):
                                      (InsertStrokaValuesRandom(datetime::GenerateTime,rows_[0], rows_[0])+ ",");
            }
            sql_script += (DataSystems::Instance().db_check==DB_check::SQLITE)?
                                            (InsertStrokaValuesRandom(datetime::GenerateTime_sqlite,rows_[0], rows_[0])+";"):
                                            (InsertStrokaValuesRandom(datetime::GenerateTime,rows_[0], rows_[0])+";");
            logger::WriteMsg(" <<<<<<Random sql Insert>>>>>  ");
            //sql_script_f = "insert_"+tab_fn+".sql";
            sql_script_f = "insert_table_"+tab_fn+".sql";
            //logger::(sql_script);
            logger::WriteSqlScript(sql_script,sql_script_f);

            return;
        }
        sql_script += " VALUES ";
        for(int n=1;n<rows_.size()-1;n++){
            sql_script += (DataSystems::Instance().db_check==DB_check::SQLITE)?
                              (InsertStrokaValues(datetime::GenerateTime_sqlite,rows_[0], rows_[n])+ ","):
                              (InsertStrokaValues(datetime::GenerateTime,rows_[0], rows_[n])+ ",");
        }
        sql_script +=  (DataSystems::Instance().db_check==DB_check::SQLITE)?
                          (InsertStrokaValues(datetime::GenerateTime_sqlite,rows_[0], rows_[rows_.size()-1])+";"):
                         (InsertStrokaValues(datetime::GenerateTime,rows_[0], rows_[rows_.size()-1])+";");
        
        DataSystems::Instance().db_sql_table_insert[QString::fromStdString(tab_fn)]=QString::fromStdString(sql_script);

        logger::WriteMsg("   ");
        //logger::WriteMsg(sql_script);
        sql_script_f = "insert_table_"+tab_fn+".sql";

        logger::WriteSqlScript(sql_script,sql_script_f);
        //logger::WriteLog(QString::fromStdString(sql_script_f));
    }

/*
    void SqlDataBase::TableInsert(std::string tab_fn)
    {
        std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);
        //std::cout << "TableInsert - Size column: "<< rows_.size() << "\n\n";
        std::cout << "TableInsert <<<"+tab_fn+">>> - Size Rows: "<< rows_.size() << "\n\n";
        logger::WriteMsg("TableInsert <<<"+tab_fn+">>> - Size Rows: "+ std::to_string(rows_.size()));
        std::string sql_script = "INSERT INTO " + tab_fn + InsertStrokaFieldsNames(rows_[0]);

        if(rows_.size()<2)
        {
            //sql_script += ";";
            //std::cout << ("    ");
            //std::cout << ("<<<<No DATA>>>> <<< RANDOMIZE DATA>>>:" + sql_script);

            logger::WriteMsg("    ");
            logger::WriteMsg("<<<<No DATA>>>> <<< RANDOMIZE DATA>>>:");

            sql_script += " VALUES ";
            for(int n=1;n<50;n++){
                    sql_script += InsertStrokaValuesRandom(rows_[0], rows_[0])+ ",";
            }
            sql_script +=  InsertStrokaValuesRandom(rows_[0], rows_[0])+";";
            logger::WriteMsg(" <<<<<<Random sql Insert>>>>>  ");
            sql_script_f = "insert_"+tab_fn+".sql";
            //logger::(sql_script);
            logger::WriteSqlScript(sql_script,sql_script_f);

            return;
        }
        sql_script += " VALUES ";
        for(int n=1;n<rows_.size()-1;n++){
            sql_script += InsertStrokaValues(rows_[0], rows_[n])+ ",";
        }
        sql_script +=  InsertStrokaValues(rows_[0], rows_[rows_.size()-1])+";";

        DataSystems::Instance().db_sql_table_insert[QString::fromStdString(tab_fn)]=QString::fromStdString(sql_script);

        logger::WriteMsg("   ");
        //logger::WriteMsg(sql_script);
        sql_script_f = "insert_table_"+tab_fn+".sql";
        logger::WriteSqlScript(sql_script,sql_script_f);
    }

/**/

    std::string SqlDataBase::SelectWhere(std::vector<key_value_t> kv)
    {
        int sz = kv.size();
        std::string sql_script="";
        if(sz<1)return sql_script+=";";



        sql_script += "where ";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {
//            if(Str::contains(Str::tolower(kv[i]),"time")!=-1)
//            {
//                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
//                    sql_script += columns_Name[i] + " = " +date_str() + ",";
//            }
//            else
            {
                    sql_script += kv[i].key + " = " + "'" + kv[i].value + "', ";
            }
        }

//        if(Str::contains(Str::tolower(columns_Name[sz-1]),"time")!=-1)
//        {
//            //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
//            sql_script += columns_Name[sz-1] + " = " + date_str();
//        }
//        else
        {
            sql_script += kv[sz-1].key + " = " + "'" + kv[sz-1].value + "'";
        }

        return sql_script;

    }

    std::string SqlDataBase::SelectVars(std::vector<std::string> columns_Name, std::string table)
    {
        int sz = columns_Name.size();

        std::string sql_script="select ";
        if(sz<1) return sql_script + " * from " + table + " ";
        sql_script += columns_Name[0] + ",";
        for(int i=1; i<sz-1;i++)
        {
            sql_script += columns_Name[i]+", ";
        }
            sql_script += columns_Name[sz-1];


        sql_script +=  " from " + table + " ";
        return sql_script;

    }

    std::string SqlDataBase::SelectValues(std::vector<std::string> columns_Name, std::string table, std::vector<key_value_t> kv)
    {
        std::string sql_script=SelectVars(columns_Name, table)+ SelectWhere(kv);
        std::string sql_script_f = "select_table_.sql";
        logger::WriteSqlScript(sql_script,sql_script_f);

        return sql_script;
    }

    std::string SqlDataBase::SelectTable(std::string tab_fn)
    {
            std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);
            std::string sql_script = SelectValues(rows_[0],tab_fn,{});
            //std::string sql_script = SelectValues(rows_[0],tab_fn,{key_value_t("RecordId","245")});
            //std::string sql_script = SelectValues({},tab_fn,{});
            //logger::WriteMsg("   ");
            sql_script_f = "select_table_"+tab_fn+".sql";
            logger::WriteSqlScript(sql_script,sql_script_f);

        //std::string sql_script=SelectVars(columns_Name, table)+ SelectWhere({});
        return sql_script;

    }

    void SqlDataBase::SelectAllTables()
    {

        std::vector<std::string> tabFiles = csvfile::ReadFiles();

        for(auto tab_fn:tabFiles)
        {
            SelectTable(tab_fn);
        }

        //std::string sql_script=SelectVars(columns_Name, table)+ SelectWhere({});
        //return sql_script;

    }




    std::string SqlDataBase::UpdateValues(std::string date_str(),
                                          std::vector<std::string> columns_Name, std::string rowId)
    {
        int sz = columns_Name.size();
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {
            if(Str::contains(Str::tolower(columns_Name[i]),"time")!=-1)
            {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += columns_Name[i] + " = " +date_str() + ",";
            }
            else
            {
                    sql_script += columns_Name[i] + " = " + "'" + std::to_string(rand()%10000) + "', ";
            }
        }

        if(Str::contains(Str::tolower(columns_Name[sz-1]),"time")!=-1)
        {
            //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
            sql_script += columns_Name[sz-1] + " = " + date_str();
        }
        else
        {
            sql_script += columns_Name[sz-1] + " = " + "'" + std::to_string(rand()%10000) + "'";
        }

        sql_script += " where " + columns_Name[0]+ " = " + "'" + rowId+ "'" + "\n";
        return sql_script;
    }

    /*
    std::string SqlDataBase::UpdateValues__(std::string date_str(),
                                          std::vector<std::string> columns_Name, std::string Idname, std::string rowId)
    {
        int sz = columns_Name.size();
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {
            if(Str::contains(Str::tolower(columns_Name[i]),"time")!=-1)
            {
                    //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
                    sql_script += columns_Name[i] + " = " +date_str() + ",";
            }
            else
            {
                    sql_script += columns_Name[i] + " = " + "'" + std::to_string(rand()%10000) + "', ";
            }
        }

        if(Str::contains(Str::tolower(columns_Name[sz-1]),"time")!=-1)
        {
            //sql_script += "to_timestamp('"+columns_[i]+ "', 'dd-mm-yyyy hh24:mi:ss'),";
            sql_script += columns_Name[sz-1] + " = " + date_str();
        }
        else
        {
            sql_script += columns_Name[sz-1] + " = " + "'" + std::to_string(rand()%10000) + "'";
        }

        sql_script += " where " + Idname+ " = " + "'" + rowId+ "'" + "\n";
        return sql_script;
    }
/**/

    std::string SqlDataBase::UpdateValues(std::string parameterId, std::string valueId, std::vector<key_value_t> columns_value)
    {
        int sz = columns_value.size();
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {

            sql_script += columns_value[i].key + " = " + "'" + columns_value[i].value + "', ";

        }


            sql_script += columns_value[sz-1].key + " = " + "'" + columns_value[sz-1].value + "'";


        sql_script += " where " + parameterId+ " = " + "'" + valueId+ "'" + "\n";
        return sql_script;
    }


    std::string SqlDataBase::UpdateValues__(std::string tab_fn, std::string parameterId, std::string valueId, std::vector<key_value_t> columns_value)
    {
        int sz = columns_value.size();
        qDebug()<<"sz: "<<sz;
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {

            sql_script += columns_value[i].key + " = " + "'" + columns_value[i].value + "', ";

        }

        //qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ";
        sql_script += columns_value[sz-1].key + " = " + "'" + columns_value[sz-1].value + "'";
        //qDebug()<<"------------------------------ ";
        sql_script += " where " + parameterId+ " = " + "'" + valueId+ "'" + "\n";

        sql_script = "UPDATE "+ tab_fn +" SET " +sql_script;

        return sql_script;
    }


    std::string SqlDataBase::UpdateValues__2(std::string tab_fn, std::string parameterId, std::string valueId, std::vector<std::string> columns_name, std::vector<std::string> columns_value)
    {
        int sz = columns_value.size();
        //qDebug()<<"sz: "<<sz;
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {

            sql_script += columns_name[i] + " = " + "'" + columns_value[i] + "', ";

        }

        //qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ";
        sql_script += columns_name[sz-1] + " = " + "'" + columns_value[sz-1] + "'";
        //qDebug()<<"------------------------------ ";
        sql_script += " where " + parameterId+ " = " + "'" + valueId+ "'" + "\n";

        sql_script = "UPDATE "+ tab_fn +" SET " +sql_script;

        return sql_script;
    }

    std::string SqlDataBase::UpdateValues__2(std::string tab_fn, std::string parameterId, int valueId, std::vector<std::string> columns_name, std::vector<std::string> columns_value)
    {
        int sz = columns_value.size();
        //qDebug()<<"sz: "<<sz;
        std::string sql_script="";
        sql_script += "";// columns_Name[0] + " = " +",";
        for(int i=1; i<sz-1;i++)
        {

            sql_script += columns_name[i] + " = " + "'" + columns_value[i] + "', ";

        }

        //qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ";
        sql_script += columns_name[sz-1] + " = " + "'" + columns_value[sz-1] + "'";
        //qDebug()<<"------------------------------ ";
        sql_script += " where " + parameterId+ " = " + std::to_string(valueId)+  "\n";

        sql_script = "UPDATE "+ tab_fn +" SET " +sql_script;

        return sql_script;
    }



    void SqlDataBase::TableUpdate(std::string tab_fn, std::string rowId)
    {
        std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);
        //logger::WriteMsg("TableInsert <<<"+tab_fn+">>> - Size Rows: "+ std::to_string(rows_.size()));
        std::string sql_script = "UPDATE "+ tab_fn +" SET " +
                                         ((DataSystems::Instance().db_check==DB_check::SQLITE)?
                                     UpdateValues(datetime::GenerateTime_sqlite,rows_[0],rowId):
                                                                     UpdateValues(datetime::GenerateTime,rows_[0],rowId));

        //logger::WriteMsg("   ");
        sql_script_f = "update_table_"+tab_fn+".sql";

        logger::WriteSqlScript(sql_script,sql_script_f);
        //logger::WriteLog(QString::fromStdString(sql_script_f));
    }

    void SqlDataBase::TablesUpdate()
    {
        std::vector<std::string> tabFiles = csvfile::ReadFiles();

        for(auto fn:tabFiles)
        {
            TableUpdate(fn,"242");
        }
    }



    void SqlDataBase::AllTablesInsert()
    {         
        std::vector<std::string> tabFiles = csvfile::ReadFiles();

         for(auto fn:tabFiles)  
         {
            TableInsert(fn);
         }        
    }

     // delete tables
    void SqlDataBase::DropTables()
    {         
        std::vector<std::string> tabFiles = csvfile::ReadFiles();
        std::string sql_script="";

         for(auto fn:tabFiles)  
         {
            sql_script = "DROP TABLE "+fn+";"+"\n";
            std::string sql_script_del_all_tables = "drop_table_"+fn+".sql";
            logger::WriteSqlScript(sql_script,sql_script_del_all_tables);
         }
    }

    void SqlDataBase::DropDataBase(std::string nameDB)
    {
         std::string sql_script="";
         sql_script = "DROP DATABASE "+nameDB+";";
         std::string sql_script_del_all_tables = "drop_db.sql";
         logger::WriteSqlScript(sql_script,sql_script_del_all_tables);
    }

    void SqlDataBase::UseDataBase(std::string nameDB)
    {
         std::string sql_script="";
         sql_script = "USE "+nameDB+";";
         std::string sql_script_del_all_tables = "use_db.sql";
         logger::WriteSqlScript(sql_script,sql_script_del_all_tables);
    }

    void SqlDataBase::CreateDataBase(std::string nameDB)
    {
         std::string sql_script="";
         sql_script = "Create DATABASE "+nameDB+";";
         std::string sql_script_del_all_tables = "create_db.sql";
         logger::WriteSqlScript(sql_script,sql_script_del_all_tables);
    }
