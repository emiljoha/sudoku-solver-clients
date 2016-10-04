#include "Main-Window.h"
#include "inputarea.h"
#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include "sudoku_solver.h"
#include <assert.h>

typedef QLineEdit cell;

using namespace std;

Main_Window::Main_Window(int cell_width, int section_diff):inputarea(this, cell_width, section_diff){

    // Set upp the parameters for the cell area:
    // Width of the input cells
    int inputarea_width = 9 * cell_width + 2 * section_diff;
    // diff is the seperation between the different 3x3 sections of the sudoku.
    int solve_button_hight = 0.2 * inputarea_width;
    int reset_button_hight = solve_button_hight;
    int Main_Window_width = inputarea_width;
    int reset_button_width = 0.3 * Main_Window_width;
    int solve_button_width = Main_Window_width - reset_button_width;
    int Main_Window_height = inputarea_width + solve_button_hight;

    // Set font for text in main window.
    QFont font("Helvetica", 40);

    // Set geometry for the main window
    setGeometry(0, 0, Main_Window_width, Main_Window_height);

    // Set up the input area. (the QLabel boxes that takes the input and displays the result)
    //First argument: parent, Second argument: Area side lenghts
    //Third argument: Distance between the 3x3 blocks.
    inputarea.setParent(this);
    inputarea.setGeometry(0, 0, inputarea_width, inputarea_width);
    inputarea.show();


    // Set upp the solve push button.
    solve_button.setParent(this);
    solve_button.setText("Solve");
    solve_button.setGeometry(0, Main_Window_height - solve_button_hight, solve_button_width, solve_button_hight);
    solve_button.setFont(font);
    solve_button.show();


    // Connect the clicked slot on the solve_button to the solve_sudoku method the main window that solves and
    // displayes the result in the cells.
    QObject::connect(&solve_button, SIGNAL(clicked()), this, SLOT(solve_sudoku()));

    // Set upp the reset button
    reset_button.setParent(this);
    reset_button.setText("reset");
    reset_button.setGeometry(solve_button_width, Main_Window_height - reset_button_hight,
                             reset_button_width, reset_button_hight);
    reset_button.setFont(font);
    reset_button.show();

    // Connect the clicked signal of the reset button to to clear slot in the
    // created Main_Window. clear calls setText(" ") for all QLineEdit widgets
    // that form the input for the sudoku.
    QObject::connect(&reset_button, SIGNAL(clicked()), &inputarea, SLOT(reset()));

}

void Main_Window::solve_sudoku(){
    vector<vector<int> > input = inputarea.retreive_input();
    Sudoku *S = new Sudoku(input);

    // Font for the error pop ups.
    QFont Helvetica_40("Helvetica", 30);


    if (!S->solvable()){

       error_label.setText("There is something wrong with the Sudoku \n Check if something is wrong and try again");
       //error_label.setGeometry(0, 0, 400, 100);
       error_label.setFont(Helvetica_40);
       error_label.show();
    }
    else if(S->solve()){
        inputarea.setInput(input);
        inputarea << *S;
    }
    else{
        error_label.setText("Sorry, can´t solve it. \n Check if you have written the sudoku correctly.");
        error_label.setFont(Helvetica_40);
        error_label.show();
    }
    delete S;
}

void Main_Window::closing(){
    inputarea.closing();
}






