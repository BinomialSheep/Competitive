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
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vi A(N);
  rep(i, N) cin >> A[i];

  /* solve */

  if (N == 1) {
    cout << (A[0] <= W ? 1 : 0) << endl;
    return 0;
  }
  if (N == 2) {
    set<int> cnt;
    if (A[0] <= W) cnt.insert(A[0]);
    if (A[1] <= W) cnt.insert(A[1]);
    if (A[0] + A[1] <= W) cnt.insert(A[0] + A[1]);
    cout << cnt.size() << endl;
    return 0;
  }
  unordered_set<int> cnt;
  rep(i, N - 2) {
    for (int j = i + 1; j < N - 1; j++) {
      for (int k = j + 1; k < N; k++) {
        if (A[i] <= W) cnt.insert(A[i]);
        if (A[j] <= W) cnt.insert(A[j]);
        if (A[k] <= W) cnt.insert(A[k]);
        if (A[i] + A[j] <= W) cnt.insert(A[i] + A[j]);
        if (A[j] + A[k] <= W) cnt.insert(A[j] + A[k]);
        if (A[i] + A[k] <= W) cnt.insert(A[i] + A[k]);
        if (A[i] + A[j] + A[k] <= W) cnt.insert(A[i] + A[j] + A[k]);
      }
    }
  }

  /* output */
  cout << cnt.size() << endl;

  return 0;
}