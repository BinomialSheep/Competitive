#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int factrial(int n, int ret) {
  if (n == 1 || n == 0)
    return ret;
  else
    return factrial(n - 1, n * ret);
}

int countOrder(vector<int> vec, int size) {
  int ret = 1;

  rep(i, size) {
    // cout << i << " ";
    ret *= vec[i] * factrial(size - i - 1, 1);
  }

  return ret;
}

vector<vector<int> > allOrder;

void makeAllOrder(vector<int> nowOrder, vector<int> useable) {
  if (useable.size() == 1) {
    nowOrder.push_back(useable[0]);
    allOrder.push_back(nowOrder);
    return;
  }

  for (int i = 0; i < useable.size(); i++) {
    int temp = useable[i];
    nowOrder.push_back(temp);
    useable.erase(useable.begin() + i);
    makeAllOrder(nowOrder, useable);
    useable.insert(useable.begin() + i, temp);
    nowOrder.pop_back();
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> p(n);
  vector<int> q(n);
  rep(i, n) cin >> p[i];
  rep(i, n) cin >> q[i];

  /*
    int pCount = countOrder(p, n);
    int qCount = countOrder(q, n);
    cout << pCount << " " << qCount << endl;
    cout << abs(pCount - qCount) << endl;
    */

  vector<int> nowOrder;
  vector<int> useable;
  for (int i = 1; i <= n; i++) useable.push_back(i);

  makeAllOrder(nowOrder, useable);

  int pCount;
  int qCount;

  for (int i = 0; i < allOrder.size(); i++) {
    if (equal(allOrder[i].begin(), allOrder[i].end(), p.begin())) {
      pCount = i + 1;
    }
    if (equal(allOrder[i].begin(), allOrder[i].end(), q.begin())) {
      qCount = i + 1;
    }
  }
  cout << abs(pCount - qCount) << endl;

  return 0;
}