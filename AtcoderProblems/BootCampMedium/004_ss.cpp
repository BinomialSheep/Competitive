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
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  string s;
  cin >> s;
  /* solve */
  while (true) {
    // 2文字削除
    s.pop_back();
    s.pop_back();
    // 偶文字列判定
    int n = s.size() / 2;
    bool flag = true;
    rep(i, n) {
      if (s[i] != s[i + n]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << 2 * n << endl;
      return 0;
    }
  }

  return 0;
}