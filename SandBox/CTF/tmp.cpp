#include <bits/stdc++.h>
using namespace std;

int main() {
  int j = -1;
  vector<vector<int>> vec(3);

  auto f = [](string s) {
    string tmp = "0123456789abcdef";
    int ret = 0;
    for (int i = 0; i < 16; i++)
      if (s[1] == tmp[i]) ret += i;
    for (int i = 0; i < 16; i++)
      if (s[0] == tmp[i]) ret += 16 * i;
    return ret;
  };

  for (int i = 0; i < 199; i++) {
    string S;
    cin >> S;
    if (S.size() > 2)
      j++;
    else {
      vec[j].push_back(f(S));
    }
  }

  for (auto ve : vec) {
    for (auto n : ve) cout << n << ",";
    cout << endl;
  }

  return 0;
}