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
  vector<int> D(N);
  rep(i, N) cin >> D[i];
  int M;
  cin >> M;
  vector<int> T(M);
  rep(i, M) cin >> T[i];

  /* solve */
  unordered_multiset<int> mySet;
  rep(i, N) { mySet.insert(D[i]); }
  rep(i, M) {
    auto it = mySet.find(T[i]);
    if (it == mySet.end()) {
      cout << "NO" << endl;
      return 0;
    }
    mySet.erase(it);
  }

  /* output */
  cout << "YES" << endl;

  return 0;
}