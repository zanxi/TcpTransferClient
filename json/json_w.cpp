#include "json_w.h"
#include "../csv/csvfile.h"

json_w::json_w()
{

}

vec_json_prop json_w::readJsonFile_all_tables_json(QString pathApp)
{
    vec_json_prop vals;
    QFile file;
    file.setFileName(QDir::currentPath()+ "/tables/" + pathApp+".json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return vals;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return vals;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    QJsonValue jsonVal;
    QTextStream textStream(stdout);

    QJsonArray jsonArray;
    jsonArray = jsonObj[pathApp].toArray();
    foreach(const QJsonValue & value, jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject obj = value.toObject();
            foreach(const QString& key, obj.keys()) {
                QJsonValue value = obj.value(key);
                key_value_t kv;
                kv.key = QString(key).toStdString();
                kv.value = QString(value.toString()).toStdString();
                vals.push_back(kv);
            }
        }
    }
    return vals;
}

QMap<QString, vec_json_prop> json_w::all_tables_json()
{

    QMap<QString, vec_json_prop> temp_all_tables;

    QString pathApp = QDir::currentPath()+ "/tables/";
    qDebug()<<" Read Folder "<< (QDir::currentPath()+ "/tables/")<<"\n";
    QDir directory(pathApp);
    directory.setFilter(QDir::Files);
    QFileInfoList listfiles = directory.entryInfoList();
    for(QFileInfo qf: listfiles){
        //QDir::currentPath()+ "/tables/e.json";
        QString n = qf.fileName();
        QString nTab = n.remove(n.length()-5,n.length());
        vec_json_prop vals = readJsonFile_all_tables_json(nTab);
        temp_all_tables[nTab] = vals;
    }
    return temp_all_tables;
}




QList<QString> json_w::readJsonFile_all_tables(QString pathApp)
{
    QList<QString> vals;
    //qDebug() << "Read Json File:";

    //qDebug()<<"******** //1. **********"<<"\n";
    //1. Open the QFile and write it to a byteArray and close the file
    QFile file;
    //file.setFileName("./tables/RFeedSettings.json");
    //qDebug()<<QDir::currentPath()+ "/tables/e.json"<<"\n";

    file.setFileName(QDir::currentPath()+ "/tables/" + pathApp+".json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return vals;
    }



    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return vals;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    //qDebug()<<"******************"<<"\n";

    //4. Now picking the jsonValues and printing them out or do what ever you need
    QJsonValue jsonVal;
    QTextStream textStream(stdout);

    //qDebug()<<"******************"<<"\n";
    QJsonArray jsonArray;
    jsonArray = jsonObj[pathApp].toArray();
    //jsonArray = jsonObj["Phone numbers"].toArray();
    //logger::WriteMsg(QString(" ************** " + pathApp + " **********************").toStdString());

    foreach(const QJsonValue & value, jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject obj = value.toObject();
            foreach(const QString& key, obj.keys()) {
                QJsonValue value = obj.value(key);
                //qDebug() << "Key = " << key << ", Value = " << value.toString();
                //vals.append(value.toString());
                vals.append(key);
            }
        }
    }
    return vals;
}

QMap<QString, QList<QString>> json_w::all_tables()
{

    QMap<QString, QList<QString>> temp_all_tables;

    QString pathApp = QDir::currentPath()+ "/tables/";
    qDebug()<<" Read Folder "<< (QDir::currentPath()+ "/tables/")<<"\n";
    QDir directory(pathApp);
    directory.setFilter(QDir::Files);
    QFileInfoList listfiles = directory.entryInfoList();
    for(QFileInfo qf: listfiles){
        //QDir::currentPath()+ "/tables/e.json";
        QString n = qf.fileName();
        QString nTab = n.remove(n.length()-5,n.length());        
        QList<QString> vals = readJsonFile_all_tables(nTab);
        temp_all_tables[nTab] = vals;        
    }
    return temp_all_tables;
}

QMap<QString, QString> json_w::form_table(QString table_form_file)
{

    QMap<QString, QString> temp_form_table;

    QString pathApp = QDir::currentPath()+ "/setting_forms/"+table_form_file;

    qDebug()<<" Read json file:  "<< (QDir::currentPath()+ "/setting_forms/"+table_form_file)<<"\n";
    QFileInfo qf(pathApp);
    if(!qf.exists())
    {
        //qDebug()<<" Read json file:  "<< (QDir::currentPath()+ "/setting_forms/"+table_form_file)<<"\n";
        return temp_form_table;

    }
        QString n = qf.fileName();
        QString nTab = n.remove(n.length()-5,n.length());
        //qDebug()<<qf.filePath()<<" | "<< nTab<<"\n";
        temp_form_table = readJsonFile_form_table(nTab);


    return temp_form_table;

}

QList<QString> json_w::form_table2(QString table_form_file)
{

    QList<QString> temp_form_table;

    QString pathApp = QDir::currentPath()+ "/setting_forms/"+table_form_file;

    qDebug()<<" Read json file:  "<< (QDir::currentPath()+ "/setting_forms/"+table_form_file)<<"\n";
    QFileInfo qf(pathApp);
    if(!qf.exists())
    {
        //qDebug()<<" Read json file:  "<< (QDir::currentPath()+ "/setting_forms/"+table_form_file)<<"\n";
        return temp_form_table;

    }
    QString n = qf.fileName();
    QString nTab = n.remove(n.length()-5,n.length());
    //qDebug()<<qf.filePath()<<" | "<< nTab<<"\n";
    temp_form_table = readJsonFile_form_table2(nTab);


    return temp_form_table;

}



