#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m);
  rep(i, n) cin >> a[i];
  rep(i, m) cin >> b[i];

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  stack<int> aStack;
  rep(i, n) aStack.push(a[i]);

  bool isYes = true;

  rep(i, m) {
    while (true) {
      int temp = aStack.pop();
      aStack.top();

      if (temp == b[i]) {
        break;
      }
      if (temp > b[i]) {
        isYes = false;
        break;
      }
    }
    if (!isYes) {
      break;
    }
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}