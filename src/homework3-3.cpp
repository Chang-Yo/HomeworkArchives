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
    double weight = tmp3 / tmp1;
    double bias = (Y_sum - weight * X_sum) / size;
    double R = tmp3 / sqrt(tmp1 * tmp2);
    // output
    if (abs(R) < 0.75) {
        R=(int)(R*10000)/10000.0;
        cout << R << "\n" << "error\nerror\n";
    } else {
        R = (int)(R * 10000) / 10000.0;
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
