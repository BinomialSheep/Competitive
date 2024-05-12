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
  // その文字が出た回数（青 - 赤）
  unordered_map<string, int> myMap;
  // in
  int n, m;
  string s, t;
  cin >> n;
  rep(i, n) {
    cin >> s;
    myMap[s]++;
  }
  cin >> m;
  rep(i, m) {
    cin >> t;
    myMap[t]--;
  }

  // solve
  int ans = 0;
  for (auto pa : myMap) {
    ans = max(ans, pa.second);
  }

  // out
  cout << ans << endl;

  return 0;
}