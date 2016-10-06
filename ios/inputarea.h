#ifndef INPUTAREA_H
#define INPUTAREA_H

#include <QWidget>
#include <QLineEdit>
#include <vector>
#include "sudoku_solver.h"

using namespace std;

typedef QLineEdit cell;


class InputArea : public QWidget
{
    Q_OBJECT
    // The QLineEdit cells
    cell **p2DArray;
    // The input of the th
    vector<vector<int> > input;
public:
    InputArea(QWidget *parent, int width, int diff = 0);
    vector<vector<int> > retreive_input();
    void update_area(vector<vector<int> > input, vector<vector<int> > solution);
    friend InputArea &operator << ( InputArea &inputarea, Sudoku &sod);
    bool event(QEvent *the_event);

    void setInput(vector<vector<int> >);

    void closing();
signals:

public slots:
    void reset();
};

#endif // INPUTAREA_H
