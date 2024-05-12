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

int stupidity(string s) {
  int ans = 0;

  while (true) {
    int thisCnt = 0;
    rep(i, s.size() - 1) {
      if (s[i] == 'B' && s[i + 1] == 'W') {
        swap(s[i], s[i + 1]);
        thisCnt++;
      }
    }
    // 交換できなくなったら終わり
    if (thisCnt == 0) break;
    ans += thisCnt;
  }

  return ans;
}

int main() {
  /* input */
  string s;
  cin >> s;
  /* solve */
  // 最終的に一般形はWW..WB..BBとなる
  // つまり、途中にあるWが左詰めされるように隣接スワップする回数を求めればいい
  ll ans = 0;
  // Bが現れる最初のindex - 1
  int bi = 0;
  rep(i, s.size()) {
    if (s[i] == 'B') continue;
    // whiteIndexの位置まで隣接スワップする回数をansに足す
    ans += i - bi;
    bi++;
  }

  // cout << (ans == stupidity(s) ? "Yes" : "No") << endl;

  /* output */
  cout << ans << endl;

  return 0;
}