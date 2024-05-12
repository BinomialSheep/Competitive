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
  int N;
  cin >> N;
  vector<string> s(N);
  vector<string> t(N);
  rep(i, N) { cin >> s[i] >> t[i]; }

  /* solve */
  rep(i, N) {
    int cnt1 = 0;
    int cnt2 = 0;

    rep(j, N) {
      if (s[i] == s[j] || s[i] == t[j]) {
        cnt1++;
      }
      if (t[i] == s[j] || t[i] == t[j]) {
        cnt2++;
      }
    }
    if (cnt1 >= 2 && cnt2 >= 2) {
      cout << "No" << endl;
      return 0;
    }
  }

  /* output */
  cout << "Yes" << endl;

  return 0;
}