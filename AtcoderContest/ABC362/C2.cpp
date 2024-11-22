
#include <bits/stdc++.h>
using namespace std;

int main() {
  // 入力
  int N;
  cin >> N;
  vector<long> L(N), R(N);
  for (int i = 0; i < N; i++) cin >> L[i] >> R[i];

  // 答えを最小値で初期化
  vector<long> ans = L;
  long sum = reduce(begin(ans), end(ans));

  // 既に0以上ならこれより小さくできないのでNo
  if (sum > 0) {
    cout << "No" << endl;
    return 0;
  }

  // できるだけ増やして0に近づける
  for (int i = 0; i < N; i++) {
    long v = min(R[i] - L[i], -sum);
    sum += v;
    ans[i] += v;
  }

  // 出力
  if (sum) {
    cout << "No" << endl;
  } else {
    cout << "Yes" << endl;
    for (int i = 0; i < N; i++) cout << ans[i] << " ";
    cout << endl;
  }
}
