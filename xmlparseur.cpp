#include "xmlparseur.h"

XMLParseur::XMLParseur()
{

}

XMLParseur::XMLParseur(QString fileName){
    this->fileName = fileName;
    parsXML();
}

XMLParseur::~XMLParseur()
{
    delete this->file;
}

void XMLParseur::parsXML(){
    this->file = new QFile(this->fileName);

    QXmlStreamReader xml(file);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Erreur d'ouverture du fichier de configuration";
            return;
    }
    while(!xml.atEnd() && !xml.hasError()){
        QXmlStreamReader::TokenType token = xml.readNext();
        //si c'est le début du document on continue
        if(token == QXmlStreamReader::StartDocument){
            continue;
        }
        //si c'est le premier element
        else if(token== QXmlStreamReader::StartElement){
            if(xml.name()== "teiHeader"){
                continue;
            }
            if(xml.name()=="text"){

                parseText(xml);
            }
        }
    }
    if(xml.hasError()){
        qDebug() << xml.errorString();
    }
    xml.clear();
    file->close();
}

void XMLParseur::parseText(QXmlStreamReader &xml){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="text"){
        return;
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "text")){

        if(xml.tokenType() == QXmlStreamReader::StartElement){
            if(xml.name()=="body"){
                parseBody(xml);
            }
        }
        xml.readNext();
    }
}

void XMLParseur::parseBody(QXmlStreamReader &xml){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="body"){
        return;
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "body")){

        if(xml.tokenType() == QXmlStreamReader::StartElement){
            //qDebug()<< xml.name().toString();
            if(xml.name()=="entry"){
                parseEntry(xml);
            }
        }
        xml.readNext();
    }
}

void XMLParseur::parseEntry(QXmlStreamReader &xml){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="entry"){
        return;
    }
    word w;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "entry")){
        //QXmlStreamReader::TokenType token = xml.readNext();
        if(xml.tokenType() == QXmlStreamReader::StartElement){

            if(xml.name()=="form"){
                parseForm(xml, w);
            }
            if(xml.name()=="gramGrp"){
                parseGram(xml, w);
            }
            //qDebug() << w.getName();
            if(xml.name()=="sense"){
                parseSense(xml, w);
            }
           // qDebug() << w.getName();
            this->dico.insert(w.getName(), w);

        }
        xml.readNext();
    }
}

void XMLParseur::parseForm(QXmlStreamReader &xml, word &w){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="form"){
        return;
    }
    QString element;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "form")){
        if(xml.tokenType() == QXmlStreamReader::StartElement){
            if(xml.name()=="orth"){
                element = xml.name().toString();
                xml.readNext();
                if(xml.tokenType() != QXmlStreamReader::Characters){
                    continue;
                }
                //qDebug() << xml.text().toString();
                w.setName(xml.text().toString());
            }
            if(xml.name()=="pron"){
                element = xml.name().toString();
                xml.readNext();
                if(xml.tokenType()!= QXmlStreamReader::Characters){
                    continue;
                }
                w.setPronon(xml.text().toString());
            }
        }
        xml.readNext();
    }

}


void XMLParseur::parseSense(QXmlStreamReader &xml, word& w){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="sense"){
        return;
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "sense")){
        //QXmlStreamReader::TokenType token = xml.readNext();
        if(xml.name()=="cit"){

            parseCit(xml, w);
        }
        xml.readNext();
    }
}


void XMLParseur::parseCit(QXmlStreamReader &xml, word& w){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="cit"){
        return;
    }
    QString element;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "cit")){
        if(xml.tokenType() == QXmlStreamReader::StartElement){
            if(xml.name()=="quote"){
                element = xml.name().toString();
                xml.readNext();
                if(xml.tokenType() != QXmlStreamReader::Characters){
                    continue;
                }

                w.setTranslat(xml.text().toString());
            }
        }
        xml.readNext();
    }
}

QMap<QString, word>& XMLParseur::getDico(){
    return this->dico;
}


void XMLParseur::parseGram(QXmlStreamReader &xml, word & w){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="gramGrp"){
        return;
    }
    QString element;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "gramGrp")){
        if(xml.tokenType() == QXmlStreamReader::StartElement){
            if(xml.name()=="pos"){
                element = xml.name().toString();
                xml.readNext();
                if(xml.tokenType() != QXmlStreamReader::Characters){
                    continue;
                }

                //qDebug() << xml.text().toString();
                w.setType(xml.text().toString());
            }
        }
        xml.readNext();
    }

}
