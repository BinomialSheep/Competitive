#include <bits/stdc++.h>
using namespace std;
int main() {
  vector<pair<int, int>> q;
  auto heappop = [&]() {
    // 取り出し
    auto ret = q[0];
    swap(q[0], q[q.size() - 1]);
    q.pop_back();
    // 入れ替え
    int idx = 0;
    while (true) {
      int left = (idx + 1) * 2 - 1, right = (idx + 1) * 2;
      if (left >= (int)q.size()) break;
      if (right == (int)q.size()) right--;  // サボり
      // 自分が1番小さくなったら終わり
      if (q[idx].first < q[left].first && q[idx].first < q[right].first) break;
      // 左右で同じなら右へ
      if (q[right].first <= q[left].first)
        swap(q[idx], q[right]), idx = right;
      else
        swap(q[idx], q[left]), idx = left;
    }
    return ret;
  };
  for (int i = 0; i < 15; i++) q.emplace_back(0, i);
  while (q.size()) cout << heappop().second << " ";
  cout << endl;
  for (int i = 0; i < 16; i++) q.emplace_back(0, i);
  while (q.size()) cout << heappop().second << " ";
}