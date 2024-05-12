#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

void solve(int testCase) {
  /* input */
  int R, C;
  cin >> R >> C;
  vector<string> S(R);
  rep(i, R) cin >> S[i];

  /* solve */
  string ans = "Possible";
  if (R != 1 && C != 1) {
    rep(i, R) rep(j, C) S[i][j] = '^';
  } else {
    rep(i, R) rep(j, C) {
      if (S[i][j] == '^') ans = "Impossible";
    }
  }

  /* output */
  printf("Case #%d: %s\n", testCase, ans.c_str());
  if (ans == "Possible") {
    rep(i, R) cout << S[i] << "\n";
  }
}

int main() {
  int T;
  cin >> T;
  rep(ti, T) solve(ti + 1);
  return 0;
}