#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>
#include <QStringList>

class language
{
public:
    language();
    language(QString, QStringList);
    language(const language&);
    language& operator=(const language&);
    ~language();
    QString getName();
    QStringList getTranslate();

private:
    QString name;
    QStringList translate;
};

#endif // LANGUAGE_H
