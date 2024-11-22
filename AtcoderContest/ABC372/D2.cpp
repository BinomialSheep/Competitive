#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void solve() {
  int N;
  cin >> N;
  vector<int> H(N), ans(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }

  stack<int> s;
  for (int i = N - 1; i >= 0; i--) {
    int count = 0;
    while (!s.empty() && H[i] < H[s.top()]) {
      count += ans[s.top()];
      s.pop();
    }
    ans[i] = count + (s.empty() ? 0 : 1);
    s.push(i);
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}

int main() {
  solve();
  return 0;
}
