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
  map<int, int> a;
  vector<int> b(m);
  rep(i, n) {
    int temp;
    cin >> temp;
    a[temp]++;
  }
  rep(i, m) cin >> b[i];

  // for (auto i = a.begin(); i != a.end(); i++) {
  //   cout << i->first << " " << i->second << endl;
  // }

  bool isYes = true;
  rep(i, m) {
    // 同じ長さが残り0ならfalse
    if (a[b[i]] == 0) isYes = false;
    // 同じ長さが残り1以上ならデクリメントして続行
    a[b[i]]--;
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}