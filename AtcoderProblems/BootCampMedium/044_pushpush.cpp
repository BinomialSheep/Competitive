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
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  /* solve */
  deque<int> b;
  rep(i, n) {
    if (i % 2 == 0) {
      b.push_back(a[i]);
    } else {
      b.push_front(a[i]);
    }
  }

  if (n % 2 == 1) {
    reverse(b.begin(), b.end());
  }

  /* output */
  rep(i, n) {
    cout << b.front() << " ";
    b.pop_front();
  }
  cout << endl;

  return 0;
}