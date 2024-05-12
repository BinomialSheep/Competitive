#include <bits/stdc++.h>
using namespace std;

int main() {
  for (int i = 0; i < 10; i++) {
    string S;
    int V;
    cin >> S >> V;
    printf("if(S==\"%s\")cout<<%d<<endl;\n", S.c_str(), V);
  }

  return 0;
}