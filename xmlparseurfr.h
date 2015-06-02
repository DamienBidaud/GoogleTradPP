#ifndef XMLPARSEURFR_H
#define XMLPARSEURFR_H



#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QMap>
#include <QString>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include "word.h"

class xmlparseurfr
{
public:
    xmlparseurfr();
    xmlparseurfr(QString);
    ~xmlparseurfr();
    void parsXML();
    void parseText(QXmlStreamReader &xml);
    void parseBody(QXmlStreamReader &xml);
    void parseEntry(QXmlStreamReader &xml);
    void parseForm(QXmlStreamReader &xml, word&);
    void parseSense(QXmlStreamReader &xml, word&);
    QMap<QString, word>& getDico();
private:
    QString fileName;
    QFile* file;
    QMap<QString, word> dico;
};


#endif // XMLPARSEURFR_H
