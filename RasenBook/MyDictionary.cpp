#include <bits/stdc++.h>

using namespace std;



class MyDictionary {
  int M =  1046527;
  int NIL =  (-1);
  int L = 14;
  char H[1046527][14];


  // ダブルハッシュを用いたオープンアドレス法
  int calcH(int key, int i){
    return (h1(key) + i * h2(key)) % M;
  }
  int h1(int key){
    return key % M;
  }
  int h2(int key){
    return 1 + (key % (M - 1));
  }

  // 文字列から数値へ変換し、keyを生成
  long long getKey(char str[]) {
    long long sum = 0;
    long long p = 1;
    for(long long i = 0; i < strlen(str); i++){
      sum += p * getChar(str[i]);
      p *= 5; 
    }
    return sum;
  }

  // 文字から数値に変換
  int getChar(char ch){
    if(ch=='A') return 1;
    else if(ch == 'C') return 2;
    else if(ch == 'G') return 3;
    else if(ch == 'T') return 4;
    else return 0;
  }

  public:
    MyDictionary(){
      for(long long i = 0; i < M; i ++ ) H[i][0] = '\0';
    }    
    void insert(char str[]) {
      long long key = key = getKey(str); // 文字列を数値に変換
      for(long long i = 0; ; i++ ){
        long long h = calcH(key, i); // 挿入する位置
        if (strcmp(H[h], str) == 0 ) return; 
        else if (strlen(H[h]) == 0) {
          strcpy(H[h], str);
          return;
        }
      }
      return;
    }

    bool find(char str[]){
      long long key, i, h;
      key = getKey(str); // 文字列を数値に変換
      for(i = 0; ; i++){
        h = (h1(key) + i * h2(key)) % M;
        if (strcmp(H[h], str) == 0 ) return true;
        else if (strlen(H[h]) == 0) return false;
      }
      return false;
    }
};




int main() {



  int n;
  scanf("%d", &n);

  char com[10];
  char str[20];


  MyDictionary *dict = new MyDictionary;


  for(int i = 0; i < n; i++){
    scanf("%s %s", com, str);

    if(com[0] == 'i'){
      (*dict).insert(str);
    } else {
      if((*dict).find(str)){
        printf("yes\n");
      } else {
        printf("no\n");
      }

    }
  }



  return 0;
}