#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

void GetUserInput(vector<string>&);  // get input
void Print(const vector<string>&);   // print vector to check result
vector<string> Tokenize(const string& input_data);  // tokenize the string data
int JudgeType(const char& a);  // divide the character by rule
bool CompareTokens(const vector<string>&, const vector<string>&,
                   const double&);  // compare the two tokens sequence

int main() {
    // read the input
    vector<string> INPUT;
    GetUserInput(INPUT);
    Print(INPUT);

    vector<string> predicted_tokens;
    vector<string> real_tokens;
    double error = stod(INPUT[0]);  // get the error

    predicted_tokens = Tokenize(INPUT[1]);
    real_tokens = Tokenize(INPUT[2]);
    // cout << "The predicted answer token:" << "\n";
    // Print(predicted_tokens);
    // cout << "The real answer token" << "\n";
    // Print(real_tokens);

    // compare the two token sequences
    bool Matched = CompareTokens(predicted_tokens, real_tokens, error);
    if (Matched)
        cout << "Y" << "\n";
    else
        cout << "N" << "\n";

    return 0;
}

// This function can split the string data into tokens, with the white space
// removed.
vector<string> Tokenize(const string& input_data) {
    int size = input_data.size();
    int i = 0;
    vector<string> tokens;
    while (i < size) {
        string tmp = "";
        char head = input_data[i];

        // this step will remove the whitespace
        if (isspace(head)) {
            i++;
            continue;
        }

        int tag_head = JudgeType(head);

        // every icon is considered as a token
        if (tag_head == 0) {
            tokens.push_back({head});
            i++;
            continue;
        }

        // if the character is letter
        if (tag_head < 0) {
            tmp += head;
            int j = i + 1;
            while (j < size) {
                if (JudgeType(input_data[j]) < 0) {
                    tmp += input_data[j];
                    j++;
                } else
                    break;
            }
            tokens.push_back(tmp);
            i = j;
        }

        // if the character is number
        if (tag_head > 0) {
            tmp += head;
            int j = i + 1;
            while (j < size) {
                if (JudgeType(input_data[j]) > 0) {
                    tmp += input_data[j];
                    j++;
                } else
                    break;
            }
            tokens.push_back(tmp);
            i = j;
        }
    }

    return tokens;
}

// 0 for icon; 1 for number; -1 for letter
// This function as well as isspace() serve as dividing the characters
int JudgeType(const char& data) {
    bool flag_icon = data == '+' || data == '-' || data == '=';
    bool flag_number = (data > 47 && data < 58) || (data == '.');
    bool flag_letter = (data > 96 && data < 123);

    if (flag_icon) return 0;
    if (flag_letter) return -1;
    if (flag_number) return 1;

    return 0;
}

bool CompareTokens(const vector<string>& predicted_tokens,
                   const vector<string>& real_tokens, const double& error) {
    // if the size are different, then it must be wrong
    if (predicted_tokens.size() != real_tokens.size()) {
        return false;
    }

    // match the result token by token
    int size = predicted_tokens.size();
    for (int i = 0; i < size; i++) {
        // we first try to convert the number (include the negative number)
        try {
            double num1 = stod(predicted_tokens[i]);
            double num2 = stod(real_tokens[i]);
            int times = 1 / error;
            int num1_int = num1 * times;
            int num2_int = num2 * times;

            if (fabs(num1_int - num2_int) > error * times) {
                return false;
            }
        }
        // this handles the icon or letter condition
        catch (const invalid_argument& e) {
            if (predicted_tokens[i] != real_tokens[i]) {
                return false;
            }
        }
    }
    // If all the tokens match, the answer is supposed to be right
    return true;
}

void GetUserInput(vector<string>& INPUT) {
    string read_input = "";
    while (getline(cin, read_input)) {
        cout << read_input << "\n";
        if (read_input.empty()) break;
        if (read_input[0] == '#') {
            string tmp = read_input.substr(1, read_input.size() - 1);
            INPUT.push_back(tmp);
        } else {
            int size = INPUT.size();
            INPUT[size - 1] += read_input;
        }
        // cin.ignore();
    }

    return;
}

void Print(const vector<string>& Input) {
    int size = Input.size();
    for (int i = 0; i < size; i++) cout << Input[i] << "\n";
    return;
}