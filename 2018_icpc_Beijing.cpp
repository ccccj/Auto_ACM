/*
#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
const int maxn = 200010;
string arr[maxn];
bool isend[maxn];
int cnt = 1;

bool HasChar(string s) {
  for (int i = 0; s[i]; ++i) {
    if (s[i] < '0' || s[i] > 9) {
      return 1;
    }
  }
  return 0;
}

int main() {
  freopen("/Users/Amon/Desktop/a.txt", "r", stdin);
  string ss;
  while (getline(cin, ss)) {
    istringstream line;
    line.str(ss);
    isend[cnt - 1] = 1;
    while (line >> arr[cnt]) {
      ++cnt;
    }
  }
  isend[cnt - 1] = 1;

  vector<int> v;
  int ans = 0, k = 0;

  for (int i = 1; i < cnt; ++i) {
    int len = arr[i].size();
    if (isend[i] == 1) {
      // 是结尾
      if (HasChar(arr[i])) {
        // 不合法
        v.push_back(ans);
        ans = 0;
        continue;
      }

//////////////////////////////////////////

      if (arr[i][0] == '0' && len == 1) {
        if (i == len - 1) {
          // 是最后一个字符串
          // 直接输出
          if (k == 0) {
            cout << arr[i];
            ++k;
          } else {
            cout << ' ' << arr[i];
          }
          ++ans;
          v.push_back(ans);
          ans = 0;
          continue;
        }

        if (HasChar(arr[i+1])) {
          // 下一个有字符
          ++ans;
          if (k == 0) {
            cout << arr[i];
            ++k;
          } else {
            cout << ' ' << arr[i];
          }

        } else {
          // 下一个无字符
          ++i;
        }
        v.push_back(ans);
        ans = 0;

      } else if (arr[i][0] == 0 && len > 1) {

        // 开头是0，长度大于1，不合法
        v.push_back(ans);
        ans = 0;
        if (!HasChar(arr[i+1])) {
          // 下一个无字符
          ++i;
        }

      } else {



        // 是开头没有0合法数字
        if (i == len - 1) {
          // 是最后一个字符串
          // 直接输出
          if (k == 0) {
            cout << arr[i];
            ++k;
          } else {
            cout << ' ' << arr[i];
          }
          ++ans;
          v.push_back(ans);
          ans = 0;
          continue;
        }
        if (!HasChar(arr[i+1])) {
          // 下一个也没有字符
          if (k == 0) {
            cout << arr[i] << arr[i + 1];
            ++k;
          } else {
            cout << ' ' << arr[i] << arr[i + 1];
          }
          ++i;
        } else {

          // 下一行第一个串有字符
          if (k == 0) {
            cout << arr[i];
            ++k;
          } else {
            cout << ' ' << arr[i];
          }
        }

        ++ans;
        v.push_back(ans);
        ans = 0;
      }


//////////////////////////////////////////////////////////

    } else {

      // 在中间
      if (HasChar(arr[i])) {
        // 有字符，不合法
        continue;
      }
      // 没有字符
      if ((len == 1 && arr[i][0] == '0') || arr[i][0] > '0') {
        // 合法
        ++ans;
        if (k == 0) {
          cout << arr[i];
          ++k;
        } else {
          cout << ' ' << arr[i];
        }
      }
    }
  }


  cout << endl;
  int len = v.size();
  for (int i = 0; i < len; ++i) {
    printf("%d\n", v[i]);
  }
  return 0;
}



// I
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;
char s[maxn];
int ans[maxn];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    memset(ans, 0, sizeof ans);
    scanf("%s", s);
    int len = strlen(s), q = 1, f = 1;
    if (!s[1]) {
      --s[0];
      printf("%s\n", s);
      continue;
    }
    if (s[0] == '1' && s[1] == '0' && s[2] == '\0') {
      printf("9\n");
      continue;
    }
    if (s[0] == '1' && s[1] == '0') {
      printf("9");
      for (int i = 2; i < len; ++i) printf("%c", s[i]);
      for (int i = len - 2; i >= 2; --i) printf("%c", s[i]);
      printf("9");
    } else if (s[0] == '1') {
      for (int i = 1; i < len; ++i) printf("%c", s[i]);
      for (int i = len - 1; i > 0; --i) printf("%c", s[i]);
    } else {
      --s[0];
      for (int i = 0; i < len; ++i) printf("%c", s[i]);
      for (int i = len - 2; i >= 0; --i) printf("%c", s[i]);
    }
    printf("\n");
  }
  return 0;
}

// I 打标找规律
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5;
LL arr[maxn];
int num = 0;

bool judge(LL a) {
  int tmp[30], cnt = 0;
  while (a) {
    tmp[cnt++] = a % 10;
    a /= 10;
  }
  int l = 0, r = cnt - 1;
  while (l <= r) {
    if (tmp[l] != tmp[r]) return 0;
    ++l, -- r;
  }
  return 1;
}

void init() {
  for (LL i = 0; i < 1ll << 10; ++i) {
    if (judge(i)) {
      arr[num++] = i;
      printf("%d %lld\n", num, i);
    }
  }
}

int main() {
  init();

  return 0;
}

// D
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn = 55;
LL fei[maxn] = {1, 1};

void init() {
  for (int i = 2; i < 50; ++i) {
    fei[i] = fei[i - 1] + fei[i - 2];
  }
}

int main() {
  init();
  LL M;
  while (~scanf("%lld", &M)) {
    if (M == 0) {
      printf("2\n1 1\n2 1\n");
      continue;
    }
    vector<LL> v;
    for (int i = 49; i >= 0; --i) {
      if (M >= fei[i]) {
        M -= fei[i];
        v.push_back(i);
        //printf("%lld\n", fei[i]);
      }
    }
    int len = v.size(), now = 0, sta = 0;
    printf("%d\n", len + 1);
    while (now < len) {
      printf("%d %lld\n", sta + 1, 200 - v[now++]);
      sta += 2;
    }
    printf("%d %d\n", sta, sta);
  }
  return 0;
}


// A
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100;
char str[maxn][35], s1[35], s2[35];
int num, cnt, head[maxn], vis[maxn];

struct Edge {
  int to, next;
} edge[maxn];

void insert(int x, int y) {
  edge[cnt].to = y, edge[cnt].next = head[x];
  head[x] = cnt++;
}

bool dfs(int now) {
  if (vis[now]) return 1;
  for (int i = head[now]; i != -1; i = edge[i].next) {
    int to = edge[i].to;
    if (dfs(to)) return 1;
  }
  return 0;
}

int main() {
  int n, a, b, f;
  while (~scanf("%d", &n)) {
    memset(head, -1, sizeof head);
    num = cnt = f = 0;

    for (int i = 0; i < n; ++i) {
      scanf("%s%s", s1, s2);
      //printf("====\n");
      if (f) continue;
      memset(vis, 0, sizeof vis);

      a = b = -1;
      for (int j = 0; j < num && (a == -1 || b == -1); ++j) {
        if (a == -1 && strcmp(str[j], s1) == 0) a = j;
        if (b == -1 && strcmp(str[j], s2) == 0) b = j;
      }
      if (a != -1 && b != -1) {
        vis[a] = 1;
        if (dfs(b)) {
          printf("%s %s\n", s1, s2);
          f = 1;
        } else {
          insert(a, b);
        }
      } else {
        if (a == -1) {a = num; strcpy(str[num++], s1);}
        if (b == -1) {b = num; strcpy(str[num++], s2);}

        insert(a, b);
      }
    }
    if (f == 0) printf("0\n");
  }
  return 0;
}
*/
