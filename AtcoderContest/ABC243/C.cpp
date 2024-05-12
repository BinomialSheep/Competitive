#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  // in
  int n;
  cin >> n;
  vector<int> X(n);
  vector<int> Y(n);
  rep(i, n) cin >> X[i] >> Y[i];
  string S;
  cin >> S;
  // solve
  // y座標, index
  map<int, vector<int>> myMap;
  rep(i, n) { myMap[Y[i]].emplace_back(i); }
  // 衝突判定

  for (auto myPair : myMap) {
    // Lのmaxと、Rのminを求める
    int left = 0;
    int right = 1001001000;
    for (auto index : myPair.second) {
      if (S[index] == 'L') {
        left = max(X[index], left);
      } else {
        right = min(X[index], right);
      }
    }
    if (left > right) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  // out
  cout << "No" << endl;

  return 0;
}