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
  ll T;
  cin >> T;

  /* solve */
  rep(i, T) {
    int N;
    cin >> N;
    vector<string> S(N);
    rep(j, N) cin >> S[j];

    cout << "Case #" << i + 1 << ": ";
    //
    bool isImp = false;
    rep(j, 26) {
      char c = (char)('A' + j);
      vector<string> newS;
      vector<string> startC;
      vector<string> endC;
      vector<string> startEndC;
      // 例えば先頭がa、最後尾がa、両方a、両方a以外で分類
      rep(k, S.size()) {
        if (S[k][0] == c && S[k].back() == c)
          startEndC.push_back(S[k]);
        else if (S[k][0] == c)
          startC.push_back(S[k]);
        else if (S[k].back() == c)
          endC.push_back(S[k]);
        else
          newS.push_back(S[k]);
      }
      // 先頭のみaとか最後尾のみaは高々1つのはず
      if (startC.size() > 1 || endC.size() > 1) {
        isImp = true;
        break;
      }
      // aが連続する部分をくっ付ける（strで矛盾がIMP判定になることもあるが判定しない
      string str = "";
      if (endC.size() == 1) str = endC[0];
      for (auto addS : startEndC) str += addS;
      if (startC.size() == 1) str += startC[0];
      newS.push_back(str);
      //
      S.resize(newS.size());
      rep(l, newS.size()) S[l] = newS[l];
    }
    // 全部くっ付ける
    string ans = "";
    rep(j, S.size()) ans += S[j];
    // 判定する
    vector<bool> used(26, false);
    rep(j, ans.size()) {
      if (used[ans[j] - 'A'] && ans[j] != ans[j - 1]) {
        isImp = true;
        break;
      } else {
        used[ans[j] - 'A'] = true;
      }
    }
    cout << (isImp ? "IMPOSSIBLE" : ans) << endl;
  }

  /* output */

  return 0;
}