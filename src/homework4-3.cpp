#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

double precision = 1e-4;//to control the error of double number
double Lagrange(vector<double>&, vector<double>&, const double&);
bool CrossJudge(vector<double>&, vector<double>&);
double AreaCacul(vector<double>&, vector<double>&);
bool OnSegment(vector<double>&, vector<double>&, int, int, int);

// to caculate the cross product
double det(const double& x1, const double& y1, const double& x2,
           const double& y2) {
    return x1 * y2 - x2 * y1;
}

// to caculate the cross product within 3 dots
double Cross(vector<double>& Xkdr, vector<double>& Ykdr, int a, int b, int c) {
    return det(Xkdr[b] - Xkdr[a], Ykdr[b] - Ykdr[a], Xkdr[c] - Xkdr[a],
               Ykdr[c] - Ykdr[a]);
}

// to judge whether the product are 0
int DetCheck(const double& m) {
    if (fabs(m) < precision) return 0;
    return (m > 0) ? 1 : -1;
}

//-------the main point-------
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
    double yy = Lagrange(Xkdr, Ykdr, xx);
    Xkdr.push_back(xx);
    Ykdr.push_back(yy);  // append the xx,yy

    if (CrossJudge(Xkdr, Ykdr)) {
        cout << "Crossed" << '\n';
    } else {
        double Area = AreaCacul(Xkdr, Ykdr);
        cout << Area << "\n";
    }
    return 0;
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

// This functions judge whether the lines are crossed
bool CrossJudge(vector<double>& Xkdr, vector<double>& Ykdr) {
    int n = Xkdr.size();
    //  由于线段是顺次连接的，所以我们判断的方法是任意不相邻线段之间是否存在交点
    //  假如发现叉乘为0，则判断是否为共线情况
    for (int i = 0; i < n; i++) {
        int a = i;
        int b = (i + 1) / n;

        // the secondary loop
        for (int j = i + 2; j < n - 1; j++) {
            int c = j;
            int d = (j + 1) % n;

            double dir_1 = Cross(Xkdr, Ykdr, a, b, c);  // c ---> ab
            double dir_2 = Cross(Xkdr, Ykdr, a, b, d);  // d --->ab
            double dir_3 = Cross(Xkdr, Ykdr, c, d, a);  // a ---> cd
            double dir_4 = Cross(Xkdr, Ykdr, c, d, a);  // b ---> vd
            int signal12 = DetCheck(dir_1) * DetCheck(dir_2);
            int signal34 = DetCheck(dir_3) * DetCheck(dir_4);

            if (signal12 < 0 && signal34 < 0) return true;

            // if on the same line
            if (dir_1 == 0 && OnSegment(Xkdr, Ykdr, a, b, c)) return true;
            if (dir_2 == 0 && OnSegment(Xkdr, Ykdr, a, b, d)) return true;
            if (dir_3 == 0 && OnSegment(Xkdr, Ykdr, c, d, a)) return true;
            if (dir_4 == 0 && OnSegment(Xkdr, Ykdr, c, d, b)) return true;
        }
    }
    return false;
}

// this function caculate the Area of multi-segment shapes
double AreaCacul(vector<double>& Xkdr, vector<double>& Ykdr) {
    int size = Xkdr.size();
    double sum = 0.0;
    for (int i = 0; i < size - 1; i++) {
        sum += Xkdr[i] * Ykdr[i + 1] - Xkdr[i + 1] * Ykdr[i];
    }
    sum += Xkdr[size - 1] * Ykdr[0] - Xkdr[0] * Ykdr[size - 1];
    sum = abs(sum / 2.0);
    return sum;
}

// to judge whether the dot c is on the line ab
bool OnSegment(vector<double>& Xkdr, vector<double>& Ykdr, int a, int b,
               int c) {
    return (
        Xkdr[c] >= min(Xkdr[a], Xkdr[b]) && Xkdr[c] <= max(Xkdr[a], Xkdr[b]) &&
        Ykdr[c] >= min(Ykdr[a], Ykdr[b]) && Ykdr[c] <= max(Ykdr[a], Ykdr[b]));
}