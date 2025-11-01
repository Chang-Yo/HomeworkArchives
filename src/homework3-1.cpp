#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
void GetSolution(vector<vector<double>>, int, int);
void CheckResult(vector<vector<double>>, int, int);
void FormatResult(vector<vector<double>>, int, int);
int main() {
    string Input = "";
    vector<vector<double>> Matrix;
    int col = 0;
    int row = 0;
    //  read the input and create matrix
    //  We assume that user type data formally
    while (getline(cin, Input)) {
        // to judge whether ends
        if (Input.empty()) break;
        istringstream istr(Input);
        vector<double> NewCol;
        double num = 0;
        while (istr >> num) {
            NewCol.push_back(num);
            row++;
        }
        //    col++;
        Matrix.push_back(NewCol);
        //    row_max = (row_max > row) ? row_max : row;
    }

    col = Matrix.size();
    row = Matrix[0].size();

    // to check the Input's result
    CheckResult(Matrix, col, row);

    if (col < row - 1) {
        cout << "error2" << "\n";
        return 0;
    }

    // Gaussian process
    for (int i = 0; i < col - 1; i++)  // the location of the variable
    {
        if (Matrix[i][i] == 0) {
            continue;
        }
        for (int j = i + 1; j < col; j++) {
            
            double times = Matrix[j][i] / Matrix[i][i];
            for (int k = 0; k < row; k++) {
                Matrix[j][k] -= times * Matrix[i][k];
            }
        }
    }
    CheckResult(Matrix, col, row);

    // we assume that the Matrix has been formalized
    int flag;  // 0:No  1:only one  2:more than one
    if (Matrix[col - 1][row - 2] == 0 && Matrix[col - 1][row - 1] != 0)
        flag = 0;
    else if (Matrix[col - 1][row - 2] != 0 && Matrix[col - 1][row - 1] != 0)
        flag = 1;
    else
        flag = 2;

    switch (flag) {
        case 0:
            cout << "error1" << "\n";
            break;
        case 2:
            cout << "error2" << "\n";
            break;
        case 1:
            GetSolution(Matrix, col, row);
            break;
    }

    return 0;
}

// to caculate the solution if the Matrix has ONLY one set of solution
void GetSolution(vector<vector<double>> Matrix, int col, int row) {
    // when there only one set of solutions, col == row-1
    vector<double> solution(col);
    for (int i = col - 1; i >= 0; i--) {
        double sum = Matrix[i][row - 1];
        for (int j = i + 1; j < col; j++) {
            sum -= Matrix[i][j] * solution[j];
        }
        solution[i] = sum / Matrix[i][i];
        // cout << Matrix[i][row - 1] / Matrix[i][i];
    }
    for (int i = 0; i < col; i++) {
        double x = solution[i];
        int rounded = round(x * 10000);
        solution[i]= rounded/10000.0;
        

        cout << solution[i] << " ";
    }
    return;
}

// this func can print the Matrix
void CheckResult(vector<vector<double>> Matrix, int col, int row) {
    cout << "Have read " << col << " euqlations" << "\n";
    cout << "And " << row - 1 << " Var nums" << "\n";
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// this func can format the input when the user don't type formally. For example
/*Input:
  1 2 8             1 2 0 0 8
  2 3 1 3      ===> 2 3 1 0 3
  3 2 4 5 6         3 2 4 5 6
*/
void Format(vector<vector<double>> Matrix, int col, int row) {
    for (int i = 0; i < col; i++) {
        if (Matrix[i].size() < row) {
            int tmp = Matrix[i].back();
            while (Matrix[i].size() < row - 1) {
                Matrix[i].push_back(0);
            }
            Matrix[i].push_back(tmp);
        }
    }
}