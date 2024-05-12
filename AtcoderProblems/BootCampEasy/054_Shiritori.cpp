#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  set<string> used;

  int n;
  cin >> n;

  char endWord;
  string word;
  bool isYes = true;
  rep(i, n) {
    cin >> word;
    if (i != 0 && endWord != word[0]) {
      isYes = false;
    }
    if (used.count(word) == 1) {
      isYes = false;
    }

    used.insert(word);
    endWord = word[word.size() - 1];
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}