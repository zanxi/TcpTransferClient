#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <iostream>
#include <map>
#include <vector>
#include <list>

//#include "libjson.h"

#include "utils/Utils.h"

const std::string create_table = "CREATE TABLE IF NOT EXISTS ";
const std::string create_table_end = ";";//"WITH (OIDS=FALSE,MACS=FALSE);";
//const std::string create_table ="INSERT INTO products " + " VALUES"; 

class SqlDataBase
{
public:     
    static std::string sql_script_f;
    static std::string sql_script_create;
    
    std::vector<std::string>  SortVars(std::vector<std::string> vars);
    std::vector<std::string> SearchIdentVarsAndChange(std::vector<std::string> vars);
    
    static void CreateDataBase(std::string nameDB);
    static void CreateTables();
    static std::string InsertStrokaFieldsNames(std::vector<std::string> columns_);
    static std::string InsertStrokaValues(std::string date_str(),
    std::vector<std::string> columns_Name, std::vector<std::string> columns_);
    static std::string InsertStrokaValuesRandom(std::string date_str(),
          std::vector<std::string> columns_Name, std::vector<std::string> columns_);

    static void TableInsertValue(std::string tab_fn, std::vector<std::string> columns_Name, std::vector<std::string> columns_value);
    static std::string TableInsertValue__(std::string tab_fn, std::vector<std::string> columns_Name, std::vector<std::string> columns_value);
    static void TableInsert(std::string tab_fn = "RMilkSettings");

    static std::string UpdateValues(std::string date_str(),
                                    std::vector<std::string> columns_Name, std::string row);

    static std::string UpdateValues(std::string parameterId, std::string valueId, std::vector<key_value_t> columns_value);    
    static std::string UpdateValues__(std::string tab_fn, std::string parameterId, std::string valueId, std::vector<key_value_t> columns_value);
    static std::string UpdateValues__2(std::string tab_fn, std::string parameterId, std::string valueId, std::vector<std::string> columns_name, std::vector<std::string> columns_value);
    static std::string UpdateValues__2(std::string tab_fn, std::string parameterId, int valueId, std::vector<std::string> columns_name, std::vector<std::string> columns_value);

    static void TableUpdate(std::string rowId, std::string tab_fn = "RMilkSettings");
    static void TablesUpdate();

    static std::string SelectWhere(std::vector<key_value_t> kv);
    static std::string SelectVars(std::vector<std::string> columns_Name, std::string table);
    static std::string SelectValues(std::vector<std::string> columns_Name, std::string table, std::vector<key_value_t> kv);
    static std::string SelectTable(std::string tab_fn);
    static void SelectAllTables();

    static void AllTablesInsert();
     // delete tables
    static void DropTables();
    static void DropDataBase(std::string nameDB);
    static void UseDataBase(std::string nameDB);
};

#endif
