#include "database.h"
#include "dataanimals.h"
#include "Debug/logger.h"
#include "db/SqlDataBase.h"
#include "csv/csvfile.h"

#include <QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>
#include <QJsonArray>
#include <QSqlRecord>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    columns_Name_insert_temp.push_back("");
    columns_value_insert_temp.push_back("");

    columns_Name_update_temp.push_back("");
    columns_value_update_temp.push_back("");

//    key_value_t kv;
//    kv.key="";
//    kv.value="";
//    columns_value_update.push_back(kv);

    this->connection_name = "connection"+QString::number(DataSystems::Instance().db_connection_counter++);
    db_open = Open();
}

DataBase::DataBase(const QString& sqliteEmpty, QObject *parent) : QObject(parent)
{
    columns_Name_insert_temp.push_back("");
    columns_value_insert_temp.push_back("");

    columns_Name_update_temp.push_back("");
    columns_value_update_temp.push_back("");

    this->connection_name = "connection"+QString::number(DataSystems::Instance().db_connection_counter++);
    db_open_sqlite = OpenSQLite();
}


DataBase::~DataBase()
{

    db.close();
    QSqlDatabase::removeDatabase(connection_name);
    //QSqlDatabasePrivate::removeDatabase(connection_name);
    logger::WriteMsg(" ---------- база данных ------ "+connection_name.toStdString()+" удалена");
    qDebug()<<" ---------- база данных ------ "+connection_name+" удалена";
}

void DataBase::WriteLog(QString msg)
{
    log+=QString(" | ")+QString::fromStdString(datetime::utcExample())+"| message: "+msg+"  "+"\n";
}

bool DataBase::Open()                                          //  метод подключения к БД.   Если нашей бд не существовало, она будет создана и подключена.
{
    if(QSqlDatabase::contains(connection_name)) {
       db = QSqlDatabase::database(connection_name);
       logger::WriteMsg("соедиенние: |"+connection_name.toStdString()+"| действует" );
    }
    else
    {
       logger::WriteMsg("соедиенние: |"+connection_name.toStdString()+"| отсутствует" );
    switch(DataSystems::Instance().db_check)
    {
        case DB_check::SQLITE:
        {

            logger::WriteMsg("----------- Initialize -------- QSQLITE -------------");
            db = QSqlDatabase::addDatabase("QSQLITE", connection_name                                           );
            db.setDatabaseName(DataSystems::Instance().db_name);
            logger::WriteMsg(QString("Подключение к драйверу SQLITE; база данных <<<" + DataSystems::Instance().db_sqlite_file +  ">>>").toStdString());
            //logger:WriteLog("Подключение к драйверу SQLITE; база данных <<<" + DataSystems::Instance().db_sqlite_file);
            break;
        }
         case DB_check::PGSQL:
         {
            logger::WriteMsg("----------- Initialize -------- QPSQL -------------");
            db = QSqlDatabase::addDatabase("QPSQL", connection_name);              //  драйвер
            db.setHostName(DataSystems::Instance().db_host);              // или  localhost
            db.setPort(DataSystems::Instance().db_port);
            db.setDatabaseName(DataSystems::Instance().db_name);       //  сперва подключаемся к встроенной бд, что-бы иметь возможность создать нашу.
            db.setUserName(DataSystems::Instance().db_login);
            db.setPassword(DataSystems::Instance().db_password);            
            logger::WriteMsg(QString("Подключение к драйверу PostgreSQL; база данных <<<" + DataSystems::Instance().db_name +  ">>>").toStdString());
            logger::WriteLog("Подключение к драйверу PostgreSQL; база данных <<<" + DataSystems::Instance().db_name +  ">>>");
            break;
         }
    }
    }
    //bool ret = db.open();
    return db.open();
}

bool DataBase::OpenSQLite()                                          //  метод подключения к БД.   Если нашей бд не существовало, она будет создана и подключена.
{
    if(QSqlDatabase::contains(connection_name)) {
       db = QSqlDatabase::database(connection_name);
       logger::WriteMsg("соедиенние: |"+connection_name.toStdString()+"| действует" );
    }
    else
    {
       logger::WriteMsg("соедиенние: |"+connection_name.toStdString()+"| отсутствует" );

            logger::WriteMsg("----------- Initialize -------- QSQLITE -------------");
            db = QSqlDatabase::addDatabase("QSQLITE", connection_name                                           );
            db.setDatabaseName(DataSystems::Instance().db_sqlite_file_autorization);
            logger::WriteMsg(QString("Подключение к драйверу SQLITE; база данных <<<" + DataSystems::Instance().db_sqlite_file +  ">>>").toStdString());
            //logger:WriteLog("Подключение к драйверу SQLITE; база данных <<<" + DataSystems::Instance().db_sqlite_file);
    }
    //bool ret = db.open();
    return db.open();
}


bool DataBase::isOpen()
{
    QSqlDatabase db=QSqlDatabase::database("createDb");
    return db.isOpen();
}


