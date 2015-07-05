#include "word.h"

word::word()
{
    this->name="";
    this->translat="";
    this->type="";
    this->prononciation= "";
}

word::word(QString name, QString translat, QString type){
    this->name = name;
    this->translat = translat;
    this->type = type;
    this->prononciation= "";
}

word::word(const word& w){
    this->name = w.name;
    this->translat = w.translat;
    this->type = w.type;
    this->prononciation = w.prononciation;
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

void word::setPronon(QString prononciation){
    this->prononciation = prononciation;
}

QString word::getName(){
    return this->name;
}

QString word::getTranslate(){
    return this->translat;
}

QString word::getType(){
    return this->type;
}

QString word::getPrononciation(){
    return this->prononciation;
}

bool word::operator ==(const word& w){
    return name == w.name && translat == w.translat && type == w.type && prononciation == w.prononciation;
}

bool word::operator ==(const QString& w){
    return (name == w && translat == w && prononciation == w && type == w);
}

bool word::operator !=(const word& w){
    return !(*this == w);
}

bool word::operator !=(const QString& w){
    return !(*this == w);
}
