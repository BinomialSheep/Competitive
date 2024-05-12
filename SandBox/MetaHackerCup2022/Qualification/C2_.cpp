#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
void solve(int testCase) {
  /* input */
  int N;
  cin >> N;
  string C;
  cin >> C;

  vector<string> ans;

  /* solve */
  string init = "..........";
  if (C[0] == '.') init[0] = '-';

  int bit = -1;
  while ((int)ans.size() + 1 < N) {
    bit++;
    string s = init;
    rep(i, 9) {
      if (bit & (1 << i)) s[i + 1] = '-';
    }
    ans.push_back(s);
  }

  /* output */
  printf("Case #%d:\n", testCase);
  rep(i, (int)ans.size()) cout << ans[i] << "\n";
}

int main() {
  int T;
  cin >> T;
  rep(ti, T) solve(ti + 1);
  return 0;
}