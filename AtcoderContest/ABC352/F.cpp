#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vector<int> A(M), B(M), C(M);
  rep(i, M) {
    cin >> A[i] >> B[i] >> C[i];
    --A[i], --B[i];
  }
  /* solve */
  vector<set<int>> possible(N);

  vector<int> perm(N);
  iota(perm.begin(), perm.end(), 0);
  do {
    // 与えられた条件に矛盾するか判定する
    bool ng = false;
    rep(i, M) {
      // debug(i, A[i], B[i]);
      if (perm[A[i]] - perm[B[i]] != C[i]) {
        ng = true;
        // break;
      }
    }
    if (!ng) {
      rep(i, N) { possible[perm[i]].insert(i); }
    }
    // 矛盾しない場合、あり得る順位とする
  } while (next_permutation(perm.begin(), perm.end()));

  /* output */
  vector<int> ans(N, -1);
  rep(i, N) {
    if (possible[i].size() == 1) {
      // 順位確定
      ans[*(possible[i].begin())] = i + 1;
    }
  }
  rep(i, N) cout << ans[i] << endl;
  return 0;
}