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
    QObject::connect(this->ui->pushButton_4, SIGNAL(clicked()), this, SLOT(voice()));
    QAction::connect(this->ui->actionHistorique, SIGNAL(triggered()), this, SLOT(afficherHistorique()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//traduit
void MainWindow::translate(){
    if(this->ui->source->currentText() == this->ui->destination->currentText()){
        QMessageBox mes;
        mes.setText("La langue de destination est la meme que la langue source!");
        mes.exec();
    }else{
        QString text = ui->textEdit->toPlainText();
        QString translate;
        QString key = ui->source->currentText()+"-"+ui->destination->currentText();
        QRegExp del("\\.");
        QRegExp del2("\\ ");
        QStringList phrases = text.split(del);
        QMap<QString, word> dicoTrad = dico.value(key);
        //QList keys = dicoTrad.keys();
        for(int i = 0; i < phrases.length(); i++){
            int j = 0;
            word w;
            while(i+j < phrases.length()&& (w = dicoTrad.value(phrases[i+j]))!= ""){
                if(phrases[i+j]!= "" && w != ""){
                    translate += w.getTranslate() + " ";
                    i = i+(j+1);
                }
                j++;
            }
            if(w==""){
                translate += phrases[i] + " ";
            }
        }
        this->ui->textEdit_2->setText(translate);
        h.writeHistorique("historique/"+key+".json", text, translate);

    }
}


//échange les 2 valeurs du spinner
void MainWindow::change(){
    int source = this->ui->source->currentIndex();
    int destination = this->ui->destination->currentIndex();
    this->ui->source->setCurrentIndex(destination);
    this->ui->destination->setCurrentIndex(source);
}

//reset les champs text
void MainWindow::reset(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

//verifie les dicos disponnibles et les initialises
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
                    QString key = countries[0]+"-"+countries[1];
                    XMLParseur xml("dico/"+files[i]);
                    this->dico.insert(key, xml.getDico());
                }
            }
        }
    }else{
        qDebug() << "the directory doesn'existe!";
    }
}

void MainWindow::voice(){

}

//verfie si une langue à déjà été enregister
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


void MainWindow::afficherHistorique(){
    QString filename = ui->source->currentText()+"-"+ui->destination->currentText()+".json";
    HistoriqueFenetre hf("historique/"+filename);
    hf.exec();
}
