#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap background("icone/background.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

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
        QStringList phrase;
        QMap<QString, word> dicoTrad = dico.value(key);
        QString typePrecedent = "";
        //QList keys = dicoTrad.keys();
        for(int i = 0; i < phrases.length(); i++){
            phrase = phrases[i].split(del2);
            for(int q = 0; q < phrase.length();q++){
                int j = 0;
                int start = q;
                word w;
                typePrecedent = "";
                while(q+j < phrase.length()&& (w = dicoTrad.value(phrase[q+j]))!= ""){
                    if(phrase[start+j]!= "" && w != ""){

                        if(typePrecedent != "n" && w.getType() == "adj" && ui->source->currentText()=="fra"){
                            qDebug() << translate;
                            QStringList changeGrammaire = translate.split(del2);
                            QString last = changeGrammaire[changeGrammaire.length()-2];
                            changeGrammaire[changeGrammaire.length()-2] = w.getTranslate();
                            qDebug() << last;
                            //changeGrammaire.append(last);

                            translate = "";
                            for(int z = 0; z < changeGrammaire.length(); z++){
                                qDebug() << translate;
                                translate += changeGrammaire[z] + " ";
                            }
                            translate += last + " ";
                        }else{
                            translate += w.getTranslate() + " ";
                        }
                        typePrecedent = w.getType();
                        q = start+(j);
                    }
                    j++;
                }
                if(w==""){
                    translate += phrase[q] + " ";
                }
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
    int newSource = 0;
    int newDestination = 0;
    for(int i = 0; i < this->ui->source->count(); i++){
        if(this->ui->source->itemText(i) == this->ui->destination->itemText(destination)){
            newSource = i;
        }
    }
    for(int i = 0; i < this->ui->destination->count(); i++){
        if(this->ui->destination->itemText(i) == this->ui->source->itemText(source)){
            newDestination = i;
        }
    }
    this->ui->source->setCurrentIndex(newSource);
    this->ui->destination->setCurrentIndex(newDestination);
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
                        if(this->lang[j]->getName()==countries[0]){
                            this->lang[j]->getTranslate().append(countries[1]);
                            bool isIn = false;
                            for(int q = 0; q < this->ui->destination->count(); q++){
                                if(this->ui->destination->itemText(q) == countries[1]){
                                    isIn = true;
                                }
                            }
                            if(!isIn)
                                this->ui->destination->addItem(countries[1]);
                            QString key = countries[0]+"-"+countries[1];
                            XMLParseur xml("dico/"+files[i]);
                            this->dico.insert(key, xml.getDico());
                        }
                    }
                }else{
                    QStringList trad;
                    trad << countries[1];
                    language* l = new language(countries[0], trad);
                    this->lang.append(l);
                    this->ui->source->addItem(countries[0]);
                    bool isIn = false;
                    for(int q = 0; q < this->ui->destination->count(); q++){
                        if(this->ui->destination->itemText(q) == countries[1]){
                            isIn = true;
                        }
                    }
                    if(!isIn)
                        this->ui->destination->addItem(countries[1]);
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
    QString string = "tts\\tts.exe \"" + ui->textEdit_2->toPlainText() + "\"";
    QByteArray ba = string.toLatin1();
    const char* text = ba.data();
    system(text);
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
