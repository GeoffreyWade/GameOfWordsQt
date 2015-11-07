# GameOfWordsQt
This is project is a word game application, that was coded in C++/Qt in the spring of 2014.

The application was initially built as a project with the Qt4.8 framework. Since then the application has been rebuilt with Qt versions 5.1, 5.2, 5.3, and prior to this commit Qt5.5. The application consists of three files:

main.cpp
gameofwords.cpp
gameofwords.h

and directory title WordData that contains the word list that will be inputted into the program as a word bank
for the application:

WordData/TheHundredGrand.txt

Due to the fact that the application has been built and tested with many versions of Qt, different Interactive 
Development Environments, and with many operating system types:
Windows, Linux, MacOSx, and Solaris; the requester can download and build the project themselves.

To do so, instead of opening a .pro file (which I have not commited) within a Netbeans/Qt IDE, 
create a new Qt Application project. Then copy and paste the main into main, gameofwords.cpp into gameofwords.cpp
and gameofwords.h into gameofwords.h.

After doing so the project builder will have to create a Qt resource file (.qrc) for the WordData prefix and
TheHundredGrand.txt file.

As of right now the application is ready to built and used by users of Unix-like operating systems. With the
prefix being:
WordData

and the AddFile being:

WordData/TheHundredGrand.txt

Simple command line statements to copy or move the WordData diretory from the extracted archive into the projects
directory can be performed in order for the the directory to exist in the requesters project. 


It should be noted that Windows users will have to make adjustments to the name space of the Qt Resource file (.qrc) file and to the function within the gameofwords.cpp class file.

The function:
void GameOfWords::fileStart(bool load) {}

contains a QFile object titled myfile, adjustments will have to be made for Windows filesystem types for the backslashes of the namespace of the files added.

I hope this helps!




