#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
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
  int n, k, x;
  cin >> n >> k >> x;
  priority_queue<int> a;
  rep(i, n) {
    int temp;
    cin >> temp;
    a.push(temp);
  }
  /* solve */
  while (k != 0 && !a.empty()) {
    int temp = a.top();
    a.pop();

    int mai = temp / x;
    if (mai == 0) {
      k--;
      continue;
    }
    if (k >= mai) {
      temp -= x * mai;
      k -= mai;
      a.push(temp);
    } else {
      temp -= x * k;
      k = 0;
      a.push(temp);
    }
  }

  /* output */
  ll sum = 0;
  while (!a.empty()) {
    sum += a.top();
    a.pop();
  }
  cout << sum << endl;

  return 0;
}