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
    void setTranslat(QString);
    QString getName();
    QString getTranslate();
    ~word();
private:
    QString name;
    QString translat;
    QString type;
};

#endif // WORD_H
