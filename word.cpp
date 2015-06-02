#include "word.h"

word::word()
{
    this->name="";
    this->translat="";
    this->type="";
}

word::word(QString name, QString translat, QString type){
    this->name = name;
    this->translat = translat;
    this->type = type;
}

word::word(const word& w){
    this->name = w.name;
    this->translat = w.translat;
    this->type = w.type;
}

word::~word()
{

}

void word::setName(QString name){
    this->name = name;
}

void word::setTranslat(QString translate){
    this->translat = translate;
}

QString word::getName(){
    return this->name;
}

QString word::getTranslate(){
    return this->translat;
}
