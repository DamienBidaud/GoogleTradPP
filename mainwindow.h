#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include <QVector>
#include "language.h"
#include <algorithm>
#include <QMap>
#include "xmlparseur.h"
#include "xmlparseurfr.h"
#include "word.h"
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

private:
    Ui::MainWindow *ui;
    QVector<language*> lang;
    QMap<QString, QMap<QString, word> > dico;

};

#endif // MAINWINDOW_H
