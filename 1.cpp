#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(const vector<string>& patterns) {
  trie t(1); // Initialize the trie with one node (root)
  int nodeCount = 1; // Counter to keep track of the number of nodes in the trie

  for (size_t i = 0; i < patterns.size(); ++i) {
    const string& pattern = patterns[i];
    int currentNode = 0; // Start from the root
    for (size_t j = 0; j < pattern.size(); ++j) {
      char c = pattern[j];
      if (t[currentNode].find(c) != t[currentNode].end()) {
        // If the edge with character 'c' already exists, follow it
        currentNode = t[currentNode][c];
      } else {
        // Otherwise, create a new node and add the edge
        edges m; // New map to represent edges
        t.push_back(m); // Add a new node
        t[currentNode][c] = nodeCount; // Create the edge
        currentNode = nodeCount; // Move to the new node
        nodeCount++; // Increment the node count
      }
    }
  }

  return t;
}

int main() {
  size_t n;
  cin >> n;
  vector<string> patterns(n);
  for (size_t i = 0; i < n; i++) {
    cin >> patterns[i];
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (edges::iterator it = t[i].begin(); it != t[i].end(); ++it) {
      cout << i << "->" << it->second << ":" << it->first << "\n";
    }
  }

  return 0;
}
