//
//  main.cpp
//  acm热身赛
//
//  Created by admin on 18/3/9.
//  Copyright © 2018年 Amon. All rights reserved.
//

#include <iostream>
using namespace std;

int y[32][32];

int main() {
    for (int i = 1; i <= 30; ++i) {
        y[i][1] = 1;
        y[i][i] = 1;
    }
    for (int i = 2; i <= 30; ++i) {
        for (int j = 2; j < i; ++j) {
            y[i][j] = y[i-1][j-1] + y[i-1][j];
        }
    }
    int a;
    scanf("%d", &a);
    for (int i = 1; i <= a; ++i) {
        int j = 1;
        for (; j < i; ++j) {
            printf("%d ", y[i][j]);
        }
        printf("%d\n", y[i][j]);
    }
    while (~scanf("%d", &a)) {
        printf("\n");
        for (int i = 1; i <= a; ++i) {
            int j = 1;
            for (; j < i; ++j) {
                printf("%d ", y[i][j]);
            }
            printf("%d\n", y[i][j]);
        }
    }
    return 0;
}


/*
int main()
{
    int a;
    while (~scanf("%d", &a) && a != 0) {
        if (a % 2 == 0) {
            printf("No Solution!\n");
        } else {
            printf("%d\n", a-1);
        }
    }
    return 0;
}

int main() {
    char a[11];
    int N;
    scanf("%d", &N);
    char b;
    scanf("%c", &b);
    while (N--) {
        for (int i = 0; i < 11; ++i) {
            scanf("%c", &a[i]);
        }
        scanf("%c", &b);
        cout << '6';
        for (int i = 6; i < 11; ++i) {
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}

int main() {
    int N;
    while (~scanf("%d", &N) && N != 0) {
        for (int i = 1; i <= N; ++i) {
            for (int k = N-i; k > 0; --k) {
                printf(" ");
            }
            for (int j = 2*i-1; j > 0; --j) {
                printf("*");
            }
            cout << endl;
        }
    }
    return 0;
}

int gcd(int a, int b) {
    int x = a % b;
    int y = b;
    while (x != 0) {
        a = y;
        b = x;
        x = a % b;
        y = b;
    }
    return b;
}

int main () {
    int a, b;
    while (~scanf("%d%d", &a, &b)) {
        int k = gcd(a, b);
        printf("%d %d\n", k, a*b/k);
    }
    return 0;
}

int main() {
    int a, b , c, d;
    while (~scanf("%d%d%d%d", &a, &b, &c, &d) &&
           (a != 0 || b != 0 || c != 0 || d != 0)) {
        // b + d //卖的钱
        // a + d // 赔的钱
        // b + d - c // 赚的钱
        printf("%d\n", a - b  + c);
    }
    return 0;
}

int main() {
    int a, b;
    while (~scanf("%d%d", &a, &b)) {
        int flag = 0;
        int first = 0;
        for (; a <= b; ++a) {
            int a1, a2, a3;
            a1 = a % 10; // 个位
            a2 = (a / 10) % 10; // 十位
            a3 = (a / 100) % 10;
            if (a == a1*a1*a1 + a2*a2*a2 + a3*a3*a3) {
                flag = 1;
                if (first != 0) {
                    printf(" ");
                }
                printf("%d", a);
                ++first;
            }
        }
        if (flag == 0) {
            printf("no");
        }
        printf("\n");
    }
    return 0;
}

int main() {
    int s;
    while (~scanf("%d", &s)) {
        if (s > 100 || s < 0) {
            printf("Score is error!\n");
        } else {
            if (s <= 59) {
                printf("E\n");
            } else if (s <= 69) {
                printf("D\n");
            } else if (s <= 79) {
                printf("C\n");
            } else if (s <= 89) {
                printf("B\n");
            } else {
                printf("A\n");
            }
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int n;
    int flag = 0;
    while (~scanf("%d", &n)) {
        if (flag != 0) {
            printf("\n");
        }
        printf("%d\n", (1+n)*n / 2);
        ++flag;
    }
    return 0;
}
*/
