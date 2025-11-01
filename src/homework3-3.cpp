// requirement:
/*任务描述
编写程序，使用高斯消去法实现线性方程组求解，系数为整数或小数。

相关知识
列主元高斯消去法/雅可比迭代法。

编程要求
（1）读入线性方程组
    程序的输入共有若干行，通过每一行输入，构建一个线性方程（如3 4 10
代表线性方程为3*x1+4*x2=10）。 （2）利用高斯消去法计算 利用高斯消去法进行求解。
（3）输出结果
    （a）若有唯一解，依次输出所有变量的解，如果解为浮点数，数字最多保留至小数点后4位（截断或者四舍五入的方式均可）。
    （b）若方程组无解（例如，0*x1=5），则输出error1；
    （c）若方程组存在多个解（例如，0*x2=0），则输出error2；
*/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
void GetSolution(vector<vector<double>>, int, int);
int main() {
    string Input = "";
    vector<vector<double>> Matrix;
    int col = 0;
    int row = 0;
    //  read the input and create matrix
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

    cout << "Have read " << col << " euqlations" << "\n";
    cout << "And " << row - 1 << " Var nums" << "\n";
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << "\n";
    }
    /*
        // to format the matrix
        for (int i = 0; i < col; i++) {
            if (Matrix[i].size() < row) {
                int tmp = Matrix[i].back();
                while (Matrix[i].size() < row - 1) {
                    Matrix[i].push_back(0);
                }
                Matrix[i].push_back(tmp);
            }
        }
    */
    // Gaussian process
    for (int i = 0; i < col - 1; i++)  // the location of the variable
    {
        for (int j = i + 1; j < col; j++) {
            double times = Matrix[j][i] / Matrix[i][i];
            for (int k = 0; k < col; k++) {
                Matrix[j][k] -= times * Matrix[i][k];
            }
        }
    }

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
        printf("%.4f\n", solution[i]);
    }
    return;
}