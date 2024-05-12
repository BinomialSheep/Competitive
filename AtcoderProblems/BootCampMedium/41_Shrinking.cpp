#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
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

  // 0チェック
  bool flag0 = true;
  rep(i, s.size()) {
    if (s[i] != s[i + 1]) {
      flag0 = false;
      break;
    }
  }
  if (flag0) {
    cout << 0 << endl;
    return 0;
  }

  /* solve */
  int ans = MAX;
  rep(i, 26) {
    // 何に合わせるか
    char c = 'a' + i;
    bool flag = true;
    string t = s;
    int size = (int)t.size();
    int num = 0;

    // 通常
    while (size != 1) {
      flag = false;
      rep(j, size - 1) {
        if (t[j] != c) {
          t[j] = t[j + 1];
          flag = true;
        }
      }
      // if (c == 'a') {
      //   cout << t << endl;
      // }
      if (flag || t[size - 1] != c) {
        size--;
        num++;
      } else {
        break;
      }
    }
    // cout << t << ":" << num << endl;
    ans = min(ans, num);
  }

  /* output */
  cout << ans << endl;

  return 0;
}