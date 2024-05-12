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
    bool isNo = false;
    // 同じ文字の中に離れて単語が存在したら終わり
    rep(j, N) {
      if (S[j].size() <= 2) continue;
      set<char> se;
      se.insert(S[j][0]);
      rep(k, S[j].size() - 1) {
        if (se.count(S[j][k + 1]) && S[j][k + 1] != S[j][k]) {
          isNo = true;
          break;
        } else {
          se.insert(S[j][k + 1]);
        }
      }
    }
    if (isNo) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    // 一種類のみで構成された文字を探す
    map<char, int> onlyCharMap;
    // 1文字のindex
    set<int> onlyCharIndex;
    // 始まりと終わりの文字のindex
    map<char, int> startIdxMap;
    map<char, int> endIdxMap;
    rep(j, N) {
      bool flag = true;
      if (S[j].size() != 1) {
        rep(k, S[j].size() - 1) {
          if (S[j][k] != S[j][k + 1]) flag = false;
        }
      }
      if (flag) {
        onlyCharMap[S[j][0]] += (int)S[j].size();
        onlyCharIndex.insert(j);
      } else {
        if (startIdxMap.count(S[j][0])) {
          isNo = true;
        } else {
          startIdxMap[S[j][0]] = j;
        }
        if (endIdxMap.count(S[j].back())) {
          isNo = true;
        } else {
          endIdxMap[S[j].back()] = j;
        }
      }
    }
    if (isNo) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    // 一種類のみで構成された文字が、何かの文字の真ん中にだけ存在したら終わり
    for (auto p : onlyCharMap) {
      char c = p.first;
      rep(j, N) {
        if (S[j].size() <= 2 || S[j][0] == c || S[j][S[j].size() - 1] == c) {
          continue;
        }
        for (int k = 1; k < (int)S[j].size() - 1; k++) {
          if (S[j][k] == c) isNo = true;
        }
      }
    }
    if (isNo) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }

    //
    if (startIdxMap.size() == 0) {
      // 全部がonly文字から構成されている場合
      for (auto p : onlyCharMap) {
        rep(j, p.second) cout << p.first;
      }
      cout << endl;
      continue;
    }

    // dequeを構成していく

    deque<string> q;
    vector<bool> used(N, false);
    while (true) {
      if (q.empty()) {
        if (onlyCharIndex.count(0)) {
          string s = "";
          int num = onlyCharMap[S[0][0]];
          rep(j, num) s.push_back(S[0][0]);
          q.push_back(s);
          onlyCharMap.erase(S[0][0]);
        } else {
          q.push_back(S[0]);
        }
        used[0] = true;
      }
      string f = q.front();
      if (onlyCharMap.count(f[0])) {
        string s = "";
        int num = onlyCharMap[f[0]];
        rep(j, num) s.push_back(f[0]);
        q.push_front(s);
        onlyCharMap.erase(f[0]);
        continue;
      } else if (endIdxMap.count(f[0])) {
        q.push_front(S[endIdxMap[f[0]]]);
        used[endIdxMap[f[0]]] = true;
        continue;
      }
      string b = q.back();
      if (onlyCharMap.count(b[b.size() - 1])) {
        string s = "";
        int num = onlyCharMap[b[b.size() - 1]];
        rep(j, num) s.push_back(b[b.size() - 1]);
        q.push_back(s);
        onlyCharMap.erase(b[b.size() - 1]);
        continue;
      } else if (startIdxMap.count(b.back())) {
        q.push_back(S[startIdxMap[b.back()]]);
        used[startIdxMap[b.back()]] = true;
        continue;
      }
      break;
    }
    string ans = "";
    while (!q.empty()) {
      ans += q.front();
      q.pop_front();
    }
    rep(j, N) {
      if(used[i] || onlyCharIndex[i]) continue;
      
    }
    for (auto p : onlyCharMap) {
      rep(j, p.second) ans.push_back(p.first);
    }
    if (ans.size() >= 3) {
      set<char> se;
      se.insert(ans[0]);
      rep(j, ans.size() - 1) {
        if (se.count(ans[j + 1]) && ans[j + 1] != ans[j]) {
          isNo = true;
          break;
        } else {
          se.insert(ans[j + 1]);
        }
      }
    }
    if (isNo) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    } else {
      cout << ans << endl;
    }
  }

  /* output */

  return 0;
}