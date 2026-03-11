#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool isKeyword(string buffer) {
    string keywords[] = {"int", "if", "else", "while"};
    for (int i = 0; i < 4; ++i) {
        if (keywords[i] == buffer) return true;
    }
    return false;
}

int main() {
    string filename = "input.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    char ch;
    string buffer;
    int tokenCount = 0;

    while (file.get(ch)) {
        if (isspace(ch)) continue;

        if (ch == '/') {
            char next = file.peek();
            if (next == '/') {
                string dummy;
                getline(file, dummy);
                continue;
            } else if (next == '*') {
                file.get();
                while (file.get(ch)) {
                    if (ch == '*' && file.peek() == '/') {
                        file.get();
                        break;
                    }
                }
                continue;
            }
        }

        if (isalpha(ch) || ch == '_') {
            buffer += ch;
            while (file.get(ch) && (isalnum(ch) || ch == '_')) {
                buffer += ch;
            }
            file.putback(ch);

            if (isKeyword(buffer)) cout << "KEYWORD: " << buffer << endl;
            else cout << "IDENTIFIER: " << buffer << endl;

            tokenCount++; // NEW: Increment for keywords/identifiers
            buffer = "";
        }

        else if (isdigit(ch)) {
            buffer += ch;
            bool isFloat = false;
            while (file.get(ch) && (isdigit(ch) || ch == '.')) {
                if (ch == '.') isFloat = true;
                buffer += ch;
            }
            file.putback(ch);
            if (isFloat) cout << "FLOAT CONSTANT: " << buffer << endl;
            else cout << "INT CONSTANT: " << buffer << endl;

            tokenCount++;
            buffer = "";
        }

        else if (ch == '+' || ch == '-' || ch == '=' || ch == '*') {
            if (ch == '=') {
                if (file.peek() == '=') {
                    file.get();
                    cout << "OPERATOR: ==" << endl;
                } else {
                    cout << "OPERATOR: =" << endl;
                }
            } else {
                cout << "OPERATOR: " << ch << endl;
            }

            tokenCount++;
        }
    }

    file.close();


    cout << "Total Tokens Found: " << tokenCount << endl;


    return 0;
}
