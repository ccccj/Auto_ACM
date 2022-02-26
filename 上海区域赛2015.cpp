//
//  main.cpp
//  上海区域赛2015
//
//  Created by admin on 18/9/18.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double EPS = 1e-1;

typedef struct {
    double x, y, r;
} vect, point;

vect creat(point a, point b) {
    return {b.x - a.x, b.y - a.y};
}

double length(vect a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

double dot(vect a, vect b) {
    return a.x * b.x + a.y * b.y;
}

double cross(vect a, vect b) {
    return a.x * b.y - a.y * b.x;
}

bool online(point a, point v, point p) {
    if (fabs((p.y - a.y) * v.x - (p.x - a.x) * v.y) < EPS) {
        return true;
    }
    return false;
}

double distance(point a, point b, point p) {
    vect ap = creat(a, p), bp = creat(b, p), ab = creat(a, b), ba = creat(b, a);
    if (dot(ap, ab) * dot(bp, ba) < 0) {
        return min(length(ap), length(bp));
    } else {
        //printf("l : %f\n", cross(ap, ab)/length(ab));
        return fabs(cross(ap, ab))/length(ab);
    }
}

bool direction(point a, point v, point p) {
    vect ap = creat(a, p);
    //printf ("apx: %f  apy: %f\n", ap.x, ap.y);
    //printf ("v: %f  v: %f\n", v.x, v.y);
    if (dot(ap, (vect)v) >= 0) return true;
    return false;
}

vect bisector(vect a, vect b) {
    double lena = length(a), lenb = length(b);
    a.x /= lena, a.y /= lena, b.x /= lenb, b.y /= lenb;
    // printf("ax: %f, ay: %f\n", a.x, a.y);
    // printf("bx: %f, by: %f\n", b.x, b.y);
    a.x += b.x, a.y += b.y;
    //printf("ax: %f, ay: %f\n", a.x, a.y);
    //printf("bx: %f, by: %f\n", b.x, b.y);
    lena = length(a);
    return {a.x/lena, a.y/lena};
}

point crosspoint(point a, point b, point o) {
    vect oa = creat(o, a), ob = creat(o, b);
    vect c = bisector(oa, ob);
    //printf("xx: %f yy:%f", c.x, c.y);
    return {c.x * o.r + o.x, c.y * o.r + o.y};
}

int main()
{
    int T, ca = 0;
    scanf("%d", &T);
    while (T--) {
        point O, A, B, V;
        scanf("%lf%lf%lf", &O.x, &O.y, &O.r);
        scanf("%lf%lf%lf%lf", &A.x, &A.y, &V.x, &V.y);
        scanf("%lf%lf", &B.x, &B.y);
        printf("Case #%d: ", ++ca);
        if (distance(A, B, O) < O.r) {
            //printf("d : %.20f  r: %.20f\n", distance(A, B, O), O.r);
            printf("No\n");
            continue;
        }
        if (online(A, V, B) && direction(A, V, B)) {
            printf("Yes\n");
            continue;
        }
        point c = crosspoint(A, B, O);
        //printf("x : %f y : %f\n", c.x, c.y);
        //printf("%d, %d\n", online(A, V, c), direction(A, V, c));
        if (online(A, V, c) && direction(A, V, c)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}
/*
// A
#include <cstdio>
#include <cmath>
using namespace std;

const double eps=1e-7;

int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    if (x>0) return 1;
    return -1;
}

struct Vector { // 向量
    double x, y;
    bool operator==(const Vector& a) {
        return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;
    }
};

struct point { // 点
    double x, y;
    Vector operator-(const point& a) {
        Vector tmp = {x - a.x, y - a.y};
        return tmp;
    }
};

// 判断点是否同一个点
bool operator ==(const point& a, const point& b) {
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double dot(Vector A, Vector B) {    //向量点积
    return A.x * B.x + A.y * B.y;
}

double Length(Vector A) {    //向量A长度
    return sqrt(dot(A, A));
}

double cross(Vector A, Vector B)  { //叉积
    return A.x * B.y - A.y * B.x;
}

double DistoLine(point P, point A, point B) //点P到直线AB距离
{
    Vector v1= B - A, v2 = P - A;
    return fabs(cross(v1, v2)) / Length(v1);
}

double DistoSegment(point P, point A, point B){
    if(A == B) return Length(P - A); //两点之间的距离
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(dot(v1, v2)) < 0) return Length(v2); // p点投影到射线
    if (dcmp(dot(v1, v3)) > 0) return Length(v3); // p点投影到射线
    return fabs(cross(v1,v2)) / Length(v1); // p点投影到线段
}


int main() {
    
    int t, ca = 1;
    double ox, oy, r, x1, y1, x2, y2, vx, vy;
    scanf("%d", &t);
    while (t--) {
        printf("Case #%d: ", ca++);
        scanf("%lf%lf%lf", &ox, &oy, &r);
        scanf("%lf%lf%lf%lf", &x1, &y1, &vx, &vy);
        x1 -= ox, y1 -= oy;
        scanf("%lf%lf", &x2, &y2);
        x2 -= ox, y2 -= oy;
        
        double ret = DistoSegment({0, 0}, {x1, y1}, {x2, y2});
        if (ret - r < 0) {
            printf("No\n");
            continue;
        }
        
        if (dcmp(vy*(x2-x1) - vx*(y2-y1)) == 0
            && (y2-y1) * vy >= 0 && (x2-x1) * vx >= 0) {
            printf("Yes\n");
            continue;
        }
        
        double a1 = sqrt(x1*x1 + y1*y1), a2 = sqrt(x2*x2 + y2*y2);
        double x = x1 / a1 + x2 / a2, y = y1 / a1 + y2 / a2;
        double sum = sqrt(x*x + y*y);
        x /= sum, y /= sum;
        x *= r, y *= r;
        
        //printf("%lf %lf\n", x, y);
        if (dcmp(vy*(x-x1) - vx*(y-y1)) == 0) {
            if ((y-y1) * vy >= 0 && (x-x1) * vx >= 0) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        } else {
            printf("No\n");
        }
    }
    return 0;
}



// B
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
typedef long long LL;

struct node {
    bool op; // 1+ 0-
    LL num;
};

vector<node> ans;

int main() {
    int t, k, ca = 1;
    LL n;
    scanf("%d", &t);
    while (t--) {
        printf("Case #%d:\n", ca++);
        ans.clear();
        scanf("%lld%d", &n, &k);
        LL Min = pow(2, k);
        if (n % 2 == 0) {
            ans.push_back({1, Min / 2 + 1});
            n -= Min / 2 + 1;
        } else {
            ans.push_back({1, Min / 2});
            n -= Min / 2;
        }
        --k;
        
        while (k) {
            Min = pow(2, k);
            if (n % 2 == 0) {
                // 右边
                if (n > 0) {
                    ans.push_back({1, Min / 2 + 1});
                    n -= Min / 2 + 1;
                } else {
                    ans.push_back({0, Min / 2 + 1});
                    n += Min / 2 + 1;
                }
            } else {
                // 左边
                if (n > 0) {
                    ans.push_back({1, Min / 2});
                    n -= Min / 2;
                } else {
                    ans.push_back({0, Min / 2});
                    n += Min / 2;
                }
            }
            --k;
        }
        int len = (int)ans.size();
        for (int i = len - 1; i >= 0; --i) {
            printf("%lld ", ans[i].num);
            if (ans[i].op == 0) {
                printf("-\n");
            } else {
                printf("+\n");
            }
        }
    }
    return 0;
}


// F
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1010;
struct node {
    int x, xiabiao;
} arr[maxn];

bool cmp(struct node a, struct node b) {
    if (a.x == b.x) {
        return a.xiabiao < b.xiabiao;
    }
    return a.x < b.x;
}

int main() {
    int t, ca = 1;
    char str[maxn];
    scanf("%d", &t);
    getchar();
    while (t--) {
        scanf("%s", str);
        int len = (int)strlen(str);
        for (int i = 0; i < len; ++i) {
            arr[i] = {str[i] - 'a', i};
        }
        sort(arr, arr + len, cmp);
        int Min = 0x3f3f3f3f;
        for (int i = 1; i < len; ++i) {
            if (arr[i].x == arr[i-1].x) {
                Min = min(Min, arr[i].xiabiao - arr[i-1].xiabiao);
            }
        }
        if (Min == 0x3f3f3f3f) {
            Min = -1;
        }
        printf("Case #%d: %d\n", ca++, Min);
        
    }
    return 0;
}


// L
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL ans;

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        LL x, y;
        scanf("%lld%lld", &x, &y);
        ans = 1;
        while (1) {
            if (x < y) {
                swap(x, y);
            }
            LL g = gcd(x, y);
            if (x % (g + y) != 0) {
                break;
            } else {
                ++ans;
                LL m = x / (g + y);
                x -= m * y;
            }
        }
        printf("Case #%d: %lld\n", ca++, ans);
    }
    return 0;
}


#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
char str[maxn];
LL num[maxn];

LL _abs(LL a) {
    return a > 0 ? a : -a;
}

int main(int argc, const char * argv[]) {
    int t, ca = 1;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);

        LL Max = 0, now = 1, cnt = 0, f = 0;
        LL ans = 0;
        for (int i = 1; str[i]; ++i) {
            if (str[i] == str[i - 1]) {
                ++now;
            } else {
                num[cnt++] = now;
                ans += now * now;
                now = 1;
                f = 1;
            }
        }
        num[cnt++] = now;
        for (int i = 1; i < cnt; ++i) {
            Max = max(_abs(num[i]-num[i-1]), Max);
        }
        if (f) {
            Max = Max * 2 + 2;
        }
        for (int i = 1; i < cnt - 1; ++i) {
            if (num[i] == 1) {
                LL k = (num[i-1] + num[i+1] + num[i-1] * num[i + 1]) * 2;
                if (k > Max) {
                    Max = k;
                }
            }
        }
        printf("Case #%d: %lld\n", ca++, ans + Max + now * now);
    }
    return 0;
}

*/
