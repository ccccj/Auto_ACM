#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 10;
double ans[maxn], ave;
int arr[maxn], tree[maxn << 2], num[maxn];

void pushup(int now) {
  if (ans[tree[now << 1]] > ans[tree[(now << 1)|1]]) {
    tree[now] = tree[now << 1];
  } else {
    tree[now] = tree[(now << 1)|1];
  }
}

void build(int l, int r, int now) {
  if (l == r) {
    ans[l] = (arr[l] / (num[l] + 1) - ave) * (arr[l] / (num[l] + 1) - ave);
    tree[now] = l;
    return;
  }
  int m = (l + r) / 2;
  build(l, m, now << 1);
  build(m + 1, r, (now << 1)|1);
  pushup(now);
}

void update(int l, int r, int now, int tar) {
  if (l == r) {
    ++num[l];
    ans[l] = (double)arr[l] / num[l];
    return;
  }
  int m = (l + r) / 2;
  if (tar <= m) update(l, m, now << 1, tar);
  else update(m + 1, r, (now << 1)|1, tar);
  pushup(now);
}

int main() {

  int t, ca = 1, n, m;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &arr[i]);
      sum += arr[i];
      num[i] = 1;
    }
    ave = sum / m;
    build(1, n, 1);
    m -= n;
    while (m) {
      --m;
      update(1, n, 1, tree[1]);
    }


    sum = 0;
    for (int i = 1; i <= n; ++i) {
      sum += (ans[i] - ave) * (ans[i] - ave);
    }
    sum /= m;
    printf("Case #%d: %.12f\n", ca++, sum);
  }
  return 0;
}

/*
// Gym - 101775J
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 7;
int arr[maxn], d[maxn];

int main(){
    int t, n;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas++){
      scanf("%d", &n);
      for(int i = 1; i <= n; i++){
        scanf("%d", &arr[i]);
        d[i] = arr[i] - arr[i - 1];
      }
      d[n + 1] = -arr[n];
      bool flag = 1;
      int r = 4;
      for (int i = 1; i <= n + 1; ++i) {
        if (d[i] < 0) {
          flag = 0;
          break;
        }
        if (d[i] > 0) {
          for (int j = max(r, i + 3); j <= n + 1; ++j) {
            r = j;
            if (d[j] >= 0) continue;
            if (d[i] + d[j] <= 0) {
              d[j] += d[i];
              d[i] = 0;
              break;
            } else {
              d[i] += d[j];
              d[j] = 0;
            }
          }
          if (d[i] > 0) {
            flag = 0;
            break;
          }
        }
      }
      if (flag) printf("Case #%d: Yes\n", cas);
      else printf("Case #%d: No\n", cas);
    }
    return 0;
}


// Gym 101775C
#include <cstdio>
typedef long long LL;

LL max(LL a, LL b) {
  return a > b ? a : b;
}

using namespace std;
int main() {
  LL t, ca = 1, n, x, y;
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &n);
    LL Max = 0, ans = 0;
    for (int i = 0; i <= n; ++i) {
      scanf("%lld", &x);
      ans += x;
    }
    for (int i = 0; i < n; ++i) {
      scanf("%lld%lld", &x, &y);
      Max = max(Max, y);
    }
    printf("Case #%lld: %lld.000000\n", ca++, Max + ans);

  }

  return 0;
}


// Gym 101775A
#include <cstdio>
using namespace std;
typedef long long LL;
const int mod = 1000000007;

LL fast_pow(LL a, LL b) {
  LL ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * a % mod;
    }
    b >>= 1;
    a = a * a % mod;
  }
  return ans;
}

LL inv(LL a) {
  return fast_pow(a, mod - 2);
}

LL S(LL n, LL k) { // 计算 S(n, k)
  LL ans = 1, C = n - k;
  for (int i = 1; i <= k; ++i) {
    ans = (ans * 2 % mod + C) % mod;
    C = C * (n - k + i) % mod * inv(i + 1) % mod;
    //printf("%lld\n", ans);

  }
  return ans;
}

int main() {
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    LL n, k;
    scanf("%lld%lld", &n, &k);

    printf("Case #%d: %lld\n", ca++, (fast_pow(2, n) - S(n, k - 1) + mod ) % mod);
  }
  return 0;
}


// Gym 101775K
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
LL sum[maxn], Next[maxn];

int main() {
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    LL A, B, N, x;
    scanf("%lld%lld%lld", &A, &B, &N);
    for (int i = 1; i <= A; ++i) {
      scanf("%lld", &x);
      sum[i] = sum[i - 1] + x;
    }
    for (LL i = 1; i <= A; ++i) {
      LL pos = lower_bound(sum + 1, sum + A + 1, i) - sum;
      Next[i] = pos;
      //printf("%lld %lld\n", i, Next[i]);
    }
    LL now = A, Last = 1;
    while (!(Next[now] == now && Last == 1) && N) {
      --N;
      Last = now - sum[Next[now] - 1];
      now = Next[now];
      //printf("%lld-%lld\n", now, Last);
    }
    printf("Case #%d: %lld-%lld\n", ca++, now, Last);
  }
  return 0;
}


// Gym 101775M
#include <cstdio>
#include <cstring>
const int maxn = 70;
int price[10], arr[maxn];

int main() {
  int t, ca = 1, n, x;
  scanf("%d", &t);
  while (t--) {
    memset(arr, 0, sizeof arr);

    for (int i = 1; i <= 5; ++i) {
      scanf("%d", &price[i]);
    }
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &x);
      ++arr[x];
    }
    long long int ans = 0;
    for (int i = 1; i <= 48; ++i) ans += price[1] * arr[i];
    for (int i = 49; i <= 56; ++i) ans += price[2] * arr[i];
    for (int i = 57; i <= 60; ++i) ans += price[3] * arr[i];
    for (int i = 61; i <= 62; ++i) ans += price[4] * arr[i];
    ans += arr[63] * price[5];
    printf("Case #%d: %lld0000\n", ca++, ans);
  }
  return 0;
}
*/
