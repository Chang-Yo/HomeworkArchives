// Jacobi 迭代法的使用有一定条件，并不能像 Gaussion 消元法一样对所有方程组都试用
// Jacobi 迭代法要求系数矩阵 A 必须是 严格对角占优
// 也即对角线上的某一个元素必须比所在行的其他元素之和还要大
// 所以在本题中，我们先对系数矩阵做了一定的优化处理，利用Poviting()函数将矩阵做了一定程度地排序，但并非十分的有效
// 在Jacobi迭代过程中，对一些细节做了优化，让收敛速度加快
// 每次我们都会检测优化后的系数矩阵，如果无法使用 Jacobi
// 迭代法，便会转向Gaussion消元法，所以代码看起来有些臃肿，但已尽力结构化
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
void GetSolution_Jacobi(vector<vector<double>>, int, int);
void GetSolution_Gaussion(vector<vector<double>>, int, int);
void CheckResult(vector<vector<double>>, int, int);
void Poviting(vector<vector<double>>&, int, int);
int main() {
    string Input = "";
    vector<vector<double>> Matrix;
    int row = 0;
    int col = 0;
    //  read the input and create matrix
    //  We assume that user type data formally
    while (getline(cin, Input)) {
        // to judge whether ends
        if (Input.empty()) break;
        istringstream istr(Input);
        vector<double> Neroww;
        double num = 0;
        while (istr >> num) {
            Neroww.push_back(num);
            col++;
        }
        Matrix.push_back(Neroww);
    }

    row = Matrix.size();
    col = Matrix[0].size();

    // to check the Input's result
    CheckResult(Matrix, row, col);

    if (row < col - 1) {
        cout << "error2" << "\n";
        return 0;
    }

    // sort the Matrix to better iteration
    Poviting(Matrix, row, col);

    // To check if the Matrix is qualified for Jacobi Methods
    for (int i = 0; i < row; i++) {
        double sum = 0.0;
        for (int j = 0; j < row; j++) {
            if (j == i) continue;
            sum += Matrix[i][j];
        }
        if (Matrix[i][i] < sum) {
            GetSolution_Gaussion(Matrix, row, col);
            return 0;
        }
    }

    GetSolution_Jacobi(Matrix, row, col);

    return 0;
}

// we change the sequence of some lines
void Poviting(vector<vector<double>>& Matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        double max_val = abs(Matrix[i][i]);
        int pivot = i;

        // Find the col with the largest element in the current rowumn
        for (int k = i + 1; k < row; k++) {
            if (abs(Matrix[k][i]) > max_val) {
                max_val = abs(Matrix[k][i]);
                pivot = k;
            }
        }

        // If a better pivot is found, swap the cols
        if (pivot != i) {
            for (int j = 0; j < col; j++) {
                double tmp = Matrix[i][j];
                Matrix[i][j] = Matrix[pivot][j];
                Matrix[pivot][j] = tmp;
            }
        }
    }
}

// Jacobi Iteration Methods
void GetSolution_Jacobi(vector<vector<double>> Matrix, int row, int col) {
    int n = row;
    vector<double> x(n, 0.0);
    int max_iter = 1000;  // limit the iter times to save memory
    double tol = 1e-6;    // if the error is small than the tolerance, then end

    for (int iter = 0; iter < max_iter; iter++) {
        vector<double> x_old = x;  // Save for error calculation

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += Matrix[i][j] * x[j];
                }
            }
            x[i] = (Matrix[i][n] - sum) / Matrix[i][i];
        }

        double error = 0.0;
        for (int i = 0; i < n; i++) {  // to find the most error
            error = max(error, abs(x[i] - x_old[i]));
        }

        if (error <= tol) {
            for (int i = 0; i < n; i++) {
                double val =
                    round(x[i] * 10000) / 10000.0;  // to limit the output
                cout << val << " ";
            }
            cout << "\n";
            return;
        }
    }
    for (int i = 0; i < n; i++) cout << x[i] << " ";
    cout << "error1" << "\n";
}

// this func can print the Matrix
void CheckResult(vector<vector<double>> Matrix, int row, int col) {
    cout << "Have read " << row << " euquations" << "\n";
    cout << "And " << col - 1 << " Var nums" << "\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// if the Matrix cannot be handled by Jacobi methods, then we use Gaussion
void GetSolution_Gaussion(vector<vector<double>> Matrix, int row, int col) {
    // Gaussian process
    for (int i = 0; i < row - 1; i++)  // the location of the variable
    {
        if (Matrix[i][i] == 0) {
            continue;
        }
        for (int j = i + 1; j < row; j++) {
            double times = Matrix[j][i] / Matrix[i][i];
            for (int k = 0; k < col; k++) {
                Matrix[j][k] -= times * Matrix[i][k];
            }
        }
    }
    // we assume that the Matrix has been formalized
    int flag;  // 0:No  1:only one  2:more than one
    if (Matrix[row - 1][col - 2] == 0 && Matrix[row - 1][col - 1] != 0)
        flag = 0;
    else if (Matrix[row - 1][col - 2] != 0 && Matrix[row - 1][col - 1] != 0)
        flag = 1;
    else
        flag = 2;

    switch (flag) {
        case 0:
            cout << "error1" << "\n";
            return;
            break;
        case 2:
            cout << "error2" << "\n";
            return;
            break;
        case 1:
            break;
    }
    // when there only one set of solutions, row == col-1
    vector<double> solution(row);
    for (int i = row - 1; i >= 0; i--) {
        double sum = Matrix[i][col - 1];
        for (int j = i + 1; j < row; j++) {
            sum -= Matrix[i][j] * solution[j];
        }
        solution[i] = sum / Matrix[i][i];
    }
    for (int i = 0; i < row; i++) {
        double x = solution[i];
        int rounded = round(x * 10000);
        solution[i] = rounded / 10000.0;

        cout << solution[i] << " ";
    }
    return;
}