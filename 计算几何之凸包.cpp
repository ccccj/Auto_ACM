//
//  main.cpp
//  计算几何——凸包
//
//  Created by admin on 18/10/28.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 4e4;
const double eps = 1e-8;
int n, l, r;

typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

struct Line {
    Point s, e;
    Vector v;
    double ang;
    Line() {}
    Line(Point a, Point b) {
        s = a, e = b, v = b - a;
        ang = atan2(v.y, v.x);
    }
} line[maxn], dq[maxn];

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp(Line a, Line b) {
    //if (fabs(a.ang - b.ang) < eps) return cross(a.e - b.s, b.v) < eps;
    if (fabs(a.ang - b.ang) < eps) return cross(a.e - b.s, b.v) < 0;
    return a.ang < b.ang;
}

Point get_point(Line a, Line b) {
    Point ans = a.s;
    double t = cross(b.s - a.s, b.v) / cross(a.v, b.v);
    ans.x += t * (a.e.x - a.s.x);
    ans.y += t * (a.e.y - a.s.y);
    return ans;
}

bool onLeft(Point p, Line a) {
    return cross(p - a.s, a.v) < eps;
}

double find_S() {
    Point p[maxn];
    int cnt = 0;
    for (int i = l; i < r; ++i) {
        p[cnt++] = get_point(dq[i], dq[(i+1) % (r-l+1)]);
    }
    p[cnt++] = get_point(dq[r], dq[l]);
    
    double ans = 0;
    for (int i = 1; i < cnt - 1; ++i) {
        ans += cross(p[i] - p[0], p[i+1] - p[0]);
    }
    return fabs(ans)/2;
}

double halfPlaneIntersection() {
    sort(line, line + n, cmp);
    int tmp = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(cross(line[tmp].v, line[i].v)) > eps) {
            line[++tmp] = line[i];
        }
    }
    n = tmp + 1;
    dq[0] = line[0];
    for (int i = 1; i < n; ++i) {
        while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[i])) {
            --r;
        }
        while (r > l && !onLeft(get_point(dq[l], dq[l+1]), line[i])) {
            ++l;
        }
        dq[++r] = line[i];
    }
    while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[l])) {
        --r;
    }
    while (r > l && !onLeft(get_point(dq[l], dq[l+1]), line[r])) {
        ++l;
    }
    if (r - l <= 1) return 0;
    return find_S();
}

int main() {
    
    scanf("%d", &n);
    Point p1, p2;
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y);
        line[i] = Line(p1, p2);
    }
    line[n++] = Line(Point(0, 0), Point(10000, 0));
    line[n++] = Line(Point(10000, 0), Point(10000, 10000));
    line[n++] = Line(Point(10000, 10000), Point(0, 10000));
    line[n++] = Line(Point(0, 10000), Point(0, 0));
    
    printf("%.1f\n", halfPlaneIntersection());
    
    return 0;
}

