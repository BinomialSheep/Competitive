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
  vector<int> T(N);
  rep(i, N) cin >> T[i];

  /* solve */
  int id0 = -1;
  string ans = "1";
  rep(i, T[0]) ans.push_back('0');
  rep(i, N - 1) {
    // cout << ans << " " << id0 << endl;
    if (T[i] == T[i + 1]) {
      if (id0 != -1) {
        ans[id0] = '1';
        id0 = -1;
        rep(j, id0) {
          if (ans[j] == '0') id0 = j;
        }
      } else {
        // なければ左に1を足す
        ans.push_back('0');
        ans[(int)ans.size() - 1 - T[i]] = '1';
      }
    } else if (T[i] > T[i + 1]) {
      // 0を1に変えるだけ
      ans[(int)ans.size() - 1 - T[i + 1]] = '1';
      if (ans[(int)ans.size() - 2 - T[i + 1]] == '0') {
        id0 = (int)ans.size() - 2 - T[i + 1];
      }
    } else {
      // 100を1000に変えるみたいなケース
      if ((int)ans.size() <= T[i + 1]) {
        ans = "1";
        rep(j, T[i + 1]) ans.push_back('0');
        id0 = -1;
      } else {
        // 桁を変えずにどうにかできるか調べる
        if (id0 != -1) {
          ans[id0] = '1';
          id0 = -1;
          rep(j, id0) {
            if (ans[j] == '0') id0 = j;
          }

          string s = "";
          for (int j = 0; j <= id0; j++) {
            s.push_back(ans[j]);
          }
          for (int j = 0; j < T[i + 1]; j++) {
            s.push_back('0');
          }
          string s2 = "1";
          int keta = ans.size() + 1;
          rep(j, keta - 1) s2.push_back('0');
          s2[s2.size() - T[i + 1] - 1] = '1';
          if (s > s2) {
            ans = s2;
            if (s2[s2.size() - T[i + 1] - 2] == '0') {
              id0 = s2[s2.size() - T[i + 1] - 2];
            } else {
              id0 = -1;
            }
          } else {
            ans = s;
          }
        } else {
          // 桁を変える必要があるケース
          rep(j, T[i + 1] - T[i]) { ans.push_back('0'); }
        }
      }
    }
  }

  // cout << ans << endl;

  /* output */
  ll output = 0;
  rep(i, (int)ans.size()) {
    if (ans[i] == '1') {
      output += (ll)pow((ll)2, (ll)ans.size() - 1 - i);
    }
  }
  cout << output << endl;

  return 0;
}