void DataBase::FillValue()                  //   метод вставки строки в таблицу qual_table ,  принимает QVariantList  т.к.  значения в таблицах могут быть разных типов.
{
         std::vector<std::string> tabFiles = csvfile::ReadFiles();
         //std::string sql_script="";

         for(auto fn:tabFiles)
         {
               inserIntoTableSqlScript(QString::fromStdString("insert_table_"+fn+".sql"));
               logger::WriteMsg(QString::fromStdString("insert_table_"+fn+".sql").toStdString());
               logger::WriteLog(QString::fromStdString("insert_table_"+fn+".sql"));
               //return;
         }
}

bool DataBase::inserIntoTableSqlScript(QString file_sql)                  //   метод вставки строки в таблицу qual_table ,  принимает QVariantList  т.к.  значения в таблицах могут быть разных типов.
{
         QFile file(file_sql);
         bool ret = file.open(QFile::ReadOnly);
         if (ret) {
               QString sql_script = QString(file.readAll());
               bool status = sql_exec(sql_script);
               if(!status) {
                   logger::WriteLog("Error Insert data to tables sql script: XXXXXXXXXXXXXXXXX ");
                   logger::WriteLog(file_sql);
               }
               else
               {
                   //logger::WriteLog("Excellent sql script: !!!!!!!!!!!!!!!!!! ");
               }
               file.close();
         }
         else return true;


}


bool DataBase::inserIntoTable2(QString table, const QList<QString>  columns, const QVariantList  &data)                  //   метод вставки строки в таблицу qual_table ,  принимает QVariantList  т.к.  значения в таблицах могут быть разных типов.
{
    QSqlQuery query;

    QString vars = columns[0];
    for(int i=1; i<columns.count();i++)vars+=", "+ columns[i];
    QString insert="INSERT INTO " + table + " ( " + vars+ " ) " "VALUES ";

    QString values = data[0].toString();
    for(int i=1; i<data.count();i++)vars+=", "+ data[i].toString();

    insert+= " ( " + values+ ")";

    //query.prepare( "INSERT INTO " + table + " ( p00,  p01, p02 ) "            //   готовим запрос
    //                                       "VALUES  (?,?,?)");

    for(int i=1; i<data.count();i++)query.addBindValue(data[i].toString());
    query.addBindValue(data[1].toString());

    query.prepare(insert);

    if(!query.exec()){                                                                       //  выполняем запрос методом exec()
        qDebug() << "error insert into " << table;
        qDebug() << query.lastError().text();                                       //  в этом методе предусмотрен вывод информации об ошибках.
        return false;
    } else {
        return true;
    }

    //QSqlDatabase::removeDatabase(DataSystems::Instance().conn_name);
    //QSqlDatabase::removeDatabase(DataSystems::Instance().db_name);
}

void DataBase::createTables()
{
    std::vector<std::string> tabFiles = csvfile::ReadFiles();
    //std::string sql_script="";

    for(auto fn:tabFiles)
    {
        CreateDataBase(QString::fromStdString("create_table_"+fn+".sql"));
    }
}

void DataBase::DropTables()
{
    std::vector<std::string> tabFiles = csvfile::ReadFiles();

    for(auto fn:tabFiles)
    {
        DropTable(QString::fromStdString("drop_table_"+fn+".sql"));
    }
}

void DataBase::UpdateTables()
{
    std::vector<std::string> tabFiles = csvfile::ReadFiles();

    for(auto fn:tabFiles)
    {
        //UpdateTable(QString::fromStdString("update_table_"+fn+".sql"));
    }

    UpdateTable(QString::fromStdString("update_table_RIndication.sql"));
}


void DataBase::UpdateTable(QString file_sql)
{
    QFile file(file_sql);
    bool ret = file.open(QFile::ReadOnly);
    if (ret) {
        QString sql_script = QString(file.readAll());
        sql_script.remove("-");
        bool status = sql_exec(sql_script);
        if(!status) {
                   logger::WriteLog("Error Update sql script: XXXXXXXXXXXXXXXXX ");
                   logger::WriteLog(file_sql);
        }
        else
        {
            logger::WriteLog("Excellent Update sql script: !!!!!!!!!!!!!!!!!! ");
        }
        file.close();
    }
    else return;
}


void DataBase::DropTable(QString file_sql)
{
    QFile file(file_sql);
    bool ret = file.open(QFile::ReadOnly);
    if (ret) {
        QString sql_script = QString(file.readAll());
        bool status = sql_exec(sql_script);
        if(!status) {
            logger::WriteLog("Error Delete sql script: XXXXXXXXXXXXXXXXX ");
            logger::WriteLog(file_sql);
        }
        else
        {
            //logger::WriteLog("Excellent sql script: !!!!!!!!!!!!!!!!!! ");
        }
        file.close();
    }
    else return;
}

void DataBase::DropDB(QString file_sql)
{
    QFile file(file_sql);
    bool ret = file.open(QFile::ReadOnly);
    if (ret) {
        QString sql_script = QString(file.readAll());
        sql_exec(sql_script);
        file.close();
    }
    else return;
}

