//
//  main.cpp
//  长春
//
//  Created by admin on 18/10/11.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10;
int n;
const double pi = acos(-1.0), eps = 1e-8;
double x[maxn], y[maxn], d[maxn];

double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

double ans(double r) {
    double area = 0;
    for (int i = 1; i <= n; ++i) {
        area += r*r;
        r = d[i] - r;
    }
    return area;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &x[i], &y[i]);
            if (i > 0) d[i] = dis(x[i], y[i], x[i-1], y[i-1]);
        }
        d[n] = dis(x[0], y[0], x[n-1], y[n-1]);
        double sum = 0, Max = 999999999, Min = 0, tmp = 0;
        for (int i = 1; i <= n; ++i) {
            sum += pow(-1, (i+1) % 2) * d[i];
            tmp = d[i] - tmp;
            if (i % 2) {
                Max = min(Max, tmp);
            } else {
                Min = max(Min, -tmp);
            }
        }
        if (Min > Max) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        if (n % 2) {
            double r = sum/2;
            if (r > Max || r < Min || r < -eps) {
                printf("IMPOSSIBLE\n");
                continue;
            }
            printf("%.2lf\n", ans(r) * pi);
            
            for (int i = 1; i <= n; ++i) {
                printf("%.2lf\n", r);
                r = d[i] - r;
            }
        } else {
            if (fabs(sum) > eps) {
                printf("IMPOSSIBLE\n");
                continue;
            }
            double r1, r2;
            while (1) {
                r1 = (Min + Max)/ 2;
                r2 = (r1 + Max) / 2;
                if (fabs(Min - Max) < eps) {
                    break;
                }
                double S1 = ans(r1), S2 = ans(r2);
                if (S1 >= S2) {
                    Min = r1;
                } else if (S1 < S2) {
                    Max = r2;
                }
            }
            double r = Min;
            printf("%.2lf\n", ans(r)*pi);
            r = Min;
            for (int i = 1; i <= n; ++i) {
                printf("%.2lf\n", r);
                r = d[i] - r;
            }
        }
    }
    return 0;
}
/*
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-6;
const int maxn = 200;
int T, n;
typedef struct node {
    double x, y;
    node() {};
    node(double o, double p) {
        x = o, y = p;
    };
} point, vvector;
point p[maxn], G;

vvector operator + (vvector a, vvector b) {
    return vvector (a.x + b.x, a.y + b.y);
}
vvector operator - (vvector a, vvector b) {
    return vvector (a.x - b.x, a.y - b.y);
}
vvector operator * (vvector a, double p) {
    return vvector (a.x * p, a.y * p);
}
vvector operator / (vvector a, double p) {
    return vvector (a.x/p, a.y/p);
}

bool dy(double x,double y)  {   return x > y + eps;} // x > y
bool xy(double x,double y)  {   return x < y - eps;} // x < y
bool dyd(double x,double y) {   return x > y - eps;} // x >= y
bool xyd(double x,double y) {   return x < y + eps;} // x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}  // x == y

bool cmp(point a, point b)   // 第一次排序
{
    double k1 = (a.y-p[0].y)/(a.x-p[0].x+eps), k2 = (b.y-p[0].y)/(b.x-p[0].x+eps);
    if (k1 < 0 && k2 < 0) {
        return k1 > k2;
    }
    if (k1 * k2 < 0) {
        return k1 < k2;
    }
    return k1 > k2;
}

bool cmp2(point a,point b)
{
    point c;//原点
    c.x = p[0].x;
    c.y = p[0].y;
    if(compare(c,a,b)==0)//计算叉积，函数在上面有介绍，如果叉积相等，按照X从小到大排序
        return a.x<b.x;
    else return compare(c,a,b)>0;
}

bool cmp1(point a, point b) {
    if (fabs(a.x - b.x) < eps) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

double cross(vvector a, vvector b) {
    return a.x * b.y - a.y * b.x;
}

point PolyGravity(point *p, int n) {
    point ans = point(0, 0);
    double sumArea = 0, area;
    for(int i = 2; i < n; i++) {
        area = cross(p[i - 1] - p[0], p[i] - p[0]);
        sumArea += area;
        ans.x += (p[0].x + p[i-1].x + p[i].x) * area;
        ans.y += (p[0].y + p[i-1].y + p[i].y) * area;
    }
    return ans / (sumArea*3);
}

double dot(vvector a, vvector b) {
    return a.x*b.x+a.y*b.y;
}

double len(vvector a) {
    return sqrt(dot(a, a));
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        sort(p, p + n, cmp1);
        sort(p + 1, p + n, cmp);
//        for (int i = 0; i < n; ++i) {
//            printf("%lf %lf\n", p[i].x, p[i].y);
//        }
        G = PolyGravity(p, n);
        //printf("%lf %lf\n", G.x, G.y);
        double R = len(p[0] - G), dis = len(p[0] - p[1]);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (fabs(len(p[i] - p[i - 1]) - dis) <= eps
                && fabs(len(p[i] - G) - R) <= eps) {
                ans++;
            }
        }
        if (fabs(len(p[0] - p[n - 1]) - dis) <= eps) {
            ans++;
        }
        if (ans == n) printf("YES\n");
        else printf("NO\n");
    }
    
    return 0;
}


// hdu 5532
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10;
int arr1[maxn], arr2[maxn], arr3[maxn];
bool cmp(int a, int b) {
    return a > b;
}
int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr1[i]);
            arr3[i] = arr2[i] = arr1[i];
        }
        sort(arr2, arr2 + n);
        sort(arr3, arr3 + n, cmp);
        int i1 = 0, j1 = 0;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        if (i1 == n && j1 == n) {
            printf("YES\n");
            continue;
        }
        ++i1;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        ++j1;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        if (i1 == n && j1 == n) {
            printf("YES\n");
            continue;
        }
        i1 = 0, j1 = 0;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        if (i1 == n && j1 == n) {
            printf("YES\n");
            continue;
        }
        ++j1;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        ++i1;
        while (arr1[i1] == arr2[j1] && i1 < n && j1 < n) {
            ++i1, ++j1;
        }
        if (i1 == n && j1 == n) {
            printf("YES\n");
        } else {
            i1 = 0, j1 = 0;
            while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                ++i1, ++j1;
            }
            if (i1 == n && j1 == n) {
                printf("YES\n");
                continue;
            }
            ++j1;
            while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                ++i1, ++j1;
            }
            ++i1;
            while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                ++i1, ++j1;
            }
            if (i1 == n && j1 == n) {
                printf("YES\n");
            } else {
                i1 = 0, j1 = 0;
                while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                    ++i1, ++j1;
                }
                if (i1 == n && j1 == n) {
                    printf("YES\n");
                    continue;
                }
                ++i1;
                while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                    ++i1, ++j1;
                }
                ++j1;
                while (arr1[i1] == arr3[j1] && i1 < n && j1 < n) {
                    ++i1, ++j1;
                }
                if (i1 == n && j1 == n) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }
        }
    }
    return 0;
}

// hdu 5538
#include <cstdio>
using namespace std;
const int maxn = 55;
typedef long long LL;
LL Map[maxn][maxn];

int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1}, n, m;

bool canstay(int x, int y) {
    if (x >= 0 && y >= 0 && x < n && y < m) {
        return 1;
    }
    return 0;
}

LL judge(int x, int y) {
    LL ans = 0;
    for (int i = 0; i < 4; ++i) {
        int a = x + dir[i][0], b = y + dir[i][1];
        if (canstay(a, b)) {
            if (Map[a][b] < Map[x][y]) {
                ans += Map[x][y] - Map[a][b];
            }
        } else {
            ans += Map[x][y];
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        LL sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%lld", &Map[i][j]);
                if (Map[i][j]) ++sum;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                sum += judge(i, j);
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}
*/
