#include "language.h"

language::language()
{
}

language::~language()
{

}

language::language(QString name, QStringList trad){
    this->name=name;
    this->translate=trad;
}

language::language(const language& l){
    this->name = l.name;
    this->translate = l.translate;
}

language& language::operator=(const language& l){
    if(this!= &l){
        this->name = l.name;
        this->translate = l.translate;
        return *this;
    }else{
        return *this;
    }
}


QString language::getName(){
    return this->name;
}

QStringList language::getTranslate(){
    return this->translate;
}