void DataBase::DropDataBase(QString nameDB)
{
    //std::string sql_script="";
    DropDB(QString::fromStdString("drop_db.sql"));

}

void DataBase::UseDataBase(QString nameDB)
{
    sql_exec(QString("USE database "+nameDB+";"));

}

bool DataBase::CreateDataBase(QString file_sql)
{
    QFile file(file_sql);
    bool ret = file.open(QFile::ReadOnly);
    if (ret) {        
        QString sql_script = QString(file.readAll());
        bool status = sql_exec(sql_script);
        if(!status) {
            logger::WriteLog("Error Executive Create sql script: XXXXXXXXXXXXXXXXX ");
            logger::WriteLog(file_sql);
        }
        else
        {
            logger::WriteLog("Excellent executive create sql script: !!!!!!!!!!!!!!!!!! ");
        }
        file.close();
    }
    else return true;
}

bool DataBase::sql_exec(QString sql_script, QString comment)
{
        // QSqlDatabase db=QSqlDatabase::database(DataSystems::Instance().conn_name);
        QSqlQuery *query = new QSqlQuery(db);
        if(!query->exec(sql_script)) {
                 logger::WriteMsg(
                                 QString("comment: "+comment+"; Error sql script: XXXXXXXXXXXXXXXXX "+
                                 comment+
                                 " --- "+
                                 sql_script +
                                 " ----> error ").toStdString());
                 logger::WriteMsg("Error sql: "+query->lastError().text().toStdString());
                 logger::WriteLog("Error sql: "+query->lastError().text());
                 delete query;
                return false;
        }
        else
        {
                delete query;
                return true;
        }
}

QSqlQuery* DataBase::sql_exec2(QString sql_script, QString comment)
{
        // QSqlDatabase db=QSqlDatabase::database(DataSystems::Instance().conn_name);
//        /qDebug()<<sql_script;
        QSqlQuery *query = new QSqlQuery(db);
        if(!query->exec(sql_script)) {
                logger::WriteMsg(
                    QString("Error sql script: XXXXXXXXXXXXXXXXX "+
                            comment+
                            " --- "+
                            sql_script +
                            " ----> error ").toStdString());
                return nullptr;
        }
        else
        {
                return query;
        }        
}

QString DataBase::GetLog()  {  return log;  }

QString DataBase::insert_add(QString tab, QString var_type_add, QString val_add)
{
        columns_Name_insert_temp.push_back(var_type_add.toStdString());
        columns_value_insert_temp.push_back(val_add.toStdString());

        QString sql_insert = QString::fromStdString(SqlDataBase::TableInsertValue__(tab.toStdString(),columns_Name_insert_temp,columns_value_insert_temp));

        return sql_insert;
}

QString DataBase::update_add(QString tab, QString parameterId, QString valueId, QString variable_add, QString val_add)
{

        columns_Name_update_temp.push_back(variable_add.toStdString());
        columns_value_update_temp.push_back(val_add.toStdString());
        //qDebug()<<"(1): "<<columns_Name_update_temp.size()<<"; (2): "<<columns_value_update_temp.size();

        QString sql_update = QString::fromStdString(
            SqlDataBase::UpdateValues__2(tab.toStdString(),
                                                 parameterId.toStdString(),
                                                 valueId.toStdString(),
                                                 columns_Name_update_temp,
                                                 columns_value_update_temp));

        return sql_update;

}

QString DataBase::update_add(QString tab, QString parameterId, int valueId, QString variable_add, QString val_add)
{

        columns_Name_update_temp.push_back(variable_add.toStdString());
        columns_value_update_temp.push_back(val_add.toStdString());
        //qDebug()<<"(1): "<<columns_Name_update_temp.size()<<"; (2): "<<columns_value_update_temp.size();

        QString sql_update = QString::fromStdString(
            SqlDataBase::UpdateValues__2(tab.toStdString(),
                                         parameterId.toStdString(),
                                         valueId,
                                         columns_Name_update_temp,
                                         columns_value_update_temp));

        return sql_update;

}

/*
void SqlDataBase::TableInsertValue(std::string tab_fn, std::vector<std::string> columns_Name, std::vector<std::string> columns_value)
{
        std::map<int, std::vector<std::string>> rows_ = csvfile::Read_TabMap(tab_fn);

        std::string sql_script = "INSERT INTO " + tab_fn + InsertStrokaFieldsNames(rows_[0])+ " VALUES " +
                                 ((DataSystems::Instance().db_check==DB_check::SQLITE)?
                                      (InsertStrokaValues(datetime::GenerateTime_sqlite,columns_value, columns_value)+ ","):
                                      (InsertStrokaValues(datetime::GenerateTime,columns_value, columns_value)+ ","));


        //DataSystems::Instance().db_sql_table_insert[QString::fromStdString(tab_fn)]=QString::fromStdString(sql_script);
}

/**/
