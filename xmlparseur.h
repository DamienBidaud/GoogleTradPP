#ifndef XMLPARSEUR_H
#define XMLPARSEUR_H

#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QMap>
#include <QString>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include "word.h"

class XMLParseur
{
public:
    XMLParseur();
    XMLParseur(QString);
    ~XMLParseur();
    void parsXML();
    void parseText(QXmlStreamReader &xml);
    void parseForm(QXmlStreamReader &xml, word);
    void parseSense(QXmlStreamReader &xml, word);
    void parseCit(QXmlStreamReader &xml, word);
    QMap<QString, word> getDico();
private:
    QString fileName;
    QFile* file;
    QMap<QString, word> dico;
};

#endif // XMLPARSEUR_H
