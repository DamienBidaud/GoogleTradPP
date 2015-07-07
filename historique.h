#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class historique
{
public:
    historique(QString);
    void writeHistorique(QString, QString, QString);
    ~historique();
private:
    std::map<QString, QString> symboleListe;
};

#endif // HISTORIQUE_H
