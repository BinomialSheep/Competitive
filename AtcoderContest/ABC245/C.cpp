#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
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
  int n, k;
  cin >> n >> k;
  vector<int> A(n);
  vector<int> B(n);
  rep(i, n) cin >> A[i];
  rep(i, n) cin >> B[i];

  /* solve */
  // i個目でどちらがOKか（0：どちらでもダメ, 1：AのみOK, 2:BのみOK,
  // 3：どちらでもOK）
  vector<int> OK(n, 0);
  OK[0] = 3;
  for (int i = 1; i < n; i++) {
    if (OK[i - 1] == 0) {
      cout << "No" << endl;
      return 0;
    } else if (OK[i - 1] == 1) {
      if (abs(A[i - 1] - A[i]) <= k) OK[i] += 1;
      if (abs(A[i - 1] - B[i]) <= k) OK[i] += 2;
    } else if (OK[i - 1] == 2) {
      if (abs(B[i - 1] - A[i]) <= k) OK[i] += 1;
      if (abs(B[i - 1] - B[i]) <= k) OK[i] += 2;
    } else {
      if (abs(A[i - 1] - A[i]) <= k || abs(B[i - 1] - A[i]) <= k) {
        OK[i] += 1;
      }
      if (abs(A[i - 1] - B[i]) <= k || abs(B[i - 1] - B[i]) <= k) {
        OK[i] += 2;
      }
    }
  }

  /* output */
  cout << (OK[n - 1] != 0 ? "Yes" : "No") << endl;

  return 0;
}