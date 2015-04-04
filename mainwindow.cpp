#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(translate()));
    QObject::connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(change()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translate(){

    QString text = ui->textEdit->toPlainText();
    if(text == "Je suis" || text == "I am"){
        ui->textEdit_2->clear();
        if(ui->label->text()=="Français"){
            ui->textEdit_2->setText("I am");
        }else{
            ui->textEdit_2->setText("Je suis");
        }
    }else{
        ui->textEdit_2->clear();
        if(ui->label->text()=="Français"){
            ui->textEdit_2->setText("No other trad available yet! Only one: Je suis ---> I am");
        }else{
            ui->textEdit_2->setText("Pas d'autre traduction disponible pour le moment! Uniquement une: Je suis ---> I am");
        }
    }
}

void MainWindow::change(){
    QString label1 = ui->label->text();
    ui->label->setText(ui->label_2->text());
    ui->label_2->setText(label1);
}
