//*************************
// The gameofwords.h file
// author:GeoWade
//*************************
#ifndef GAMEOFWORDS_H
#define GAMEOFWORDS_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QDialog>
#include <QMessageBox>
#include <QSize>


class GameOfWords : public QMainWindow
{
    Q_OBJECT

public:
    GameOfWords(QWidget *parent = 0);
    ~GameOfWords();
    void fileStart(bool load);


private slots:

    void lettersPushed();
    void clearLine();
    void backSpace();

    void setLocation();
    void wordSearch();

signals:


private:

    QLabel *boxLabel;
    QLabel *edgeLabel;
    QLabel *windowLabel;
    QFile *myFile;
    QLineEdit *lineEdit;
    QGridLayout *gridBox;
    QScrollArea *scrollArea;
    QTextEdit *textEdit;
    QLabel *labelTime;
    QLabel *labelOne;
    QListView *listView;
    QStringListModel *model;
    QLabel *labelTwo;
    QLabel *labelCorrect[499];
    QLabel *cornerLabels[4];
    QSpinBox *spinBox;
    QPushButton *letterButtons[36];
    QPushButton *operationButton[2];
    QPushButton *enterButton;


    QMessageBox *corBox;
    QMessageBox *incorBox;
    QMessageBox *alrcorBox;

};

#endif // GAMEOFWORDS_H#ifndef GAMEOFWORDS_H
