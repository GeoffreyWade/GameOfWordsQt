//*****************************************************
// Created in the spring of 2014
// author:GeoffreyWade
//*****************************************************
#include "gameofwords.h"
#include <QApplication>
#include <QtGui>
#include <QtCore/QCoreApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // creaate a GameOfWords object
    GameOfWords w;

    // create a boolean trigger
    bool load = true;
    // load the trigger into the fileStart function
    w.fileStart(load);
    // set a window title for the app
    w.setWindowTitle("\tGAME OF WORDS");
    // the apps size is a constant, show it the app maximized on the screen
    w.showMaximized();

    // set the apps size to a constant
    w.setFixedSize(460, 400);

    // decorate the QMainWindow frame object that 'houses' the app
    w.setStyleSheet("QMainWindow{border-width: 4px; border-style: outset; border-radius: 14px; border-color: grey;}");

    // call the app to the center of the screen when executed
    w.move(QApplication::desktop()->screen()->rect().center()-w.rect().center());

    // show the app.
    w.show();

    // turn the boolean trigger off
    w.fileStart(!load);

    return app.exec();
}
