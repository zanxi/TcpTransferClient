#ifndef JSON_W_H
#define JSON_W_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <QFile>
#include <QDir>
#include <QMap>
#include <QDebug>
#include <QList>

#include "../utils/Utils.h"



class json_w
{
public:
    json_w();

    static vec_json_prop readJsonFile_all_tables_json(QString pathApp);
    static QMap<QString, vec_json_prop> all_tables_json();

    static QList<QString> readJsonFile_all_tables(QString pathApp);
    static QMap<QString, QList<QString>> all_tables();
    static QMap<QString, QString> form_table(QString table_form_file);
    static QList<QString> form_table2(QString table_form_file);

    static QMap<QString, QString> readJsonFile_form_table(QString pathApp);
    static QList<QString> readJsonFile_form_table2(QString pathApp);
    //static QMap<QString, QList<QString>> all_tables();

    static QJsonDocument loadJson(QString fileName);
    static void saveJson(QJsonDocument document, QString fileName);
    static void Save_to_file(QString pathApp);
    static void CreateJsonVarTab();

};

#endif // JSON_W_H
