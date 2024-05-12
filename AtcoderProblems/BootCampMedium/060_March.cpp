#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
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
  vs S(N);
  rep(i, N) cin >> S[i];

  /* solve */
  vl cnt(5);
  rep(i, N) {
    if (S[i][0] == 'M') cnt[0]++;
    if (S[i][0] == 'A') cnt[1]++;
    if (S[i][0] == 'R') cnt[2]++;
    if (S[i][0] == 'C') cnt[3]++;
    if (S[i][0] == 'H') cnt[4]++;
  }
  ll ans = 0;
  rep(i, 3) {
    for (int j = i + 1; j < 4; j++) {
      for (int k = j + 1; k < 5; k++) {
        ans += cnt[i] * cnt[j] * cnt[k];
      }
    }
  }
  /* output */
  cout << ans << endl;

  return 0;
}