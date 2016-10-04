#ifndef main_cpp
#define main_cpp

#include <QApplication>
#include <QDialog>
#include <vector>
#include "Main-Window.h"
#include <iostream>
#include <QLabel>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 Main_Window window(50, 3);

 // Connect the closing slot to the aboutToQuit signal. colosing slot deallocates the memmory allocated for cells.
 QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(closing()));

 window.show();

 return app.exec();
}

#endif


