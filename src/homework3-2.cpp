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


    CheckResult(Matrix, col, row);


    return 0;
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