QMap<QString, QString> json_w::readJsonFile_form_table(QString pathApp)
{
    QMap<QString, QString> temp;

    QFile file;
    //file.setFileName("./tables/RFeedSettings.json");
    //qDebug()<<QDir::currentPath()+ "/tables/e.json"<<"\n";

    file.setFileName(QDir::currentPath()+ "/setting_forms/" + pathApp+".json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return temp;
    }



    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return temp;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    //qDebug()<<"******************"<<"\n";

    //4. Now picking the jsonValues and printing them out or do what ever you need
    QJsonValue jsonVal;
    QTextStream textStream(stdout);

    //qDebug()<<"******************"<<"\n";
    QJsonArray jsonArray;
    jsonArray = jsonObj[pathApp].toArray();
    //jsonArray = jsonObj["Phone numbers"].toArray();
    //logger::WriteMsg(QString(" ************** " + pathApp + " **********************").toStdString());

    foreach(const QJsonValue & value, jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject obj = value.toObject();
            foreach(const QString& key, obj.keys()) {
                QJsonValue value = obj.value(key);
                qDebug() << "Key = " << key << ", Value = " << value.toString();
                //vals.append(value.toString());
                temp[key]=value.toString();
            }
        }
    }


    return temp;
}


QList<QString> json_w::readJsonFile_form_table2(QString pathApp)
{
    QList<QString> temp;

    QFile file;
    //file.setFileName("./tables/RFeedSettings.json");
    //qDebug()<<QDir::currentPath()+ "/tables/e.json"<<"\n";

    file.setFileName(QDir::currentPath()+ "/setting_forms/" + pathApp+".json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return temp;
    }



    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return temp;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    //qDebug()<<"******************"<<"\n";

    //4. Now picking the jsonValues and printing them out or do what ever you need
    QJsonValue jsonVal;
    QTextStream textStream(stdout);

    //qDebug()<<"******************"<<"\n";
    QJsonArray jsonArray;
    jsonArray = jsonObj[pathApp].toArray();
    //jsonArray = jsonObj["Phone numbers"].toArray();
    //logger::WriteMsg(QString(" ************** " + pathApp + " **********************").toStdString());

    int i=0;
    foreach(const QJsonValue & value, jsonArray)
    {
        if (value.isObject())
        {
            QJsonObject obj = value.toObject();
            foreach(const QString& key, obj.keys()) {
                QJsonValue value = obj.value(key);
                qDebug() << "Key = " << key << ", Value = " << value.toString();
                //vals.append(value.toString());
                //temp.append(value.toString());
                temp.append(key);
                qDebug()<<i<<")"<<" name Columns: "<<key<<"|"<<value.toString()<<"\n";
                i++;
            }
        }
    }


    return temp;
}

QJsonDocument json_w::loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void json_w::saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}


void json_w::Save_to_file(QString pathApp)
{
    QJsonObject mainObject;

    mainObject.insert("name", "Burak Hamdi");
    mainObject.insert("surname", "TUFAN");
    mainObject.insert("age",26);

    QJsonObject address;
    address.insert("city", "Istanbul");
    address.insert("country", "TURKEY");
    //insert the inner json object inside main object
    mainObject.insert("address",address);

    //create a json array for main jsonobject
    QJsonArray phones;
    phones.push_back("0555555555");
    phones.push_back("01111111111");

    // we added JSON array into our main json object
    mainObject.insert("phone", phones);

    // lastly we created a JSON document and set mainObject as object of document
    QJsonDocument jsonDoc;
    jsonDoc.setObject(mainObject);

    saveJson(jsonDoc,"json_save.json");
    qDebug()<<"End save json";
}

void json_w::CreateJsonVarTab()
{
    std::vector<std::string> tabFiles = csvfile::ReadFiles();
    for(auto fn: tabFiles)
    {
        std::map<int, std::vector<std::string>> tab_ = csvfile::Read_TabMap(fn);

        //logger::WriteMsg("file json: "+fn);

        QJsonObject table;
        QJsonArray records;

        QJsonObject record0;
        //record0.insert(QString::fromStdString(tab_[0][0]), "INTEGER PRIMARY KEY UNIQUE");
        record0.insert(QString::fromStdString(tab_[0][0]), "BIGSERIAL PRIMARY KEY");
        //record0.insert(QString::fromStdString(tab_[0][0]), "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE");
        //record0.insert(QString::fromStdString(tab_[0][0]), "text NOT NULL");
        records.push_back(record0);

        for(int i=1; i<tab_[0].size();i++)
        {
            QJsonObject record;
            // INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE
            if(tab_[0][i]=="\r")break;
            if(Str::contains(Str::tolower(tab_[0][i]),"time")!=-1)
            {
                //record.insert(QString::fromStdString(tab_[0][i]), "text NOT NULL");
                record.insert(QString::fromStdString(tab_[0][i]), "text");
            }
            else
            {
                //key_value_t kv{ tab_[0][i], "text NOT NULL" };
                //record.insert(QString::fromStdString(tab_[0][i]), "QString");
                //record.insert(QString::fromStdString(tab_[0][i]), "text NOT NULL");
                record.insert(QString::fromStdString(tab_[0][i]), "text");
            }
            records.push_back(record);
        }

        table.insert(QString::fromStdString(fn),records);

        QJsonDocument jsonDoc;
        jsonDoc.setObject(table);

        saveJson(jsonDoc,"./tables/"+QString::fromStdString(fn)+".json");
        //qDebug()<<"End save json: "<<"./tables/"+QString::fromStdString(fn)+".json";

    }

}

