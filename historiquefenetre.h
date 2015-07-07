#ifndef HISTORIQUEFENETRE_H
#define HISTORIQUEFENETRE_H

#include <QDialog>
#include "historique.h"
namespace Ui {
class HistoriqueFenetre;
}

class HistoriqueFenetre : public QDialog
{
    Q_OBJECT

public:
    explicit HistoriqueFenetre(QString, QWidget *parent = 0);
    ~HistoriqueFenetre();

private:
    Ui::HistoriqueFenetre *ui;
    historique h;
};

#endif // HISTORIQUEFENETRE_H
