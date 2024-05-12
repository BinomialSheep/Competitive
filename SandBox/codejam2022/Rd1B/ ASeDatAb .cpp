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
    // 最初は適当
    int Ni = rand() % 7 + 1;
    rep(j, 300) {
      // 出力する
      string st = "00000000";
      string st2 = "11111111";
      if (Ni == 1) {
        int r = rand() % 8;
        st[r] = '1';
        cout << st << endl;
      } else if (Ni == 2) {
        int r1 = rand() % 8;
        int r2 = rand() % 8;
        while (r1 == r2) {
          r2 = rand() % 8;
        }
        st[r1] = '1';
        st[r2] = '1';
        cout << st << endl;
      } else if (Ni == 3) {
        int r1 = rand() % 8;
        int r2 = rand() % 8;
        while (r1 == r2) {
          r2 = rand() % 8;
        }
        int r3 = rand() % 8;
        while (r1 == r3 || r2 == r3) {
          r3 = rand() % 8;
        }
        st[r1] = '1';
        st[r2] = '1';
        st[r3] = '1';
        cout << st << endl;
      } else if (Ni == 4) {
        int r1 = rand() % 8;
        int r2 = rand() % 8;
        while (r1 == r2) {
          r2 = rand() % 8;
        }
        int r3 = rand() % 8;
        while (r1 == r3 || r2 == r3) {
          r3 = rand() % 8;
        }
        int r4 = rand() % 8;
        while (r1 == r4 || r2 == r4 || r3 == r4) {
          r4 = rand() % 8;
        }
        st[r1] = '1';
        st[r2] = '1';
        st[r3] = '1';
        st[r4] = '1';
        cout << st << endl;
      } else if (Ni == 5) {
        int r1 = rand() % 8;
        int r2 = rand() % 8;
        while (r1 == r2) {
          r2 = rand() % 8;
        }
        int r3 = rand() % 8;
        while (r1 == r3 || r2 == r3) {
          r3 = rand() % 8;
        }
        st2[r1] = '0';
        st2[r2] = '0';
        st2[r3] = '0';
        cout << st2 << endl;
      } else if (Ni == 6) {
        int r1 = rand() % 8;
        int r2 = rand() % 8;
        while (r1 == r2) {
          r2 = rand() % 8;
        }
        st2[r1] = '0';
        st2[r2] = '0';
        cout << st2 << endl;
      } else if (Ni == 7) {
        int r1 = rand() % 8;
        st2[r1] = '0';
        cout << st2 << endl;
      } else if (Ni == 8) {
        cout << st2 << endl;
      }

      cin >> Ni;
      if (Ni == 0) break;
      if (Ni == -1) {
        return 0;
      }
    }
  }

  /* output */

  return 0;
}