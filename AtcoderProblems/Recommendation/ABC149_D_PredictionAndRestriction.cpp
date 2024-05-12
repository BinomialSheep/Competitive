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
  int n, k, r, s, p;
  cin >> n >> k >> r >> s >> p;
  string t;
  cin >> t;
  // solve
  int score = 0;
  rep(i, n) {
    if (i - k >= 0 && t[i] == t[i - k]) {
      t[i] = 'a';
      continue;
    }
    if (t[i] == 'r') {
      score += p;
    } else if (t[i] == 's') {
      score += r;
    } else {
      score += s;
    }
  }

  cout << score << endl;

  return 0;
}