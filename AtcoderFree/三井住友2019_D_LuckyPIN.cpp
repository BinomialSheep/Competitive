#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  string s;
  cin >> n >> s;

  // x用のメモ
  // isCheckX[i]xが探索済みならもう調べる必要はない（右側に向かって調べているので探索済み）
  vector<bool> isCheckX(10, false);

  // x, y用のメモ
  vector<vector<bool>> isCheckXY(10, vector<bool>(10, false));

  unordered_set<string> set;

  for (int x = 0; x < n - 2; x++) {
    if (isCheckX[s[x] - '0']) continue;
    isCheckX[s[x] - '0'] = true;
    for (int y = x + 1; y < n - 1; y++) {
      if (isCheckXY[s[x] - '0'][s[y] - '0']) continue;
      isCheckXY[s[x] - '0'][s[y] - '0'] = true;
      for (int z = y + 1; z < n; z++) {
        string pass = {s[x], s[y], s[z]};
        set.insert(pass);
      }
    }
  }

  cout << set.size() << endl;

  return 0;
}