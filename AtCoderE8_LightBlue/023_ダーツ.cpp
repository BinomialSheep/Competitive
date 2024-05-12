#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
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
  vector<int> P(N);
  rep(i, N) cin >> P[i];

  /* solve */
  // pre
  // 選ばないパターンを0点を選ぶものとする
  P.push_back(0);
  vector<int> P2;
  rep(i, N + 1) rep(j, N + 1) P2.push_back(P[i] + P[j]);
  sort(P2.begin(), P2.end());
  //  4個まで = 2個までを2回選ぶ
  ll ans = 0;
  int N2 = (N + 1) * (N + 1);
  // rep(i, N2) cout << P2[i] << " ";
  // cout << endl;
  rep(i, N2) {
    int a = P2[i];
    if (a > M) continue;
    // a + b <= Mとなるbを探す。言い換えると、M - aを超えない最大値
    // つまりM - aより大きいところの1つ前
    //(a > Mは弾いているのでindexは1以上になる)
    auto it = upper_bound(P2.begin(), P2.end(), M - a);
    if (it == P2.end()) continue;
    int b = P2[it - P2.begin() - 1];
    // cout << a << " " << b << endl;

    ans = llMax(ans, a + b);
  }

  /* output */
  cout << ans << endl;

  return 0;
}