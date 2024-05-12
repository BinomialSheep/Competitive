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
  int T;
  cin >> T;

  /* solve */
  rep(i, T) {
    int N;
    cin >> N;
    deque<int> D;
    rep(j, N) {
      int d;
      cin >> d;
      D.push_back(d);
    }

    // 貪欲法
    int ans = 0;
    int last = -1;
    rep(j, N) {
      int f = D.front();
      int b = D.back();
      if (last > f) {
        D.pop_front();
      } else if (last > b) {
        D.pop_back();
      } else if (f <= b) {
        last = f;
        D.pop_front();
        ans++;
      } else {
        last = b;
        D.pop_back();
        ans++;
      }
    }
    cout << "Case #" << i + 1 << ": ";
    cout << ans << endl;
  }

  /* output */

  return 0;
}