#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
double arr[maxn];

int main() {
  int t, n, ca = 1;
  scanf("%d", &t);
  double a, b;
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%lf:%lf", &a, &b);
      arr[i] = 1 / (b / a + 1);
    }
    sort(arr, arr + n);
    double sum = 0;
    int i;
    for (i = 0; i < n; ++i) {
      sum += arr[i];
      if (sum > 1 - 1e-8) {
        //printf("%d\n", i);

        break;
      }
    }
    printf("Case #%d: %d\n", ca++, i);

  }
  return 0;
}
/*
// Gym - 101194D
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e5 + 10;
typedef long long LL;
LL arr[maxn], tmp[maxn];
int t, n, k, ca;

bool judge(int x) {
  arr[n] = arr[n + 1] = arr[n + 2] = 0;
  int now = 0;
  for (int i = 0; i < x; ++i) {
    tmp[i] = arr[now++];
  }
  for (int i = 1; i < k; ++i) {
    for (int j = 0; j < x; ++j) {
      while (arr[now] / tmp[j] < 2 && now < n) {
        ++now;
      }
      if (arr[now] / tmp[j] >= 2) {
        tmp[j] = arr[now++];
      } else {
        return 0;
      }
    }
  }
  return 1;
}

int main(int argc, char const *argv[]) {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &arr[i]);
    }
    sort(arr, arr + n);
    int l = 0, r = n / k + 1;
    while (l < r) {
      int mid = (l + r) / 2;
      if (judge(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    printf("Case #%d: %d\n", ++ca, l - 1);
  }
  return 0;
}


// Gym - 101194L
#include <cstdio>
using namespace std;
int cnt;
struct node {
  int sum1, sum2, sum3, sum4;
} ans[1000];

void dfs(int now, int sum1, int sum2, int sum3, int sum4) {
  if (now == 7) {
    ans[cnt].sum1 = sum1;
    ans[cnt].sum2 = sum2;
    ans[cnt].sum3 = sum3;
    ans[cnt].sum4 = sum4;
    // if (ans[cnt].sum1 == 9 && ans[cnt].sum2 == 6 && ans[cnt].sum3 == 3 && ans[cnt].sum4 == 0) {
    //   printf("cnt %d\n", cnt);
    //
    // }
    ++cnt;
    return;
  }
  if (now == 1) {
    // 1 win 2
    dfs(now + 1, sum1 + 3, sum2, sum3, sum4);
    // 1 lose 2
    dfs(now + 1, sum1, sum2 + 3, sum3, sum4);
    // 平
    dfs(now + 1, sum1 + 1, sum2 + 1, sum3, sum4);
  } else if (now == 2) {
    // 1 win 3
    dfs(now + 1, sum1 + 3, sum2, sum3, sum4);
    // 1 lose 3
    dfs(now + 1, sum1, sum2, sum3 + 3, sum4);
    // 平
    dfs(now + 1, sum1 + 1, sum2, sum3 + 1, sum4);
  } else if (now == 3) {
    // 1 win 4
    dfs(now + 1, sum1 + 3, sum2, sum3, sum4);
    // 1 lose 4
    dfs(now + 1, sum1, sum2, sum3, sum4 + 3);
    // 平
    dfs(now + 1, sum1 + 1, sum2, sum3, sum4 + 1);
  } else if (now == 4) {
    // 2 win 3
    dfs(now + 1, sum1, sum2 + 3, sum3, sum4);
    // 2 lose 3
    dfs(now + 1, sum1, sum2, sum3 + 3, sum4);
    // 平
    dfs(now + 1, sum1, sum2 + 1, sum3 + 1, sum4);
  } else if (now == 5) {
    // 2 win 4
    dfs(now + 1, sum1, sum2 + 3, sum3, sum4);
    // 2 lose 4
    dfs(now + 1, sum1, sum2, sum3, sum4 + 3);
    // 平
    dfs(now + 1, sum1, sum2 + 1, sum3, sum4 + 1);
  } else {
    // 3 win 4
    dfs(now + 1, sum1, sum2, sum3 + 3, sum4);
    // 3 lose 4
    dfs(now + 1, sum1, sum2, sum3, sum4 + 3);
    // 平
    dfs(now + 1, sum1, sum2, sum3 + 1, sum4 + 1);
  }
}


int main(int argc, char const *argv[]) {
  dfs(1, 0, 0, 0, 0);
  int t, n1, n2, n3, n4, ca = 1;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d", &n1, &n2, &n3, &n4);
    int sum = 0;
    for (int i = 0; i < cnt; ++i) {
      if (ans[i].sum1 == n1 && ans[i].sum2 == n2 && ans[i].sum3 == n3 && ans[i].sum4 == n4) {
        ++sum;
        //printf("%d\n", i);

        if (sum == 2) {
          break;
        }
      }
    }
    if (sum == 0) {
      printf("Case #%d: Wrong Scoreboard\n", ca++);
    } else if (sum == 1) {
      printf("Case #%d: Yes\n", ca++);
    } else {
      printf("Case #%d: No\n", ca++);
    }
  }
  return 0;
}


// Gym - 101194A
#include <cstdio>
using namespace std;

int main(int argc, char const *argv[]) {
  int t, n, ca = 1;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    printf("Case #%d: %d\n", ca++, n / 3);
  }
  return 0;
}
*/
