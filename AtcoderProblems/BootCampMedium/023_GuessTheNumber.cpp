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
  int N, M;
  cin >> N >> M;
  vector<int> s(M);
  vector<int> c(M);
  rep(i, M) cin >> s[i] >> c[i];

  /* solve */
  if (N == 1) {
    for (int i = 0; i < 10; i++) {
      bool flag = true;
      rep(j, M) {
        if (i != c[j]) {
          flag = false;
        }
      }
      if (flag) {
        cout << i << endl;
        return 0;
      }
    }
  }
  if (N == 2) {
    for (int i = 10; i < 100; i++) {
      bool flag = true;
      rep(j, M) {
        if (s[j] == 1) {
          int m = i / 10;
          if (c[j] == 0) {
            cout << -1 << endl;
            return 0;
          }
          if (m != c[j]) flag = false;
        } else {
          int m = i % 10;
          if (m != c[j]) flag = false;
        }
      }
      if (flag) {
        cout << i << endl;
        return 0;
      }
    }
  }
  if (N == 3) {
    for (int i = 100; i < 1000; i++) {
      bool flag = true;
      rep(j, M) {
        if (s[j] == 1) {
          int m = i / 100;
          if (c[j] == 0) {
            cout << -1 << endl;
            return 0;
          }
          if (m != c[j]) flag = false;
        } else if (s[j] == 2) {
          int m = (i % 100) / 10;
          if (c[j] == 0) {
            cout << -1 << endl;
            return 0;
          }
          if (m != c[j]) flag = false;
        } else {
          int m = i % 10;
          if (m != c[j]) flag = false;
        }
      }
      if (flag) {
        cout << i << endl;
        return 0;
      }
    }
  }
  cout << -1 << endl;

  /* output */

  return 0;
}