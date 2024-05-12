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
  int q;
  cin >> q;
  int num, k;
  ll x;

  multiset<ll> A;

  rep(i, q) {
    // クエリ
    cin >> num >> x;
    if (num != 1) {
      cin >> k;
      k--;
    }
    //
    if (num == 1) {
      A.insert(x);
    }
    if (num == 2) {
      // x+1の最初のitr
      auto itr = A.lower_bound(x + 1);
      int flag = 0;
      if (itr == A.begin()) {
        // x+1以上の要素しかないならおしまい
        cout << -1 << endl;
      } else {
        // その1つ前がx以下の最後のイテレータ
        itr--;
        // k回だけデクリメントする
        for (int i = 1; i <= k; i++) {
          if (itr == A.end() || itr == A.begin()) {
            flag = 1;
            break;
          } else {
            itr--;
          }
        }
        if (itr == A.end() || flag == 1)
          cout << -1 << endl;
        else
          cout << *itr << endl;
      }
    }
    if (num == 3) {
      // x以上の最初のitr
      auto itr = A.lower_bound(x);
      for (int i = 1; i <= k; i++) {
        if (itr == A.end())
          break;
        else
          itr++;
      }
      if (itr == A.end())
        cout << -1 << endl;
      else
        cout << *itr << endl;
    }
  }

  return 0;
}