#include "historiquefenetre.h"
#include "ui_historiquefenetre.h"

HistoriqueFenetre::HistoriqueFenetre(QString filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoriqueFenetre)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    std::map<QString, QString> symboles = h.getSymboleList(filename);
    if (symboles.size()>0)
    {
        int col = 0;
        int nbRow = this->ui->tableWidget->rowCount();
        for (std::map<QString, QString>::iterator i = symboles.begin(); i != symboles.end(); i++)
        {

            this->ui->tableWidget->insertRow(nbRow);
            QTableWidgetItem * item1 = new QTableWidgetItem(i->first);
            QTableWidgetItem* item2 = new QTableWidgetItem(i->second);
            this->ui->tableWidget->setItem(nbRow, 0, item1);
            this->ui->tableWidget->setItem(nbRow, 1, item2);
            col++;
            nbRow++;
        }
    }
}

HistoriqueFenetre::~HistoriqueFenetre()
{
    delete ui;
}
