/*题目：一元线性回归

描述：
判断所给的一组<x,
y>是否满足线性关系，若满足线性关系，使用一元线性回归法拟合出x，y的线性回归方程，并通过回归方程预测x=n（n为给出值）时对应的y值。

相关知识
同学们需要自行查阅 “一元线性回归”相关知识并完成本次任务。
注意：一元线性回归常常用于经济预测过程中：一个经济指标的数值往往受许多因素影响，若其中只有一个因素是主要的、起决定性作用，则可用一元线性回归进行预测分析。然而，如果存在一组影响因素，则常常需要使用多元线性回归模型（感兴趣的同学也可以自行查阅网上资料）。

编程要求
已知输入数据皆不超过小数点后4位，浮点数类型默认为double，计算结果采用截取方式，输出保留小数点后4位小数（如果末位为0，则可以省略，具体不做要求）。

用户输入输出规范如下：

输入：输入总共n+1行。第一行为待计算的x值，接下来的n行为n个点坐标，每行为两个数字，中间使用空格隔开，分别表示坐标的x,y值。输入行数不超过11行。输入的坐标集至少由1个坐标组成，每行一个坐标。
例如 第一行输入0.4235，第二行输入0.4 0.3894，表示f(0.4)=0.3894。

输出：输出分为三行。第一行为相关系数值，第二行为回归方程，第三行为x=n时带入回归方程求出的y值。

例如，第一行输出相关系数为0.88，第二行输出回归方程为y=3x+1，第三行为x=1时的预测值输出
4。

0.88
y=3*x+1
4

若相关系数r的绝对值大于等于0.75时认为两个变量有很强的线性相关关系，若相关系数小于0.75则无法求出一元线性拟合方程，第二行输出error，第三行输出error：
0.5
error
error
注意：

输出结果保留四位小数（如果浮点数最后位为0，则可以被省略，具体不做要求）。
测试说明
平台会对你编写的代码进行测试：

测试输入：
0.4235
0.4 0.3894
0.5 0.4794

预期输出：
1
y=0.9*x+0.0294
0.4105*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
double GetSum(const vector<double>&);
double GetSquareSum(const vector<double>&);
double GetSquareSum(const vector<double>&, const vector<double>&);
void GetUserInput(vector<double>&, vector<double>&);
double CaculCorrelation(vector<double>, vector<double>);
int main() {
    vector<double> Xkdr, Ykdr;
    double PreX = 0.0;
    cin >> PreX;

    // read input
    GetUserInput(Xkdr, Ykdr);

    // cacul basic data
    double X_sum = GetSum(Xkdr);
    double Y_sum = GetSum(Ykdr);
    double X_square_sum = GetSquareSum(Xkdr);
    double Y_square_sum = GetSquareSum(Ykdr);
    double XY_sum = GetSquareSum(Xkdr, Ykdr);
    int size = Xkdr.size();

    // the variables ====> y = weight * x + bias
    double tmp1 = size * X_square_sum - X_sum * X_sum;
    double tmp2 = size * Y_square_sum - Y_sum * Y_sum;
    double tmp3 = size * XY_sum - X_sum * Y_sum;
    double R = tmp3 / sqrt(tmp1 * tmp2);
    // output
    if (abs(R) < 0.75) {
        R=(int)(R*10000)/10000.0;
        cout << R << "\n" << "error\nerror\n";
    } else {
        R = (int)(R * 10000) / 10000.0;
        double weight = tmp3 / tmp1;
        double bias = (Y_sum - weight * X_sum) / size;
        weight = (int)(weight * 10000) / 10000.0;
        bias = (int)(bias * 10000) / 10000.0;
        double prediction = PreX * weight + bias;
        prediction = (int)(prediction * 10000) / 10000.0;
        cout << R << "\n";
        cout << "y=" << weight << "*x+" << bias << "\n";
        cout << prediction << "\n";
    }

    return 0;
}

void GetUserInput(vector<double>& Xkdr, vector<double>& Ykdr) {
    cin.ignore();
    double x = 0.0, y = 0.0;
    while (cin >> x >> y) {
        Xkdr.push_back(x);
        Ykdr.push_back(y);
    }
}

double GetSum(const vector<double>& M) {
    double tmp = 0.0;
    for (int i = 0; i < M.size(); i++) tmp += M[i];
    return tmp;
}

double GetSquareSum(const vector<double>& M) {
    double tmp = 0.0;
    for (int i = 0; i < M.size(); i++) {
        tmp += M[i] * M[i];
    }
    return tmp;
}

double GetSquareSum(const vector<double>& M, const vector<double>& N) {
    double tmp = 0.0;
    for (int i = 0; i < M.size(); i++) tmp += M[i] * N[i];
    return tmp;
}

double GetAvg(const vector<double> M) {
    int size = M.size();
    double avg = 0.0;
    for (int i = 0; i < size; i++) avg += M[i] / size;
    return avg;
}
