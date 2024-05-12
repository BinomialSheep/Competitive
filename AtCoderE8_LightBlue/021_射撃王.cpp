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

vector<ll> H;
vector<ll> S;

// indexが条件を満たすかどうか
bool isOK(ll k) {
  int N = H.size();
  vector<ll> overK(N + 1);

  rep(i, N) {
    // H[i] + S[i] * j > Kとなる最初のjを考える
    if (H[i] > k) {
      overK[0]++;
      continue;
    }
    if (H[i] + S[i] * (N - 1) <= k) continue;
    ll j = (k - H[i]) / S[i] + 1;
    // if (k == 22) cout << i << ":" << j << endl;
    if (j <= N) overK[j]++;
  }
  rep(i, N) {
    if (overK[i] > i) return false;
    // 累積和に変換する
    overK[i + 1] += overK[i];
  }
  return true;
}

// 汎用的な二分探索のテンプレ
ll binarySearch() {
  ll ng = 1;
  ll ok = 1LL << 62;

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    if (isOK(mid)) {
      // cout << "OK:" << mid << endl;
      ok = mid;
    } else {
      // cout << "NG:" << mid << endl;
      ng = mid;
    }
  }
  // okな最小のindexを返す
  return ok;
}

int main() {
  /* input */
  int N;
  cin >> N;
  H.resize(N);
  S.resize(N);
  rep(i, N) cin >> H[i] >> S[i];

  /* solve */
  // 得点をk以下にできるか？を2分探索する
  // i秒時点でkを超えてるものがi個あったらダメ
  // 何秒目にkを超えるかを持っておく

  // Kを二分探索する（k以下にできる最小のkが返ってくる）
  ll ans = binarySearch();

  /* output */
  cout << ans << endl;

  return 0;
}