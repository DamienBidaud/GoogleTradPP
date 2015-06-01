#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkLanguage();
    QObject::connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(translate()));
    QObject::connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(change()));
    QObject::connect(this->ui->pushButton_3, SIGNAL(clicked()), this, SLOT(reset()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translate(){

    QString text = ui->textEdit->toPlainText();

}

void MainWindow::change(){

}

void MainWindow::reset(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

void MainWindow::checkLanguage(){
    QDir dico("dico/");
    QRegExp del("\\-|\\.");
    if(dico.exists()){
        QStringList files = dico.entryList();
        for(int i = 0; i < files.size(); i++){
            if(files[i]!="." && files[i]!=".."){
                QString file = files[i];
                QStringList countries = file.split(del);
                if(isInVector(countries[0])){
                    for(int j = 0; j < this->lang.size(); j++){
                        if(this->lang[i]->getName()==countries[0]){
                            this->lang[i]->getTranslate().append(countries[1]);
                        }
                    }
                }else{
                    QStringList trad;
                    trad << countries[1];
                    language* l = new language(countries[0], trad);
                    this->lang.append(l);
                    this->ui->source->addItem(countries[0]);
                    this->ui->destination->addItem(countries[0]);
                    XMLParseur xml(files[i]);
                    QString key = countries[0]+"-"+countries[1];
                    this->dico.insert(key, xml.getDico());
                }
            }
        }
    }else{
        qDebug() << "the directory doesn'existe!";
    }
}


bool MainWindow::isInVector(QString country){
    if(!this->lang.isEmpty()){
        for(int i = 0; i < this->lang.size(); i++){
            if(this->lang[i]->getName() == country)
                return true;
        }
        return false;
    }else{
        return false;
    }
}
