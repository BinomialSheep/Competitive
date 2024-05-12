#include <iostream>
#include <vector>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;

vector<int> vec;

void makeBoard(int x) {
  if (x <= 4)
    vec.push_back(x);
  else {
    makeBoard(x / 2);
    makeBoard((x + 1) / 2);
  }
}

int main() {
  int x;
  cin >> x;

  makeBoard(x);

  int ans = 1;
  for (int i = 0; i < vec.size(); i++) {
    ans = ans * vec[i];
  }
  cout << ans << endl;

  return 0;
}