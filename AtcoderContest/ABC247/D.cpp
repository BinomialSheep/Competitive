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
  int Q;
  cin >> Q;
  deque<pair<int, int>> que;
  rep(i, Q) {
    int query;
    cin >> query;
    if (query == 1) {
      int x, c;
      cin >> x >> c;
      que.emplace_back(x, c);
    } else {
      int c;
      cin >> c;
      ll sum = 0;
      while (true) {
        auto p = que.front();
        que.pop_front();
        if (p.second == c) {
          ll num = (ll)p.first * p.second;
          sum += num;
          break;
        } else if (p.second > c) {
          ll num = (ll)p.first * c;
          sum += num;
          que.emplace_front(p.first, p.second - c);
          break;
        } else {
          ll num = (ll)p.first * p.second;
          sum += num;
          c -= p.second;
        }
      }
      cout << sum << endl;
    }
  }

  /* solve */

  /* output */

  return 0;
}