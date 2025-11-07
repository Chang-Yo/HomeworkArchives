#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double> Xkdr, YKdr;
    double xx, x_get, y_get;

    //Get the input data
    cin >> xx;
    while (cin >> x_get >> y_get) {
        Xkdr.push_back(x_get);
        YKdr.push_back(y_get);
    }
    int size = Xkdr.size();

    // get the prediction
    double yy=0.0;
    for (int i = 0; i < size; i++) {
        double sum = 1.0;
        for (int j = 0; j < size; j++) {
            if(j!=i) sum=sum*(xx-Xkdr[j])/(Xkdr[i]-Xkdr[j]);
        }
        yy+=YKdr[i]*sum;
    }

    cout << yy << "\n";

    return 0;
}