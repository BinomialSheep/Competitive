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

// indexが条件を満たすかどうか
bool isOK(int index, vector<int>& S, int key) {
  if (S[index] >= key)
    return true;
  else
    return false;
}

bool contains(int key, vector<int>& S) {
  int ng = -1;
  int ok = (int)S.size();

  while (ok - ng > 1) {
    int mid = ng + (ok - ng) / 2;

    if (isOK(mid, S, key))
      ok = mid;
    else
      ng = mid;
  }
  if (ok != (int)S.size() && S[ok] == key)
    return true;
  else
    return false;
}

int main() {
  /* input */
  int n, q;
  cin >> n;
  vector<int> S(n);
  rep(i, n) cin >> S[i];
  cin >> q;
  vector<int> T(q);
  rep(i, q) cin >> T[i];

  /* solve */
  int C = 0;
  // 二分探索で解く
  rep(i, q) {
    if (contains(T[i], S)) C++;
  }

  /* output */
  cout << C << endl;

  return 0;
}