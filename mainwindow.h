#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include <QVector>
#include <algorithm>
#include <QMap>
#include "language.h"
#include "xmlparseur.h"
#include "xmlparseurfr.h"
#include "word.h"
#include "historique.h"
#include "historiquefenetre.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkLanguage();
    bool isInVector(QString);

public slots:
    void translate();
    void change();
    void reset();
    void afficherHistorique();

private:
    Ui::MainWindow *ui;
    QVector<language*> lang;
    QMap<QString, QMap<QString, word> > dico;
    historique h;

};

#endif // MAINWINDOW_H
