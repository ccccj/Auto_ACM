
// C
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int maxn = 2e5 + 10, mod = 1000000007;
LL fact[maxn] = {1}, inv[maxn];

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

void init() {
    for (int i = 1; i < maxn; ++i) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv[maxn - 1] = fast_pow(fact[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; --i) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}

LL C(int n, int m) {
    if (n < m) return 0;
    return fact[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    freopen("/Users/Amon/Desktop/C-small-attempt0.in.txt", "r", stdin);
    freopen("/Users/Amon/Desktop/out1.txt", "w", stdout);
    init();
    int t, n, m, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        
        LL ans = fact[2 * n];
        for (int i = 1; i <= m; ++i) {
            ans = (ans + (LL)pow(-1, i % 2) * fast_pow(2, i) * C(m, i) % mod * fact[2 * n - i] % mod) % mod;
        }
        
        printf("Case #%d: %lld\n", ca++, (ans + mod) % mod);
    }
    return 0;
}

/*
int main() {
    init();
    int t, n, m, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int k = 2 * (n - m);
        LL ans = fact[k];
        printf("ans: %lld\n", ans);
        ++k;
        while(m--) {
            ans = ans * 2 * C(k, 2) % mod;
            printf("ans: %lld\n", ans);
            k += 2;
        }
        printf("Case #%d: %lld\n", ca++, ans);
    }
    return 0;
}


// B
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5e6 + 10;
int n;
char str[maxn];

int slove() {
    int l = 0, r = (n - 1) / 2, sum = 0, Max = 0;
    for (int i = l; i <= r; ++i) {
        sum += str[i] - '0';
    }
    ++r;
    Max = sum;
    for (; r < n; ++l, ++r) {
        sum -= str[l] - '0';
        sum += str[r] - '0';
        Max = max(Max, sum);
    }
    return Max;
}

int main() {
    //freopen("/Users/Amon/Desktop/B-large.in.txt", "r", stdin);
    //freopen("/Users/Amon/Desktop/out.txt", "w", stdout);
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%s", &n, str);
        printf("Case #%d: %d\n", ca++, slove());
    }
    return 0;
}


// A
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 1e5;
LL ans;
int trie[maxn][2], cnt, n;
bool isend[maxn];

void insert(char* str, int rt) {
    for (int i = 0; str[i]; ++i) {
        int x = (str[i] == 'R') ? 0 : 1;
        if (isend[rt] == true) return;
        
        if (trie[rt][x] == 0) {
            trie[rt][x] = ++cnt;
        }
        rt = trie[rt][x];
    }
    isend[rt] = true;
}

void find(int rt, int len) {
    if (isend[rt] == true) {
        ans -= pow(2, n - len);
        //printf("%d\n", (int)pow(2, n - len));
        return;
    }
    for (int i = 0; i <= 1; ++i) {
        if (trie[rt][i]) find(trie[rt][i], len + 1);
    }
}

int main(int argc, const char * argv[]) {
    //freopen("/Users/Amon/Desktop/A-large.in.txt", "r", stdin);
    //freopen("/Users/Amon/Desktop/out.txt", "w", stdout);
    int t, m, ca = 1;
    char str[55];
    scanf("%d", &t);
    while (t--) {
        memset(trie, 0, sizeof(trie));
        memset(isend, false, sizeof(isend));
        cnt = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            scanf("%s", str);
            insert(str, 0);
        }
        ans = pow(2, n);
        find(0, 0);
        
        printf("Case #%d: %lld\n", ca++, ans);
    }
    return 0;
}
*/
