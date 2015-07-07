#include "historique.h"

historique::historique(QString filename)
{
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

            }
            else
            {
                qDebug() << "empty";
            }

            }
        else
        {
            qDebug() << "erreur";
        }
}

historique::~historique()
{

}

void historique::writeHistorique(QString fileName, QString key, QString val){
    if(this->symboleListe.find(key) == this->symboleListe.end()){
        QFile f;
        f.setFileName(fileName);
        f.open(QFile::WriteOnly);
        if (f.isOpen())
        {
            nbRow = this->ui->tableWidget->rowCount();
            QString add = "{";
            for (int i = 0; i < nbRow; i++)
            {
                if (i != 0)
                {
                    add += ",";
                }
                add += "\"" + QString::number(i) + "\" :{\"sentence\":\"" + key + "\", \"translate\":\"" + val + "\"  }";
            }
            add += "}";
            f.write(add.toStdString().c_str(), strlen(add.toStdString().c_str()));
        }
    }
}
