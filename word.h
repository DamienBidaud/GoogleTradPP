#ifndef WORD_H
#define WORD_H

#include <QString>

class word
{
public:
    word();
    word(QString, QString, QString);
    word(const word&);
    void setName(QString);
    void setPronon(QString);
    void setTranslat(QString);
    QString getName();
    QString getTranslate();
    QString getType();
    QString getPrononciation();
    bool operator ==(const word&);
    bool operator ==(const QString&);
    bool operator !=(const word&);
    bool operator !=(const QString&);
    ~word();
private:
    QString name;
    QString translat;
    QString type;
    QString prononciation;
};

#endif // WORD_H
