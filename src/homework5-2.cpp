/*描述：
我们读取一个表格，并且进行按列排序。用户输入列号，正向（ascend）或者逆向（descend）；
输出为按照字符串方式进行排序后的表格。这里，输入的表格数据的分割符号为tab（制表符），输出的分隔符也为tab。
如果列号超出了表格的范围，则不起作用。
例如：
2 ascend
0005    张三    90
0006    李四    85
0007    王五    88

输出为：
0006    李四    85
0007    王五    88
0005    张三    90

注意：本题目中，所有比较均为字符串方式的比较，所设计的测试数据的输出结果为唯一。
如需进一步提升程序健壮性（如上面例子中出现同名/同分的同学），则自行完善*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void SortAndPrint(vector<vector<string>>& sheet, const int col_order, bool);
int main() {
    int col_order = 0;
    string order = "";
    cin >> col_order;
    cin >> order;
    bool flag = (order == "ascend");
    vector<vector<string>> sheet;
    string element = "";
    cin.ignore();
    while (getline(cin, element)) {
        if (element.empty()) break;
        istringstream istr(element);
        vector<string> Newline;
        string tmp = "";
        while (istr >> tmp) {
            Newline.push_back(tmp);
        }
        if (!Newline.empty()) {
            sheet.push_back(Newline);
        }
    }

    // int line = sheet.size();
    // int col = sheet[0].size();

    SortAndPrint(sheet, col_order, flag);

    return 0;
}

void SortAndPrint(vector<vector<string>>& sheet, const int col_order,
                  bool flag) {
    int line = sheet.size();
    int col = sheet[0].size();
    // detect whether the order_col is beyond
    if (col_order > col) {
        cout << "Column Error. The Maximun column is " << col << "\n";
        return;
    }

    // we use bubble sort

    for (int i = 0; i < line - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < line - i - 1; j++) {
            if (flag) {
                if (sheet[j][col_order] >= sheet[j + 1][col_order]) {
                    std::swap(sheet[j], sheet[j + 1]);
                    swapped = true;
                }
            } else {
                if (sheet[j][col_order] < sheet[j + 1][col_order]) {
                    std::swap(sheet[j], sheet[j + 1]);
                    swapped = true;
                }
            }
        }
        if (!swapped) break;
    }

    /*
        sort(sheet.begin(),sheet.end(),[col_order, flag](const vector<string>&
       v1, const vector<string>& v2) { if(flag)// we use lambda expression to
       transfer the 'comp' call return v1[col_order] < v2[col_order]; else
                         return v1[col_order] > v2[col_order];
                  });
        */

    // print the result
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < col; j++) {
            cout << sheet[i][j] << " ";
        }
        cout << "\n";
    }

    return;
}