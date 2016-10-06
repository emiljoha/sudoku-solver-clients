#include "inputarea.h"
#include <vector>
#include <QEvent>
#include <QKeyEvent>
#include <assert.h>

InputArea::InputArea(QWidget *parent, int Width, int diff) : QWidget(parent)
{   QFont font("Helvetica", 30);

    // Allocate memory for the cells.
    p2DArray = new cell*[9];
    for (int i = 0; i < 9; ++i)
        p2DArray[i] = new cell[9];

    int cell_width = Width; // set Parent, Geometry, MaxLenght, Font and, Alignment for all the cells in the cell area
    int dboxi = 0, dboxj = 0; // Help variables to control manage the creation of seperation between 3x3 sections

    for (int i = 0; i < 9; i++){
        if (i == 3)
            dboxi = diff;
        if (i == 6)
            dboxi = 2 * diff;
        for (int j = 0; j < 9; j++){
            if (j == 0 or j == 1 or j == 2)
                dboxj = 0;
            if (j == 3 or j == 4 or j == 5)
                dboxj = diff;
            if (j == 6 or j == 7 or j == 8)
                dboxj = 2 * diff;
            p2DArray[i][j].setParent(this);
            p2DArray[i][j].setGeometry(i * cell_width + dboxi,j * cell_width + dboxj, cell_width, cell_width);
            p2DArray[i][j].setMaxLength(1);
            p2DArray[i][j].setFont(font);
            p2DArray[i][j].setAlignment(Qt::AlignHCenter);
            p2DArray[i][j].show();
        }
    }
}


bool InputArea::event(QEvent *the_event)
{
    if (the_event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent*>(the_event);
        if (ke->key() == Qt::Key_Up) {
            // special tab handling here
            return true;
        }
    }

    return QWidget::event(the_event);
}

void InputArea::reset(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            p2DArray[i][j].setText("");
        }
    }
    return;
}

void InputArea::closing(){
    // De-Allocate memory to prevent memory leak
    for (int i = 0; i < 9; ++i)
      delete [] p2DArray[i];
    delete [] p2DArray;
}

vector<vector<int> > InputArea::retreive_input(){
    input.resize(9);
    for (int i = 0; i < 9; i++){
        input.at(i).resize(9);
        for (int j = 0; j < 9; j++){
            if (p2DArray[i][j].text() == "")
                input.at(i).at(j) = 0;
            else {
            input.at(i).at(j) = p2DArray[i][j].text().toInt();
            }
        }
    }
    return input;
}

InputArea &operator<<( InputArea &inputarea, Sudoku &sod ){
    assert(inputarea.input.size() == 9);
    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 9; i++){
            if (inputarea.input.at(i).at(j) == 0){
                inputarea.p2DArray[i][j].setText(QString::number(sod.at(i, j)));
                inputarea.p2DArray[i][j].setStyleSheet("color:black");
            }
            else {
                inputarea.p2DArray[i][j].setText(QString::number(inputarea.input.at(i).at(j)));
                inputarea.p2DArray[i][j].setStyleSheet("color:red");
            }
        }
    }
    return inputarea;
}

void InputArea::setInput(vector<vector<int> > in){
    input = in;
    return;
}
