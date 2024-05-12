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
  int N, K;
  cin >> N >> K;
  vector<string> S(N);
  rep(i, N) cin >> S[i];

  /* solve */
  int ans = 0;
  rep(bit, 1 << N) {
    // 英小文字の出現をカウント
    vector<int> num(26);
    rep(i, N) {
      if (bit & (1 << i)) {
        rep(j, S[i].size()) { num[S[i][j] - 'a']++; }
      }
    }
    // 種類をカウント
    int kind = 0;
    rep(i, 26) {
      if (num[i] == K) kind++;
    }
    ans = max(ans, kind);
  }

  /* output */
  cout << ans << endl;

  return 0;
}