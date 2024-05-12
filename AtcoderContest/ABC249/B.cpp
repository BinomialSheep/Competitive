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
  // rep(i, 52) cout << (char)('a' + i) << char('A' + i) << endl;
  string S;
  cin >> S;

  /* solve */
  vector<int> ko(26);
  vector<int> oo(26);
  rep(i, S.size()) {
    // 小文字
    if ('a' <= S[i] && S[i] <= 'a' + 25) {
      ko[S[i] - 'a']++;
    } else {
      oo[S[i] - 'A']++;
    }
  }

  /* output */
  bool kof = false;
  bool oof = false;
  rep(i, 26) {
    if (ko[i] > 1 || oo[i] > 1) {
      cout << "No" << endl;
      return 0;
    }
    if (ko[i] == 1) kof = true;
    if (oo[i] == 1) oof = true;
  }

  cout << (kof && oof ? "Yes" : "No") << endl;

  return 0;
}