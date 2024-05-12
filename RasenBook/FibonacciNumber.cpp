#include <bits/stdc++.h>

using namespace std;

typedef long long ll;




int fib(int n) {
  if (n == 0 || n == 1) return 1;
  return fib(n - 1) + fib(n - 2);
}


pair<int, int> fib2(int n) {
  if (n == 1){
    pair<int, int> p(1, 1);
    return p;
  }

  pair<int, int> lastPair = fib2(n - 1);

  int thisSecond = lastPair.first + lastPair.second;
  pair<int, int> thisPair(lastPair.second, thisSecond);
  return thisPair;
}


int main() {
  int n;
  cin >> n;

  cout << fib2(n).second << endl;

  return 0;
}