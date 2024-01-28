#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

#include <iostream>
#include <map>
#include <vector>
#include <list>


#include "../utils/Utils.h"

#define DB_NAME   "vim2"

class DataBase : public QObject
{
    Q_OBJECT    
public:
    //DataBase(QObject *parent = 0, QString connectionname = "vim3");
    DataBase(QObject *parent = 0);
    DataBase(const QString &sqliteEmpty, QObject *parent = 0);

    bool inserIntoTableSqlScript(QString table);          // публичный метод - вставить в таблицу
    void FillValue();
    bool inserIntoTable2(QString table, const QList<QString>  clumns, const QVariantList &data);          // публичный метод - вставить в таблицу

    ~DataBase();
    void createTables();                  //   создать таблицу
    bool Open();
    bool OpenSQLite();
    bool isOpen();
    bool CreateDataBase(QString table);
    void DropTables();
    void UpdateTables();

    QString UpdateParameter(QString parameter, QString value)
        {
            QString sql = "INSERT OR REPLACE INTO [LocalSettings] ( [ParameterName], [ParameterValue]) "
                          "VALUES("
                          "'"+parameter+"',"
                          "'"+ value +"')";
            return sql;

        };

     QString GetParameter(QString parameter)
        {

            QString commandText = "select parametername,parametervalue from  LocalSettings WHERE ParameterName='" + parameter + "';";
            //QString commandText = "select * from  LocalSettings WHERE ParameterName='" + parameter + "';";
            //qDebug()<<commandText;
            return commandText;
        };

    void UpdateTable(QString file_sql);
    void DropTable(QString table);
    void DropDataBase(QString nameDB);
    void UseDataBase(QString nameDB);
    bool StatusOpen(){ return db_open; };
    bool StatusOpenSQLite(){ return db_open_sqlite; };
    QString GetLog();
    void WriteLog(QString msg);

    QSqlDatabase   db;                         // Сам объект базы данных
    bool sql_exec(QString nameDB, QString comment="");
    QSqlQuery* sql_exec2(QString nameDB, QString comment="");

    QString insert_add(QString tab, QString variable, QString val);
    QString update_add(QString tab, QString parameterId, QString valueId, QString variable, QString val);
    QString update_add(QString tab, QString parameterId, int valueId, QString variable, QString val);

    //std::string sql_insert;
    //std::string sql_update;


private:
    //QSqlDatabase   db;                         // Сам объект базы данных


    bool db_open = false;
    bool db_open_sqlite = false;
    void DropDB(QString nameDB);
    //bool sql_exec(QString nameDB, QString comment="");

    QString log="";
    QString connection_name="";

    std::string tab_fn;
    std::vector<std::string> columns_Name_insert_temp;
    std::vector<std::string> columns_value_insert_temp;


    //std::vector<key_value_t> columns_value_update;
    std::vector<std::string> columns_Name_update_temp;
    std::vector<std::string> columns_value_update_temp;


};

#endif   // DATABASE_H