/*
// poj 1474
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const double eps = 1e-8;
int n;

typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;
Point p[maxn];

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

struct Line {
    Point s, e;
    Vector v;
    double ang;
    Line() {}
    Line(Point a, Point b) {
        s = a, e = b, v = e - s;
        ang = atan2(v.y, v.x);
    }
} line[maxn], dq[maxn];

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge() {
    double ans = 0;
    for (int i = 1; i < n - 1; ++i) {
        ans += cross(p[i] - p[0], p[i+1] - p[0]);
    }
    return ans < 0;
}

bool cmp(Line a, Line b) {
    if (fabs(a.ang - b.ang) < eps) return cross(a.e - b.s, b.v) < 0;
    return a.ang < b.ang;
}

Point get_point(Line a, Line b) {
    Point ans = a.s;
    double t = cross(b.s - a.s, b.v) / cross(a.v, b.v);
    ans.x += t * (a.e.x - a.s.x);
    ans.y += t * (a.e.y - a.s.y);
    return ans;
}

bool onLeft(Point p, Line a) {
    return cross(a.v, p - a.s) > -eps;
}

bool halfPlaneIntersection() {
    sort(line, line + n, cmp);
    int tmp = 0, l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(cross(line[tmp].v, line[i].v)) > eps) {
            line[++tmp] = line[i];
        }
    }
    n = tmp + 1;
    dq[0] = line[0];
    for (int i = 1; i < n; ++i) {
        while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[i])) {
            --r;
        }
        while (r > l && !onLeft(get_point(dq[l], dq[l+1]), line[i])) {
            ++l;
        }
        dq[++r] = line[i];
    }
    while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[l])) {
        --r;
    }
    return r - l > 1;
}

int main() {
    int ca = 0;
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if (judge()) {
            for (int i = 0; i < n; ++i) {
                line[i] = Line(p[(i+1) % n], p[i]);
            }
        } else {
            for (int i = 0; i < n; ++i) {
                line[i] = Line(p[i], p[(i+1) % n]);
            }
        }
        printf("Floor #%d\n", ++ca);
        if (halfPlaneIntersection()) {
            printf("Surveillance is possible.\n\n");
        } else {
            printf("Surveillance is impossible.\n\n");
        }
    }
    return 0;
}


// poj 1279
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 2010;
const double eps = 1e-8;
int n;

typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Point p[maxn];

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

struct Line {
    Point s, e;
    Vector v;
    double ang;
    Line() {}
    Line(Point a, Point b) {
        s = a, e = b, v = e - s;
        ang = atan2(v.y, v.x);
    }
} line[maxn], dq[maxn];

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge() {
    double ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        ans += cross(p[i] - p[0], p[i+1] - p[0]);
    }
    return ans < 0;
}

bool cmp(struct Line a, struct Line b) {
    if (fabs(a.ang - b.ang) < eps) return cross(a.e - b.s, b.v) < 0;
    return a.ang < b.ang;
}

bool onLeft(Point p, Line a) {
    return cross(p - a.s, a.v) < 0;
}

Point get_point(Line a, Line b) {
    double a1 = a.s.y - a.e.y, b1 = a.e.x - a.s.x, c1 = a.s.x * a.e.y - a.e.x * a.s.y;
    double a2 = b.s.y - b.e.y, b2 = b.e.x - b.s.x, c2 = b.s.x * b.e.y - b.e.x * b.s.y;
    return Point((c1*b2-c2*b1)/(a2*b1-a1*b2), (a2*c1-a1*c2)/(a1*b2-a2*b1));
}

double find_S(int l, int r) {
    double ans = 0;
    Point tmp[maxn];
    int cnt = 0;
    for (int i = l; i <= r; ++i) {
        tmp[cnt++] = get_point(dq[i], dq[(i+1) % (r - l + 1)]);
    }
    for (int i = 1; i < cnt - 1; ++i) {
        ans += cross(tmp[i] - tmp[0], tmp[i + 1] - tmp[0]);
    }
    return fabs(ans / 2);
}

double halfPlaneIntersection() {
    sort(line, line + n, cmp);
    int tmp = 0, l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(cross(line[tmp].v, line[i].v)) > eps) {
            line[++tmp] = line[i];
        }
    }
    
    n = tmp + 1;
    dq[0] = line[0];
    for (int i = 1; i < n; ++i) {
        while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[i])) {
            --r;
        }
        while (r > l && !onLeft(get_point(dq[l], dq[l+1]), line[i])) {
            ++l;
        }
        dq[++r] = line[i];
    }
    while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[l])) {
        --r;
    }
    if (r - l <= 1) return 0;
    return find_S(l, r);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if (judge()) {
            for (int i = n - 1; i >= 0; --i) {
                line[i] = Line(p[(i + 1) % n], p[i]);
            }
        } else {
            for (int i = 0; i < n; ++i) {
                line[i] = Line(p[i], p[(i + 1) % n]);
            }
        }
        printf("%.2f\n", halfPlaneIntersection());
    }
    return 0;
}


// poj 3335
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10010;
const double eps = 1e-8;
int n;
typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

Point p[maxn];

struct Line {
    Point s, e;
    Vector v;
    double ang;
    Line() {}
    Line(Point a, Point b) {
        s = a, e = b, v = e - s;
        ang = atan2(v.y, v.x);
    }
} line[maxn], dq[maxn];

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

Point get_point(Line a, Line b) {
    Point ans = a.s;
    double t = cross(b.v, b.s - a.s) / cross(b.v, a.v);
    ans.x += t * (a.e.x - a.s.x);
    ans.y += t * (a.e.y - a.s.y);
    return ans;
}

bool onLeft(Point p, Line a) {
    return cross(p - a.s, a.v) < eps;
}

double findS(int l, int r) {
    Point tmp[maxn];
    int cnt = 0;
    for (int i = l; i < r; ++i) {
        tmp[cnt++] = get_point(dq[i], dq[i + 1]);
    }
    tmp[cnt++] = get_point(dq[r], dq[l]);
    for (int i = 0; i < cnt; ++i) {
        printf("i %d %lf %lf\n", i, tmp[i].x, tmp[i].y);
    }
    double s = 0;
    for (int i = 1; i < cnt - 1; ++i) {
        s += cross(tmp[i], tmp[i + 1]);
    }
    return fabs(s) / 2;
}

bool cmp(Line a, Line b) {
    if (fabs(a.ang - b.ang) < eps) {
        return cross(a.e - b.s, b.v) < 0;
    }
    return a.ang < b.ang;
}

bool halfPlaneIntersection() {
    sort(line, line + n, cmp);
    // 平行特判
    int tmp = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(cross(line[tmp].v, line[i].v)) > eps) {
            line[++tmp] = line[i];
        }
    }
    
    dq[0] = line[0];
    int l = 0, r = 0;
    for (int i = 1; i <= tmp; ++i) {
        while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[i])) {
            --r;
        }
        while (r > l && !onLeft(get_point(dq[l], dq[l+1]), line[i])) {
            ++l;
        }
        dq[++r] = line[i];
    }
    // 删除无用平面
    while (r > l && !onLeft(get_point(dq[r], dq[r-1]), line[l])) {
        --r;
    }
    return r - l > 1;
}

bool judge() {
    double ans = 0;
    for (int i = 1; i < n - 1; ++i) {
        ans += cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return ans < 0; // 顺时针
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if (judge()) {
            for (int i = n - 1; i >= 0; --i) {
                line[i] = Line(p[(i + 1) % n], p[i]);
            }
        } else {
            for (int i = 0; i < n; ++i) {
                line[i] = Line(p[i], p[(i + 1) % n]);
            }
        }
        if (halfPlaneIntersection()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}


// poj 3348
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int maxn = 10010;
int n, cnt;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;
Point p[maxn], s[maxn];

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool cmp(Point a, Point b) {
    return cross(a - p[0], b - p[0]) > 0;
}

void polygon() {
    int t = 0;
    for (int i = 1; i < n; ++i) {
        if (p[t].y > p[i].y || (p[t].y == p[i].y && p[t].x > p[i].x)) {
            t = i;
        }
    }
    if (t != 0) swap(p[0], p[t]);
    
    sort(p + 1, p + n, cmp);
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (cnt > 1 &&
               cross(s[cnt-1]-s[cnt-2], p[i]-s[cnt-1]) <= 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    
    if (cnt > 1) --cnt;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    polygon();
    
    Point start = s[0];
    int ans = 0;
    for (int i = 1; i < cnt; ++i) {
        ans += abs(cross(s[i]-start, s[i+1]-start));
    }
    printf("%d\n", ans/100);
    
    return 0;
}

// poj 3348
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int maxn = 10010;
int n, cnt;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;
Point p[maxn], s[maxn];

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

bool cmp(Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

void polygon() {
    sort(p, p + n, cmp);
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (cnt > 1 &&
               cross(s[cnt-1]-s[cnt-2], p[i]-s[cnt-1]) >= 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    int k = cnt;
    for (int i = n - 2; i >= 0; --i) {
        while (cnt > k &&
               cross(s[cnt-1]-s[cnt-2], p[i]-s[cnt-1]) >= 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    if (cnt > 1) --cnt;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    polygon();
    
    Point start = s[0];
    int ans = 0;
    for (int i = 1; i < cnt; ++i) {
        ans += abs(cross(s[i]-start, s[i+1]-start));
    }
    printf("%d\n", ans/100);
    
    return 0;
}


// poj 1228
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n, cnt;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;
Point p[maxn], s[maxn];

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int mult(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

bool cmp(Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

void polygon() {
    sort(p, p + n, cmp);
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (cnt > 1 &&
               cross(s[cnt-1]-s[cnt-2], p[i]-s[cnt-1]) >= 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    int k = cnt;
    for (int i = n - 2; i >= 0; --i) {
        while (cnt > k &&
               cross(s[cnt-1]-s[cnt-2], p[i]-s[cnt-1]) >= 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    if (cnt > 1) --cnt;
}

bool onSegment(Point pi, Point pj, Point pk) {
    return cross(pk-pi, pj-pi) == 0 && mult(pi-pk, pj-pk);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &p[i].x, &p[i].y);
        }
        polygon();
        if (n < 6 || cnt < 3) {
            printf("NO\n");
            continue;
        }
        int f = 1;
        for (int i = 0; i < cnt - 1; ++i) {
            int k = 0;
            for (int j = 0; j < n; ++j) {
                if (onSegment(s[i], s[i+1], p[j])) ++k;
            }
            if (k == 0) {f = 0; break;}
        }
        if (f) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}


// poj 1873
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 20;
const double EPS = 1e-8;
int n, v, sta, cnt;
double wood;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;

struct node {
    Point p;
    int value, len;
} p[maxn], tmp[maxn], s[maxn];

bool cmp(struct node a, struct node b) {
    if (a.p.x == b.p.x) return a.p.y < b.p.y;
    return a.p.x < b.p.x;
}

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double dis(Point a, Point b) {
    return sqrt((double)((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
}

double judge() {
    if (cnt == 1) {
        return wood;
    } else if (cnt == 2) {
        return wood - dis(tmp[0].p, tmp[1].p) * 2;
    }
    sort(tmp, tmp + cnt, cmp); // 原本的数组, cnt 数组长度
    int tot = 0; // 栈的长度
    s[tot++] = tmp[0], s[tot++] = tmp[1]; // 栈
    for (int i = 2; i < cnt; ++i) {
        while (tot > 1 &&
               cross(s[tot-1].p-s[tot-2].p, tmp[i].p-s[tot-1].p) >= 0) {
            --tot;
        }
        s[tot++] = tmp[i];
    }
    int k = tot;
    for (int i = cnt - 2; i >= 0; --i) {
        
        while (tot > k &&
               cross(s[tot-1].p-s[tot-2].p, tmp[i].p-s[tot-1].p) >= 0) {

            --tot;
        }
        s[tot++] = tmp[i];
    }
    for (int i = 0; i < tot - 1; ++i) {
        wood -= dis(s[i].p, s[i+1].p);
    }
    return wood;
}

void Print(int sta) {
    printf("Cut these trees:");
    for (int i = 0; i < n; ++i) {
        if (((sta >> i) & 1) == 0) {
            printf(" %d", i + 1);
        }
    }
    printf("\n");
}

int main() {
    int ca = 0;
    while (~scanf("%d", &n) && n) {
        if (ca != 0) {
            printf("\n");
        }
        printf("Forest %d\n", ++ca);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d", &p[i].p.x, &p[i].p.y, &p[i].value, &p[i].len);
        }
        int tot = 1 << n, Max = -1, num = 0, res = 0;
        double re = 0;
        
        for (int i = 0; i < tot; ++i) {
            wood = v = cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (((i >> j) & 1) == 0) {
                    // 不要
                    wood += p[j].len;
                } else {
                    v += p[j].value, tmp[cnt++] = p[j];
                }
            }
            double ans = judge();
            if ((ans >= -EPS && Max < v) || (ans >= -EPS && Max == v && cnt < res)) {
                Max = v, sta = i, re = ans, res = num;
            }
        }
        Print(sta);
        printf("Extra wood: %.2f\n", re);
    }
    return 0;
}


// poj 2007
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 100;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;

Point p[maxn];

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

bool cmp(Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int n = 0;
    while (~scanf("%d%d", &p[n].x, &p[n].y)) {
        ++n;
    }
    sort(p, p + n, cmp);
    Point s[maxn];
    int cnt = 0;
    s[cnt++] = p[0], s[cnt++] = p[1];
    for (int i = 2; i < n; ++i) {
        while (cnt > 1 &&
               cross(s[cnt-1] - s[cnt-2], p[i] - s[cnt-1]) < 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    int tot = cnt;
    for (int i = n - 2; i >= 0; --i) {
        while (cnt > tot &&
               cross(s[cnt-1] - s[cnt-2], p[i] - s[cnt-1]) < 0) {
            --cnt;
        }
        s[cnt++] = p[i];
    }
    int f = 0, tmp = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i].x == 0 && s[i].y == 0) {
            f = 1;
            tmp = i;
        }
        if (f) {
            printf("(%d,%d)\n", s[i].x, s[i].y);
        }
    }
    for (int i = 0; i < tmp; ++i) {
        printf("(%d,%d)\n", s[i].x, s[i].y);
    }
    return 0;
}


// poj 1113
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 10100;
typedef struct Grid {
    int x, y;
    Grid(int a = 0, int b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point s, Point e) {
    return Vector(e.x - s.x, e.y - s.y);
}
Point p[maxn], stack[maxn];

bool cmp(Point a, Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

double dis(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main(int argc, const char * argv[]) {
    int n, l;
    scanf("%d%d", &n, &l);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &p[i].x, &p[i].y);
        }
        sort(p, p + n, cmp);
        
        int cnt = 0;
        stack[cnt++] = p[0], stack[cnt++] = p[1];
        for (int i = 2; i < n; ++i) {
            while (cnt > 1 && cross(stack[cnt-1] - stack[cnt-2], p[i] - stack[cnt-1]) >= 0) {
                --cnt;
            }
            
            stack[cnt++] = p[i];
        }
    
        int tmp = cnt;
        
        for (int i = n - 2; i >= 0; --i) {
            while (cnt > tmp && cross(stack[cnt-1] - stack[cnt-2], p[i] - stack[cnt-1]) >= 0) {
                --cnt;
            }
            stack[cnt++] = p[i];
        }
        double d = 2 * l * acos(-1);
        for (int i = 0; i < cnt - 1; ++i) {
            d += dis(stack[i], stack[i+1]);
        }
        printf("%.0f\n", d);
    
    return 0;
}

*/
