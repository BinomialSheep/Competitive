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
  int X;
  cin >> X;

  /* solve */
  ll sum = 0;
  int i = 0;
  while (sum < X) {
    i++;
    sum += i;
  }

  cout << i << endl;

  /*
  int ans = 0;
  unordered_set<int> memo;
  vector<int> old;
  vector<int> now;
  old.push_back(0);
  memo.insert(0);
  while (true) {
    ans++;
    for (int n : mySet) {
      if (n == X || n + ans == X || n - ans == X) {
        cout << ans << endl;
        return 0;
      }
      mySet.insert(n);
      mySet.insert(n + ans);
      mySet.insert(n - ans);
    }
    last = now;
  }
  */

  /* output */

  return 0;
}