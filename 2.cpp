#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int Letters = 4;
const int NA = -1;

struct Node {
    vector<int> next;
    bool patternEnd;

    Node() : next(Letters, NA), patternEnd(false) {}
};

int letterToIndex(char letter) {
    switch (letter) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: assert(false); return -1;
    }
}

void build_trie(const vector<string>& patterns, vector<Node>& t) {
    for (const string& pattern : patterns) {
        int x = 0;
        for (char letter : pattern) {
            int index = letterToIndex(letter);
            if (t[x].next[index] == NA) {
                t[x].next[index] = t.size();
                t.emplace_back();
            }
            x = t[x].next[index];
        }
        t[x].patternEnd = true;
    }
}

vector<int> solve(const string& text, const vector<Node>& t) {
    vector<int> result;
    for (int i = 0; i < text.size(); ++i) {
        int x = 0;
        for (int j = i; j < text.size(); ++j) {
            int index = letterToIndex(text[j]);
            if (t[x].patternEnd) {
                result.push_back(i);
                break;
            }
            if (t[x].next[index] == NA) {
                break;
            }
            x = t[x].next[index];
        }
    }
    return result;
}

int main() {
    string text;
    cin >> text;

    int n;
    cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; ++i) {
        cin >> patterns[i];
    }

    vector<Node> trie(1);
    build_trie(patterns, trie);

    vector<int> occurrences = solve(text, trie);

    for (int i = 0; i < occurrences.size(); ++i) {
        cout << occurrences[i];
        if (i + 1 < occurrences.size()) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
