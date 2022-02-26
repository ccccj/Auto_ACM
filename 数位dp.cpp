#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 20;

int main() {

  printf("%d\n", 321 - 123);

  return 0;
}



/*
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 20;
int arr[maxn], dp[maxn];

LL dfs(LL x, int now, bool up) {
  if (now == 0) return 1;
  if (!up && dp[now] != -1) return dp[now];
  int maxx = up ? arr[now] : 9;
  LL cnt = 0;

  for (int i = 0; i <= maxx; ++i) {
    if (i == 0) {
      cnt += dfs(x * 10 + i, now - 1, up && i == maxx);
      // printf("cnt : %lld\n", cnt);

    } else if (x % i == 0) {
      cnt += dfs(x * 10 + i, now - 1, up && i == maxx);
      //printf("i %d cnt : %lld\n", i, cnt);
    }
  }
  return up ? cnt : (dp[now] = cnt);
}

LL slove(LL x) {
  int cnt = 0;
  memset(dp, -1, sizeof dp);

  while (x) {
    arr[++cnt] = x % 10;
    x /= 10;
  }
  return dfs(0, cnt, 1);
}

int main() {
  for (int i = 0; i <= 20; ++i) {
    printf("%d %lld\n", i, slove(i));

  }

  int t;
  scanf("%d", &t);
  while (t--) {
    LL a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld %lld\n", slove(b), slove(a - 1));

    printf("%lld\n", slove(b) - slove(a - 1));
  }
  return 0;
}

// HDU 3555
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 70;
int arr[maxn];
LL dp[maxn][2];

LL dfs(int now, bool if4, bool up) {
  if (now == 0) return 1;
  if (!up && dp[now][if4]) return dp[now][if4];
  int maxx = up ? arr[now] : 9;
  LL cnt = 0;
  for (int i = 0; i <= maxx; ++i) {
    if (if4 && i == 9) continue;
    cnt += dfs(now - 1, i == 4, up && i == maxx);
  }
  return up ? cnt : (dp[now][if4] = cnt);
}

LL slove(LL x) {
  int cnt = 0;
  memset(dp, 0, sizeof dp);

  while (x) {
    arr[++cnt] = x % 10;
    x /= 10;
  }
  return dfs(cnt, 0, 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    LL x;
    scanf("%lld", &x);
    printf("%lld\n", x + 1 - slove(x));
  }
  return 0;
}


// HDU 2089
#include <cstdio>
#include <cstring>
using namespace std;
int arr[20], dp[20][2];

int dfs(int now, bool is6, bool up) {
  if (now == 0) return 1;
  if (!up && dp[now][is6]) return dp[now][is6];
  int maxx = up ? arr[now] : 9, cnt = 0;
  for (int i = 0; i <= maxx; ++i) {
    if ((is6 && i == 2) || i == 4) continue;
    cnt += dfs(now - 1, i == 6, up && i == maxx);
  }
  return up ? cnt : (dp[now][is6] = cnt);
}

int slove(int a) {
  memset(dp, 0, sizeof dp);
  int cnt = 0;
  while (a) {
    arr[++cnt] = a % 10;
    a /= 10;
  }
  return dfs(cnt, 0, 1);
}

int main() {
  int a, b;
  while (~scanf("%d%d", &a, &b) && (a + b)) {
      printf("%d\n", slove(b) - slove(a - 1));
  }
  return 0;
}
*/
