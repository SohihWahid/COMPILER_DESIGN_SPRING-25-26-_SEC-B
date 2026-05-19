#include <iostream>
#include <string>
#include <vector>

using namespace std;

int transition[6][2] = {
    {1, 2},
    {3, 4},
    {3, 2},
    {3, 2},
    {3, 5},
    {3, 5},
};

bool accepting[6] = {true, true, true, true, true, true};

pair<bool, string> run(const string& input) {
    int state = 0;
    string path = "S0";

    for (char c : input) {
        if (c != 'a' && c != 'b')
            return {false, path + " --> DEAD"};
        state = transition[state][c == 'b' ? 1 : 0];
        path += " --" + string(1, c) + "--> S" + to_string(state);
    }

    return {accepting[state], path};
}

int main() {
    vector<string> tests = {"ab", "a", "bba", "abab", "b2c"};

    cout << "RE = ab* + [a*(b+)* + ab]+" << endl;
    cout << "-------------------------------" << endl;

    for (const string& t : tests) {
        auto [accepted, path] = run(t);
        string label = t.empty() ? "(empty)" : "\"" + t + "\"";
        cout << "Input : " << label << endl;
        cout << "Path  : " << path << endl;
        cout << "Result: " << (accepted ? "ACCEPTED" : "REJECTED") << endl;
        cout << endl;
    }

    return 0;
}
