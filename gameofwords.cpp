//******************************
// Created in the spring of 2014
// author:GeoffreyWade
//*********************
#include "gameofwords.h"

#include <QMainWindow>
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>
#include <QTextEdit>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <ctime>
#include <QString>
#include <QListView>
#include <QStringList>
#include <QList>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>


static const char alphabetic[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int cntArry[26] = {76, 20, 40, 37, 116, 14, 29, 22, 87, 3, 9, 54, 27, 69, 61, 28, 4, 73, 89, 66, 33, 10, 9, 3, 17, 4};


QChar alphaHold[30];
QChar holdAlpha[1001];

QString letters = "", answerChoice = "ALREADY CREDITED!";
QString choiceAnswer = "CORRECT!", answerFalse = "INCORRECT!";
QString holdWord = "", wordHold = "", word = "";
QString operations[] = {"BACKSPACE", "CLEAR"};

QStringList wordBank;
QString arryOne[109582];
QString holdAry[4];
QStringList cList;


bool correctSearchBool = false, start = false;
bool wordSearchBool = false, clearBool = false, backspaceBool = false;

int score = 0;

GameOfWords::GameOfWords(QWidget *parent)
    : QMainWindow(parent)
{

    /*
     * Label the whole window with a setFrameStyle function that yields the
     * visual effect that the edges of the frame are elevated, which in turn
     * yields a visual effect that the rest of GUI components are slightly
     * inset.
     */
    edgeLabel = new QLabel("",this);
    edgeLabel -> setFrameStyle(QFrame::Box | QFrame::Raised);
    edgeLabel -> setGeometry(QRect(QPoint(0, 0), QSize(460, 400)));
    edgeLabel -> setStyleSheet("QLabel{background: silver;}");

    /*
     * This label colors the background or the QMainWindow's frame.
     * This must be done to mask the edgeLabel's background color.
     */
    windowLabel = new QLabel("",this);
    windowLabel -> setFrameStyle(QFrame::Panel | QFrame::Raised);
    windowLabel -> setGeometry(QRect(QPoint(5, 5), QSize(450, 400)));
    windowLabel -> setStyleSheet("QLabel{background: cyan;}");

    /*
     * This label, due to its framestyle yields the visual effect that
     * the this QPushButton letterButtons[] layout is encompassed by an
     * inner frame.
     */
    boxLabel = new QLabel("",this);
    boxLabel -> setFrameStyle(QFrame::Box | QFrame::Raised);
    boxLabel -> setGeometry(QRect(QPoint(4, 149), QSize(302, 302)));
    boxLabel -> setStyleSheet("QLabel{background: violet;}");

    int charcnt = 1;
    int stopper = 0;

    /*
     * A nested iteration to evaluate the probability of each letter with in the
     * word list and a character array (holdAlpha) to store it in.
     */
    for (int i = 0; i < 26; i++) {

        stopper += cntArry[i];

        for (int j = 1; j <= stopper; j++) {

            QChar meChar = alphabetic[i];
            holdAlpha[charcnt] = meChar;
            charcnt++;
        }
        stopper = 0;
    }

    // a randomized variable to generate 30 possibilities in a random fasion
    srand(time(0));

    // randomly generate 30 letters
    for (int t = 0; t < 30; t++) {

        int n = (rand() % 1000+1);
        QChar charRand = holdAlpha[n];
        alphaHold[t] = charRand;

    }

    // create 30 QPushButton objects
    for (int i = 0; i < 30; i++){
        letterButtons[i] = new QPushButton(alphaHold[i], this);
        letterButtons[i] -> setStyleSheet("QPushButton{background: violet; color: blue;}");
        connect(letterButtons[i], SIGNAL(released()), this, SLOT(lettersPushed()));

    }

    // create 2 operations buttons, Clear, and Backspace
    for (int k = 0; k < 2; k++)
    {
        operationButton[k] = new QPushButton(operations[k], this);
        if (k == 0){
            operationButton[k] -> setStyleSheet("QPushButton{background: rgb(70,143,143); color: gold; border-width: 4px; border-style: outset; border-radius: 10px; border-color: white;}");
            operationButton[k] -> setGeometry(QRect(QPoint(325, 110),QSize(90, 30)));
            connect(operationButton[k], SIGNAL(clicked()), this, SLOT(backSpace()));
        }
        else {
            operationButton[k] -> setStyleSheet("QPushButton{background: gold; color: black; border-width: 4px; border-style: outset; border-radius: 10px;}");
            operationButton[k] -> setGeometry(QRect(QPoint(390, 45),QSize(55,40)));
            connect(operationButton[k], SIGNAL(clicked()), this, SLOT(clearLine()));
        }
    }

    // create the Enter button
    enterButton = new QPushButton("ENTER", this);
    enterButton -> setStyleSheet("QPushButton{background:red; color: blue; border-width: 4px; border-style: outset; border-radius: 10px;}");
    enterButton -> setGeometry(QRect(QPoint(150, 10),QSize(120,30)));
    connect(enterButton, SIGNAL(released()), this, SLOT(wordSearch()));

    // create a QLineEdit that allows the user to see what letter have been pressed
    lineEdit = new QLineEdit("", this);
    lineEdit ->	setAlignment(Qt::AlignRight);
    QFont font = lineEdit -> font();
    font.setPointSize(font.pointSize()+ 10);
    font.setBold(true);
    lineEdit -> setFont(font);
    lineEdit -> setGeometry(QRect(QPoint(50, 45), QSize(325,40)));
    lineEdit -> setStyleSheet("QLineEdit{background: white;}");
    lineEdit -> setReadOnly(true);

    // create a QScrollArea Widget scrollArea to house the listView
    scrollArea = new QScrollArea(this);
    scrollArea -> setGeometry(QRect(QPoint(305,150), QSize(150, 250)));
    scrollArea -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea -> setMaximumHeight(600);

    // create QStringListModel
    model = new QStringListModel(this);

    cList << "";
    model -> setStringList(cList);

    listView = new QListView(this);
    listView -> setGeometry(QRect(QPoint(305,150), QSize(145, 2500000)));
    listView ->setStyleSheet("QListView{background-color:rgb(224, 255, 255); color:green;}");
    listView -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    model = new QStringListModel(this);
    model -> setStringList(cList);
    listView -> setModel(model);

    scrollArea -> setWidget(listView);

    // create score label above the spinbox
    labelTwo = new QLabel("SCORE", this);
    labelTwo -> setAlignment(Qt::AlignCenter);
    labelTwo -> setFrameStyle(QFrame::Box | QFrame::Raised);
    labelTwo -> setGeometry(QRect(QPoint(35, 90), QSize(50, 20)));
    labelTwo -> setStyleSheet("QLabel{background: blue; color: red}");

    // create a spinbox to hold the score
    spinBox = new QSpinBox(this);
    spinBox -> setAlignment(Qt::AlignRight);
    QFont fontSpin = spinBox -> font();
    fontSpin.setPointSize(fontSpin.pointSize() + 6);
    fontSpin.setBold(true);

    spinBox -> setFont(fontSpin);
    spinBox -> setGeometry(QRect(QPoint(20, 115), QSize(80, 30)));
    spinBox -> setStyleSheet("QSpinBox{background:white; color: blue}");
    spinBox -> setRange(0 , 1000);
    spinBox -> setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBox -> setReadOnly(true);
    spinBox -> setValue(score);

    // create a QMessageBox to inform of correct answers
    corBox = new QMessageBox(this);
    corBox -> setContentsMargins(-10, 25, 10, 50);
    corBox -> setWindowTitle("YOU KNOW IT!");
    corBox -> setText("<h1><font color=yellow><i><b>\t\t\tTHAT IS CORRECT!\t\t\t</b></i></font-color></h1>");
    corBox -> setStyleSheet("QMessageBox{background:blue;} QPushButton{background: red; color: blue};");

    // create a QMessageBox to inform of incorrect answers
    incorBox = new QMessageBox(this);
    incorBox -> setContentsMargins(-10, 25, 10, 50);
    incorBox -> setWindowTitle("OOPS! TRY AGAIN!");
    incorBox -> setText("<h1><font color=white><b>\t\t\tSORRY INCORRECT!\t\t</b></font-color></h1>");
    incorBox -> setStyleSheet("QMessageBox{background:red;} QPushButton{background: white; color: red};");

    // create a QMessageBox to inform the user of already credited answers
    alrcorBox = new QMessageBox(this);
    alrcorBox -> setContentsMargins(-10, 25, 10, 50);
    alrcorBox -> setWindowTitle("OOPS!");
    alrcorBox -> setText("<h1><font color=blue><b>\t\t\tALREADY CREDITED!\t\t\t</b></font-color></h1>");
    alrcorBox -> setStyleSheet("QMessageBox{background:rgb(224, 255, 255);} QPushButton{background: yellow; color: blue};");

    setLocation();

}

/*
 * The lettersPushed function inputs and outputs the button text to
 * the text object
*/

void GameOfWords::lettersPushed()
{

    QPushButton *letterButtons = (QPushButton *) sender();
    // verify the button is correct and set the text to the lineEdit
    if (letterButtons)
    {
        lineEdit -> setText(letters.insert(letters.size(), letterButtons -> text()));
    }
    lineEdit -> setText(letters);
}

void GameOfWords::clearLine()
{

    QPushButton *operationButton = (QPushButton *)sender();

    // verify the button is the CLEAR button and clear the lineEdit
    if (operationButton -> text()=="CLEAR"){

        letters = "";
        lineEdit -> setText(letters);
        clearBool = true;
    }
    else {
        clearBool = false;
    }

}

void GameOfWords::backSpace()
{
    /*
     * verify that the lineEdit does have text and chop (remove) the last character
     */
    if (!(lineEdit -> text().isEmpty()))
    {
        QString backspace = lineEdit -> text();
        backspace.chop(1);
        letters = "";
        letters += backspace;
        lineEdit -> setText(letters);
        backspaceBool = true;
    }
    else
    {
        backspaceBool = false;
    }
}

void GameOfWords::setLocation()
{
    /*
     * To create a button layout that is symmetrical horizontally
     * (or vertically) the QPushButton letterButtons[] array should be
     * iterated to a terminal condition of the equivalent to the rows size
     * (e.g. 5) length of the row with counter being some multiple of the
     * x or y cordinate of the corresponding row
     */
    for (int i = 0; i < 6; i++) {

         letterButtons[i] -> setGeometry(QRect(QPoint(5+(i*50), 150), QSize(50, 50)));

    }

    for (int i = 6; i < 12; i++) {

        letterButtons[i] -> setGeometry(QRect(QPoint(5+(i-6)*50, 200), QSize(50, 50)));

    }

    for (int i = 12; i < 18; i++) {

        letterButtons[i] -> setGeometry(QRect(QPoint(5+(i-12)*50, 250), QSize(50, 50)));

    }

    for (int i = 18; i < 24; i++) {

        letterButtons[i] -> setGeometry(QRect(QPoint(5+(i-18)*50, 300), QSize(50, 50)));

    }

    for (int i = 24; i < 30; i++) {

        letterButtons[i] -> setGeometry(QRect(QPoint(5+(i-24)*50, 350), QSize(50, 50)));

    }


}

void GameOfWords::fileStart(bool load)
{

    start = load; // bool trigger, one time at app initialization

    if (start){
        QFile myfile(":/WordData/WordData/TheHundredGrand.txt");

        if(myfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString line;
            QTextStream stream(&myfile);
            int index = 0;

            /*
             * An teration to cycle through the data inputted from the open
             * file to theQTextStream, and store the data in the
             * wordBank list
             */
            do
            {
                line = stream.readLine();
                arryOne[index] = line;
                wordBank << arryOne[index];
                index++;
            }while(!stream.atEnd());

            // flush the buffer of the QTextStream
            stream.flush();
            // close the file the file whose data was inputted into program.
            myfile.close();

        }
    }
    //start = false;
}


void GameOfWords::wordSearch()
{

    QPushButton *enterButton = (QPushButton *) sender();
    word = lineEdit -> text();
    // iterate through the correct word list to see if the word has been scored
    QStringList::iterator i3 = qFind(cList.begin(), cList.end(), word);
    // search through the wordBank list inorder to see if the entry is on the word list
    QStringList::iterator i2 = qFind(wordBank.begin(), wordBank.end(), word);

    if ( i2 == wordBank.end() ){
        incorBox -> show();
        wordSearchBool = false;
    }
    else{

        wordSearchBool = true;
    }
    /*
     *  a set of nested conditional statements to evaluate the logic
     *  that has already been established for the entries that
     *  have been made into the lists
     */
    if (wordSearchBool == true){
        if ( i3 == cList.end() ){
            cList.prepend(word);
            letters = "";
            score += word.size();
            model -> setStringList(cList);
            listView -> setModel(model);
            scrollArea -> setWidget(listView);
            corBox -> show();
            correctSearchBool = true;
        }
        else{
            alrcorBox -> show();
            correctSearchBool = false;
        }
    }
    else {
        correctSearchBool = false;
    }
    // null the letters variable and the word variable
    letters = "";
    word = "";
    // null the QLineEdit widget for consecutive word entries
    lineEdit -> setText(letters);
    // tally the score setting the value (or showing) the current score count
    spinBox -> setValue(score);
    // set the correctSearchBool and wordSearchBool variables to false
    correctSearchBool = false;
    wordSearchBool = false;

}
GameOfWords::~GameOfWords()
{

}
