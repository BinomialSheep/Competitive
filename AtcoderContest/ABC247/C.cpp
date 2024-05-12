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

  if (N == 1) {
    cout << 1 << endl;
    return 0;
  }

  /* solve */
  deque<int> copyQ;
  copyQ.push_back(1);
  for (int i = 2; i <= N; i++) {
    deque<int> newQ;
    newQ.push_back(i);
    while (!copyQ.empty()) {
      int n = copyQ.front();
      copyQ.pop_front();
      newQ.push_back(n);
      newQ.push_front(n);
    }
    copyQ = newQ;
  }

  /* output */
  while (!copyQ.empty()) {
    cout << copyQ.front() << " ";
    copyQ.pop_front();
  }
  cout << endl;

  return 0;
}