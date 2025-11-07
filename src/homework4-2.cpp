#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double Lagrange(vector<double>&, vector<double>&, const double&);
double Romberg(vector<double>&, vector<double>&);
int main() {
    vector<double> Xkdr, Ykdr;
    double xx, x_get, y_get;

    // get the input
    cin >> xx;  // According to the requirement, the xx is the right border of
                // defination
    while (cin >> x_get >> y_get) {
        Xkdr.push_back(x_get);
        Ykdr.push_back(y_get);
    }
    double result = Romberg(Xkdr, Ykdr);
    result = round(result * 100) / 100.0;
    cout << result << "\n";

    return 0;
}

double Romberg(vector<double>& Xkdr, vector<double>& Ykdr) {
    double a = 0.0, b = 0.0;
    // determine the [a,b]
    int size = Xkdr.size();
    for (int i = 0; i < size; i++) {
        a = (a < Xkdr[i]) ? a : Xkdr[i];
        b = (b > Xkdr[i]) ? b : Xkdr[i];
    }
    double tolerance = 1e-5;
    const int iter_time = 3;

    vector<vector<double>> T(iter_time, vector<double>(iter_time, 0.0));
    // the initial T0
    T[0][0] =
        0.5 * (b - a) * (Lagrange(Xkdr, Ykdr, a) + Lagrange(Xkdr, Ykdr, b));

    // iteration
    for (int i = 1; i < iter_time; i++) {
        double h = (b - a) / pow(2, i);
        double sum = 0.0;
        for (int k = 1; k <= pow(2, i - 1); k++) {
            double x_inner =
                (2 * k - 1) * h + a;  // we skip the dot already existing
            sum += Lagrange(Xkdr, Ykdr, x_inner);
        }
        T[i][0] = 0.5 * T[i - 1][0] + h * sum;

        // Richardson 外推法，加快收敛速度
        for (int k = 1; k <= i; k++) {
            double elem = pow(4, k);
            T[i][k] = (elem * T[i][k - 1] - T[i - 1][k - 1]) / (elem - 1);
        }

        if (fabs(T[i][i] - T[i - 1][i - 1]) < tolerance) {
            return T[i][i];
        }
    }
    return T[iter_time - 1][iter_time - 1];
}

// this function return a double value as a prediction P(xx)
double Lagrange(vector<double>& Xkdr, vector<double>& Ykdr, const double& xx) {
    int size = Xkdr.size();
    double yy = 0.0;
    for (int i = 0; i < size; i++) {
        double sum = 1.0;
        for (int j = 0; j < size; j++) {
            if (j != i) sum = sum * (xx - Xkdr[j]) / (Xkdr[i] - Xkdr[j]);
        }
        yy += Ykdr[i] * sum;
    }
    return yy;
}
