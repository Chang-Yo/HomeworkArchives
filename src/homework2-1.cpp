#include <iostream>
#include <string>
#include<cmath>
std::string ConvertToString(const int&);
std::string ConvertToString(const long&);

int main() {
    bool flag1 = false;  // 判断是不是质数
    int delta = 0;
    long MAX_NUM = 2147483647;
    // 循环判断找到增量
    while (!flag1) {
        delta += 2;

        bool flag2 = true;
        // 判断增加后的数是不是质数
        for (int i = 3; i < long(sqrt(MAX_NUM / 2.0 + delta / 2.0 + 1)); i++) {
            int tmp = MAX_NUM % i + delta % i;
            if (tmp % i == 0) {
                flag2 = false;
                break;
            }
        }

        flag1 = flag2;
    }

    // 由于计算机无法存储大于MAX_NUM的数，我们需要转化为字符串
    std::string basenum = std::to_string(MAX_NUM);
    std::string addnum = std::to_string(delta);

    // 将字符串形式下的数字相加
    int len1 = addnum.length();
    int len2 = basenum.length();
    int pos = 0;
    bool carry = false;
    std::string newnum = "";
    while (pos < len1 || carry) {
        int tmp = basenum[len2 - pos - 1] - '0' + addnum[len1 - 1 - pos] - '0' +
                  carry;
        if (tmp >= 10) {
            newnum = (char)(tmp - 10+'0') + newnum;
            carry = true;
            pos++;
        }else {
            newnum = (char)(tmp+'0') + newnum;
            pos++;
        }
    }
    while (pos < len2) {
        newnum = basenum[len2 - 1 - pos] + newnum;  // 补足高位
        pos++;
    }

    std::cout << newnum << '\n';
    return 0;
}
