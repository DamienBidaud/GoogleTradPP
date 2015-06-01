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
            word w;
            if(xml.name()=="form"){
                parseForm(xml, w);
            }
            if(xml.name()=="sense"){
                parseSense(xml, w);
            }
            dico.insert(w.getName(), w);
        }
    }
}

void XMLParseur::parseForm(QXmlStreamReader &xml, word w){
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
                w.setName(element);
            }
            if(xml.name()=="pron"){
                continue;
            }
        }
    }
}

void XMLParseur::parseSense(QXmlStreamReader &xml, word w){
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name()=="sense"){
        return;
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "sense")){
        if(xml.name()=="cit"){
            parseCit(xml, w);
        }
    }
}

void XMLParseur::parseCit(QXmlStreamReader &xml, word w){
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
                w.setTranslat(element);
            }
        }
    }
}

QMap<QString, word> XMLParseur::getDico(){
    return this->dico;
}
