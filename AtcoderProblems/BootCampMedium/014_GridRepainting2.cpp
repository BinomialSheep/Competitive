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
  int h, w;
  cin >> h >> w;
  vector<vector<char>> s(h + 2, vector<char>(w + 2, '.'));
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> s[i][j];
    }
  }

  /* solve */
  vector<int> a = {-1, 0, 1, 0};
  vector<int> b = {0, 1, 0, -1};

  /* output */
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      if (s[i][j] == '.') continue;
      bool flag = false;
      rep(k, 4) {
        if (s[i + a[k]][j + b[k]] == '#') {
          flag = true;
          break;
        }
      }
      if (!flag) {
        cout << "No" << endl;
        return 0;
      }
    }
  }
  cout << "Yes" << endl;

  return 0;
}