#ifndef Main_Window_H
#define Main_Window_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QFont>
#include "inputarea.h"

typedef QLineEdit cell;

class Main_Window: public QMainWindow{
    Q_OBJECT

public:
    Main_Window(int cell_width, int section_diff);

private:
    QPushButton solve_button;
    QPushButton reset_button;
    QLabel error_label;
    InputArea inputarea;


private slots:
    void solve_sudoku();
    void closing();
};

#endif
