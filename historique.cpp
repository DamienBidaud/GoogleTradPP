#include "historique.h"

historique::historique()
{

}


std::map<QString, QString> historique::getSymboleList(QString filename){
    QString val;
    QFile file;
    file.setFileName(filename);
    file.open(QFile::ReadOnly);
    if (file.isOpen()){
        val = file.readAll();

        file.close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        if (!d.isEmpty()){
            QJsonObject object = d.object();
            QStringList listKey = object.keys();
            for (int i = 0; i < listKey.size(); i++)
            {
                QString key = listKey.at(i);
                QJsonValue value = object.value(key);
                QJsonObject symboles = value.toObject();
                QString sentence = symboles["sentence"].toString();
                QString translate = symboles["translate"].toString();
                symboleListe.insert(std::pair<QString, QString>(sentence, translate));

            }
            file.close();
            return symboleListe;
        }
        else
        {
            qDebug() << "empty";
            return this->symboleListe;
        }

        }
    else
    {
        qDebug() << "erreur";
        return this->symboleListe;
    }
}




historique::~historique()
{

}

void historique::writeHistorique(QString fileName, QString key, QString val){
    std::map<QString, QString> map = this->getSymboleList(fileName);
    if(map.find(key) == map.end()){
        QFile f;
        f.setFileName(fileName);
        f.open(QFile::WriteOnly);
        if (f.isOpen())
        {
            QString add = "{";
            std::map<QString, QString>::iterator it;
            int i = 0;
            for (it = map.begin(); it != map.end(); it++)            {
                if (i != 0)
                {
                    add += ",";
                }
                add += "\"" + QString::number(i) + "\" :{\"sentence\":\"" +it->first+ "\", \"translate\":\"" + it->second+ "\"  }";
                i++;
            }
            if(i != 0){
                add += ",";
            }
            add += "\"" + QString::number(i) + "\" :{\"sentence\":\"" + key + "\", \"translate\":\"" + val + "\"  }";
            add += "}";
            f.write(add.toStdString().c_str(), strlen(add.toStdString().c_str()));
            symboleListe.insert(std::pair<QString, QString>(key, val));
            f.close();
        }
    }
}
