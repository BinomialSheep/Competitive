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
  int idx0 = -1;
  string ans = "1";
  rep(i, T[0]) ans.push_back('0');
  rep(i, N - 1) {
    // cout << ans << endl;
    if (T[i] == T[i + 1]) {
      bool flag = false;
      for (int j = (int)ans.size() - 1 - T[i]; j >= 0; j--) {
        // cout << "j:" << j << endl;
        //  0があったらそこを1に変える
        if (ans[j] == '0') {
          ans[j] = '1';
          flag = true;
          break;
        }
      }
      // なければ左に1を足す
      if (!flag) {
        ans.push_back('0');
        ans[(int)ans.size() - 1 - T[i]] = '1';
      }
    } else if (T[i] > T[i + 1]) {
      // 0を1に変えるだけ
      ans[(int)ans.size() - 1 - T[i + 1]] = '1';
    } else {
      // 100を1000に変えるみたいなケース
      if ((int)ans.size() <= T[i + 1]) {
        ans = "1";
        rep(j, T[i + 1]) ans.push_back('0');
      } else {
        int flag = -1;
        // 桁を変えずにどうにかできるか調べる
        for (int j = (int)ans.size() - 1 - T[i]; j >= 0; j--) {
          if (ans[j] == '0') {
            ans[j] = '1';
            flag = j;
            // cout << "true:" << j;
            break;
          }
        }
        if (flag != -1) {
          string s = "";
          for (int j = 0; j <= flag; j++) {
            s.push_back(ans[j]);
          }
          for (int j = 0; j < T[i + 1]; j++) {
            s.push_back('0');
          }
          string s2 = "1";
          int keta = ans.size() + 1;
          rep(j, keta - 1) s2.push_back('0');
          s2[s2.size() - T[i + 1] - 1] = '1';
          ans = min(s, s2);
        }
        // 桁を変える必要があるケース
        if (flag == -1) {
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