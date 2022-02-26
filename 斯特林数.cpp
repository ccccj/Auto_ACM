//
//  main.cpp
//  斯特林数
//
//  Created by admin on 18/9/10.
//  Copyright © 2018年 Amon. All rights reserved.
//
// hdu 3625 第一类斯特林数
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

typedef long long LL;
const int maxn = 25;
void init() {

LL dp[maxn][maxn] = {1};

void init() {
    dp[1][1]=1;

   for(int i = 1; i < maxn; ++i){
        dp[i][i] = 1;
        dp[i][0] = 0;
    }
    for(int i = 2; i < maxn; ++i){
        for(int j = 1; j <= i; ++j){
            dp[i][j] = dp[i - 1][j] * (i - 1) + dp[i - 1][j - 1];
        }
    }

void print() {
    for (int i = 1; i < maxn; ++i) {
        for (int j = 1; j < maxn; ++j) {
            printf("%8lld", dp[i][j]);
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    init();
    //print();
    int t;
    LL n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &k);
        double ans = 0;
        for (int i = 1; i <= k; ++i) {
            ans += dp[n][i];
        }
        for (int i = 1; i <= n; ++i) {
            ans /= i;
        }
        // 减去第一把钥匙在第一个房间的可能性
        ans -= (double)1 / n;
        // 加上第一把钥匙在第一个房间 且其他房间成了k以上个环的可能性
        double ans2 = 0;
        for (int i = (int)k; i <= n - 1; ++i) {
            ans2 += dp[n - 1][i];
        }
        for (int i = 1; i <= n; ++i) {
            ans2 /= i;
        }
        printf("%0.4lf\n", ans + ans2);
    }
    return 0;
}
