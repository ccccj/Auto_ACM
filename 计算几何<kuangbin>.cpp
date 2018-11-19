//
//  main.cpp
//  计算几何kuangbin
//
//  Created by adm in on 18/10/23.
//  Copyright © 2018年 Amon. All rights reserved.
//
// poj 1696
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn = 100, inf = 0x3fffffff;
const double eps = 1e-8;
bool is[maxn];

typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;
Point p[maxn];

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

double dis(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double mult(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(is, 0, sizeof(is));
        int n, id, f = 0, cnt = 1;
        double Miny = inf;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &id);
            scanf("%lf%lf", &p[id].x, &p[id].y);
            if (Miny > p[id].y) {Miny = p[id].y; f = id;}
        }
        Point p1 = Point(0, p[f].y), p2 = p[f];
        printf("%d %d", n, f);
        is[f] = 1;
        Vector v1, v2;
        while (cnt < n) {
            double h = inf, tmp;
            v1 = p2 - p1;
            int flag1 = -1, flag2 = -1; // 左边
            for (int i = 1; i <= n; ++i) {
                if (is[i]) continue;
                v2 = p[i] - p2;
                tmp = fabs(cross(v1, v2)) / dis(p2, p[i]);
                
                double ddd = mult(p1 - p2, v2);
                if (ddd > 0) flag2 = 0;
                else if (fabs(ddd) < eps) flag2 = 1;
                else if (ddd < 0) flag2 = 2;
                
                if (flag1 < flag2) {
                    h = tmp, f = i, flag1 = flag2;
                } else if (flag1 == flag2) {
                    if (flag1 == 0) {
                        // h 越大越好
                        if (h < tmp) {
                            h = tmp, f = i;
                        } else if (fabs(h - tmp) < eps
                                && dis(p2, p[f]) > dis(p2, p[i])) {
                            h = tmp, f = i;
                        }
                    } else if (flag1 == 2) {
                        // h 越小越好
                        if (h > tmp) {
                            h = tmp, f = i;
                        } else if (fabs(h - tmp) < eps
                                && dis(p2, p[f]) > dis(p2, p[i])) {
                            h = tmp, f = i;
                        }
                    }
                }
            }
            p1 = p2;
            p2 = p[f];
            printf(" %d", f);
            is[f] = 1;
            ++cnt;
        }
        printf("\n");
    }
    return 0;
}

/*
// poj 1584
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const double eps = 1e-8;
int n;
double dx, dy, dr;
typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a, e = b;}
} line[maxn];

Point p[maxn];

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool is_formed() {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; ++i) {
        double k = cross(line[i].e-line[i].s, line[(i+1)%n].e-line[(i+1)%n].s);
        if (k < -eps) {
            ++cnt1;
        } else if (k > eps) {
            ++cnt2;
        } else {
            ++cnt1, ++cnt2;
        }
    }
    // 不相交
    return cnt1 == n || cnt2 == n;
}

double ddd(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double mult(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double dis(Line a) {
    Point tmp = Point(dx, dy);
    Vector x1 = a.s - tmp, y1 = a.e - tmp;
    Vector x2 = a.e - a.s, y2 = a.s - a.e;
    if (mult(x1, x2) * mult(y1, y2) > 0) {
        // 在里面
        double ans = fabs(cross(x1, y1)) / ddd(a.e, a.s);
        return ans;
    }
    double Min = min(ddd(a.s, tmp), ddd(a.e, tmp));
    return Min;
}

bool inside() {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; ++i) {
        Vector a(line[i].s - Point(dx, dy)), b = line[i].e - line[i].s;
        if (cross(a, b) > eps) {
            ++cnt1;
        } else if (cross(a, b) < -eps) {
            ++cnt2;
        }
    }
    return cnt1 == n || cnt2 == n;
}

bool is_fit() {
    if (inside() == 0) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (dis(line[i]) < dr) {
            return 0;
        }
    }
    return 1;
}

int main() {
    while (~scanf("%d", &n) && n >= 3) {
        scanf("%lf%lf%lf", &dr, &dx, &dy);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            if (i > 0) line[i] = Line(p[i-1], p[i]);
        }
        line[0] = Line(p[n-1], p[0]);
        if (is_formed() == 0) {
            printf("HOLE IS ILL-FORMED\n");
        } else {
            if (is_fit()) {
                printf("PEG WILL FIT\n");
            } else {
                printf("PEG WILL NOT FIT\n");
            }
        }
    }
    return 0;
}


// poj 3449
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1050;
const double eps = 1e-8;
typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Vector, Point;

Vector operator - (Point a, Point b) {
    return Vector(b.x - a.x, b.y - a.y);
}

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a, e = b;}
    Line(double x1, double y1, double x2, double y2) {
        s.x = x1, s.y = y1, e.x = x2, e.y = y2;
    }
};

struct Inf {
    int id, num;
    char name[10];
    Line line[50];
} inf[maxn];

char tmp[20];

Point get_point() {
    scanf("%s", tmp);
    int cnt = 1;
    int f1 = 1, f2 = 1;
    if (tmp[1] == '-') {
        f1 = -1;
        ++cnt;
    }
    int a = 0, b = 0;
    while (tmp[cnt] != ',') {
        a = a * 10 + tmp[cnt] - '0';
        ++cnt;
    }
    ++cnt;
    if (tmp[cnt] == '-') {
        f2 = -1;
        ++cnt;
    }
    while (tmp[cnt] != ')') {
        b = b * 10 + tmp[cnt] - '0';
        ++cnt;
    }
    //printf("%d %d\n", f1 * a, f2 * b);
    return Point(f1 * a, f2 * b);
}

void square(int i) {
    Point s, e, t1, t2;
    s = get_point();
    e = get_point();
    inf[i].num = 4;
    t1 = Point((s.x + e.x + e.y - s.y)/2, (s.y + e.y + s.x - e.x)/2);
    t2 = Point((s.x + e.x + s.y - e.y)/2, (s.y + e.y - s.x + e.x)/2);
    inf[i].line[0] = Line(s, t1);
    inf[i].line[1] = Line(t1, e);
    inf[i].line[2] = Line(e, t2);
    inf[i].line[3] = Line(t2, s);
}

void rectangle(int i) {
    Point p1, p2, p3, p4;
    p1 = get_point();
    p2 = get_point();
    p3 = get_point();
    inf[i].num = 4;
    inf[i].line[0] = Line(p1, p2);
    inf[i].line[1] = Line(p2, p3);
    p4.x = p3.x + p1.x - p2.x, p4.y = p3.y + p1.y - p2.y;
    inf[i].line[2] = Line(p3, p4);
    inf[i].line[3] = Line(p4, p1);
}

void line(int i) {
    Point s, e;
    s = get_point();
    e = get_point();
    inf[i].num = 1;
    inf[i].line[0] = Line(s, e);
}

void triangle(int i) {
    Point p1, p2, p3;
    p1 = get_point();
    p2 = get_point();
    p3 = get_point();
    inf[i].num = 3;
    inf[i].line[0] = Line(p1, p2);
    inf[i].line[1] = Line(p2, p3);
    inf[i].line[2] = Line(p1, p3);
}

void polygon(int i) {
    int n;
    scanf("%d", &n);
    Point last = get_point();
    Point first = last, now;
    for (int j = 1; j < n; ++j) {
        now = get_point();
        inf[i].line[j - 1] = Line(last, now);
        last = now;
    }
    inf[i].line[n-1] = Line(first, now);
    inf[i].num = n;
}

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool inter(Line a, Line b) {
    Vector v1 = a.e - a.s, x1 = b.s - a.s, x2 = b.e - a.s;
    Vector v2 = b.e - b.s, x3 = a.s - b.s, x4 = a.e - b.s;
    double d1 = cross(v1, x1), d2 = cross(v1, x2);
    double d3 = cross(v2, x3), d4 = cross(v2, x4);
    
    return min(a.s.x, a.e.x) <= max(b.s.x, b.e.x)
        && min(b.s.x, b.e.x) <= max(a.s.x, a.e.x)
        && min(a.s.y, a.e.y) <= max(b.s.y, b.e.y)
        && min(b.s.y, b.e.y) <= max(a.s.y, a.e.y)
        && d1 * d2 < eps && d3 * d4 < eps;
}

bool judge(int a, int b) {
    for (int i = 0; i < inf[a].num; ++i) {
        for (int j = 0; j < inf[b].num; ++j) {
            if (inter(inf[a].line[i], inf[b].line[j])) {
                return 1;
            }
        }
    }
    // 1 相交
    return 0;
}

bool cmp(struct Inf a, struct Inf b) {
    return a.name[0] < b.name[0];
}

int main() {
    while (~scanf("%s", inf[0].name) && inf[0].name[0] != '.') {
        int cnt = 0;
        for (int i = 0; ; ++i, ++cnt) {
            if (i != 0) scanf("%s", inf[i].name);

            if (inf[i].name[0] == '-') break;

            scanf("%s", tmp);
            if (tmp[0] == 's') square(i);
            else if (tmp[0] == 'r') rectangle(i);
            else if (tmp[0] == 'l') line(i);
            else if (tmp[0] == 't') triangle(i);
            else if (tmp[0] == 'p') polygon(i);
        }
        sort(inf, inf + cnt, cmp);
        vector<int> v[30];
        for (int i = 0; i < cnt; ++i) {
            for (int j = i + 1; j < cnt; ++j) {
                if (i == j) continue;
                if (judge(i, j)) {
                    v[i].push_back(j);
                    v[j].push_back(i);
                }
            }
        }
        for (int i = 0; i < cnt; ++i) {
            if (v[i].size() == 0) {
                printf("%s has no intersections\n", inf[i].name);
            } else {
                int len = (int)v[i].size();
                if (len == 1) {
                    printf("%s intersects with %s\n", inf[i].name, inf[v[i][0]].name);
                } else if (len == 2) {
                    printf("%s intersects with %s and %s\n", inf[i].name, inf[v[i][0]].name, inf[v[i][1]].name);
                } else {
                    printf("%s intersects with", inf[i].name);
                    for (int j = 0; j < len; ++j) {
                        if (j == len - 1) {
                            printf(" and %s\n", inf[v[i][j]].name);
                        } else {
                            printf(" %s,", inf[v[i][j]].name);
                        }
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}


// 1039
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10100;
const double eps = 1e-8;
int n, cnt;
int Max;
typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a; y = b;}
} Point, Vector;

Point up[maxn], down[maxn];

Point operator - (Point a, Point b) {
    Point ans;
    ans.x = b.x - a.x, ans.y = b.y - a.y;
    return ans;
}

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a; e = b;}
} line[maxn], stri[maxn];

double operator ^ (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge(Line a, Line b) {
    Vector v1 = a.e - a.s, x1 = b.s - a.s, x2 = b.e - a.s;
    return (v1 ^ x1) * (v1 ^ x2) < eps;
}

double get_point(Line a, Line b) {
    double a1 = a.s.y - a.e.y, b1 = a.e.x - a.s.x;
    double c1 = a.s.x * a.e.y - a.e.x * a.s.y;
    double a2 = b.s.y - b.e.y, b2 = b.e.x - b.s.x;
    double c2 = b.s.x * b.e.y - b.e.x * b.s.y;
    return (c1 * b2 - c2 * b1) / (a2 * b1 - a1 * b2);
}

int find_first(Line a) {
    for (int i = 0; i < n; ++i) {
        if (judge(a, stri[i]) == 0) {
            return i - 1;
        }
    }
    return n - 1;
}

int main() {
    while (~scanf("%d", &n) && n) {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf", &up[i].x, &up[i].y);
        }
        for (int i = 0; i < n; ++i) {
            down[i] = Point(up[i].x, up[i].y - 1);
            stri[i] = Line(up[i], down[i]);
        }
        for (int i = 1; i < n; ++i) {
            line[cnt++] = Line(up[i-1], up[i]);
            line[cnt++] = Line(down[i-1], down[i]);
        }
        Line l;
        double ret = up[1].x;
        Max = 0;
        for (int i = 0; i < n && Max != n - 1; ++i) {
            for (int j = 0; j < n && Max != n - 1; ++j) {
                if (i == j) continue;
                l = Line(up[i], down[j]);
                int ans = find_first(l);
                double ttt = -0x3fffffff;
                if (judge(l, line[2 * ans])) {
                    ttt = get_point(l, line[2*ans]);
                }
                if (judge(l, line[2 * ans+1])) {
                    ttt = max(ttt, get_point(l, line[2*ans+1]));
                }
                ret = max(ret, ttt);
                Max = max(Max, ans);
            }
        }
        
        if (Max == n - 1) {
            printf("Through all the pipe.\n");
        } else {
            printf("%.2lf\n", ret);
        }
    }
    return 0;
}


// poj 3347
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1100;
const double eps = 1e-8;
int len[maxn], n, cnt;
double left[maxn], right[maxn], x[maxn];
bool is[maxn];

typedef struct Grid {
    double x, y;
    Grid(double a = 0, double b = 0) {x = a, y = b;}
} Point, Vector;

Vector operator - (Point a, Point b) {
    Vector ans;
    ans.x = b.x - a.x, ans.y = b.y - a.y;
    return ans;
}

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a, e = b;}
} line[maxn];

double operator ^ (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool on_segment(Point pi, Point pj, Point pk) {
    if (fabs((pj - pi) ^ (pk - pi)) < eps) {
        if (pk.x > min(pi.x, pj.x) - eps && pk.x < max(pi.x, pj.x) + eps
            && pk.y > min(pi.y, pj.y) - eps && pk.y < max(pi.y,pj.y) + eps)
            return 1;
    }
    return 0;
}

bool inter(Line a, Line b) {
    Vector v1 = a.e - a.s, x1 = b.s - a.s, x2 = b.e - a.s;
    Vector v2 = b.e - b.s, x3 = a.s - b.s, x4 = a.e - b.s;
    double d1 = v1 ^ x1, d2 = v1 ^ x2, d3 = v2 ^ x3, d4 = v2 ^ x4;
    //printf("%lf %lf, %lf %lf\n", d1, d2, d3, d4);
    if (d1 < eps && on_segment(a.s, a.e, b.s)) return 0;
    else if (d2 < eps && on_segment(a.s, a.e, b.e)) return 0;
    else if (d3 < eps && on_segment(b.s, b.e, a.s)) return 0;
    else if (d4 < eps && on_segment(b.s, b.e, a.e)) return 0;
    if (d1 * d2 < 0 && d3 * d4 < 0) {
        // 相交
        return 1;
    }
    return 0;
}

bool judge(int now) {
    Point s, e;
    s.x = x[now], s.y = 0;
    e.x = x[now] - len[now], e.y = len[now];
    Line test(s, e);
    int f = 1; // 没相交
    for (int i = now - 1; f && i >= 0; --i) {
        if (inter(test, line[4*i]) || inter(test, line[4*i+1])
            || inter(test, line[4*i+2]) || inter(test, line[4*i+3])) {
            f = 0;
        }
    }
    s.y += len[now] * 2;
    test.s = s;
    for (int i = now - 1; f && i >= 0; --i) {
        if (inter(test, line[4*i]) || inter(test, line[4*i+1])
            || inter(test, line[4*i+2]) || inter(test, line[4*i+3])) {
            f = 0;
        }
    }
    e.x += len[now] * 2;
    test.e = e;
    for (int i = now - 1; f && i >= 0; --i) {
        if (inter(test, line[4*i]) || inter(test, line[4*i+1])
            || inter(test, line[4*i+2]) || inter(test, line[4*i+3])) {
            f = 0;
        }
    }
    s.y -= len[now] * 2;
    test.s = s;
    for (int i = now - 1; f && i >= 0; --i) {
        if (inter(test, line[4*i]) || inter(test, line[4*i+1])
            || inter(test, line[4*i+2]) || inter(test, line[4*i+3])) {
            f = 0;
        }
    }
    return f;
}

void getx(int now) {
    for (int i = now - 1; i >= 0; --i) {
        if (len[now] < len[i]) {
            // 下
            x[now] = x[i] + 2 * len[now];
        } else {
            // 上
            x[now] = x[i] + 2 * len[i];
        }
        // 没有相交
        if (judge(now)) break;
    }
}

int main() {
//    printf("%lf\n", 3 / sqrt(2));
    while (~scanf("%d", &n) && n) {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &len[i]);
            if (i == 0) x[i] = len[i];
            else getx(i);
            
            Point s, e;
            s.x = x[i], s.y = 0;
            e.x = x[i] - len[i], e.y = len[i];
            left[i] = e.x;
            Line test(s, e);
            line[4*i] = test; // 1
            s.y += len[i] * 2;
            test.s = s;
            line[4*i+1] = test; // 2
            e.x += len[i] * 2;
            right[i] = e.x;
            test.e = e;
            line[4*i+2] = test; // 3
            s.y -= len[i] * 2;
            test.s = s;
            line[4*i+3] = test; // 4
            
            //printf("%d  %.3lf l: %.3lf r: %.3lf\n", i, x[i], left[i], right[i]);
        }
        for (int i = 0; i < n; ++i) {
            double l = left[i], r = right[i];
            for (int j = 0; j < n && l < r; ++j) {
                //printf("===");
                if (i == j) continue;
                if (left[j] <= l && right[j] >= l) {
                    l = right[j];
                } else if (left[j] >= l) {
                    r = left[j];
                }
            }
            is[i] = (l < r);
        }
        int f = 0;
        for (int i = 0; i < n; ++i) {
            if (is[i]) {
                if (f != 0) printf(" %d", i + 1);
                else {printf("%d", i + 1), f = 1;}
            }
        }
        printf("\n");
    }
    return 0;
}


// poj 2826
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const double eps = 1e-8;

struct Vector {
    double x, y;
};

struct Point {
    double x, y;
    Point(double x1 = 0, double y1 = 0) {x = x1, y = y1;}
    Vector operator - (Point a) {
        Vector ans;
        ans.x = x - a.x, ans.y = y - a.y;
        return ans;
    }
    bool operator==(Point a) {return x == a.x && y == a.y;}
};

struct Line {
    Point s, e;
    Line() {}
    Line(Point a, Point b) {s = a, e = b;}
} a, b;


double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge(Line a, Line b) {
    Vector v1 = a.e - a.s, x1 = b.s - a.s, x2 = b.e - a.s;
    Vector v2 = b.e - b.s, x3 = a.s - b.s, x4 = a.e - b.s;
    
    // 相交
    return min(a.s.x, a.e.x) <= max(b.s.x, b.e.x)
        && min(a.s.y, a.e.y) <= max(b.s.y, b.e.y)
        && min(b.s.x, b.e.x) <= max(a.s.x, a.e.x)
        && min(b.s.y, b.e.y) <= max(a.s.y, a.e.y)
        && cross(v1, x1) * cross(v1, x2) < eps
        && cross(v2, x3) * cross(v2, x4) < eps;
}

Point get_point() {
    Point ans = a.s;
    Vector v1 = a.s - b.s, v2 = b.s - b.e;
    Vector v3 = a.s - a.e, v4 = b.s - b.e;
    double t = cross(v1, v2) / cross(v3, v4);
    ans.x += t * (a.e.x - a.s.x);
    ans.y += t * (a.e.y - a.s.y);
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lf%lf%lf%lf", &a.s.x, &a.s.y, &a.e.x, &a.e.y);
        scanf("%lf%lf%lf%lf", &b.s.x, &b.s.y, &b.e.x, &b.e.y);
        if (fabs(a.s.y - a.e.y) < eps || fabs(b.s.y - b.e.y) < eps
            || judge(a, b) == 0) {
            // 有一根平放 或 无交点
            printf("0.00\n");
            continue;
        }
        if (a.s.y > a.e.y) swap(a.s, a.e);
        if (b.s.y > b.e.y) swap(b.s, b.e);
        
        Point ins, e1, e2;
        ins = get_point();
        
        double s = 0;
        Point Min = a.e, Max = b.e;
        if (a.e.y > b.e.y) {
            swap(Min, Max);
            // b 低
            double t = (Min.y - a.s.y) / (Max.y - a.s.y);
            e1.x = t * (a.e.x - a.s.x) + a.s.x;
            e1.y = Min.y;
            e2 = Min;
            Point te(Min.x, 1000000);
            Line test(Min, te);
            if (judge(a, test)) {
                printf("0.00\n");
                continue;
            }
        } else {
            // a 低
            double t = (Min.y - b.s.y) / (Max.y - b.s.y);
            e1.x = t * (b.e.x - b.s.x) + b.s.x;
            e1.y = Min.y;
            e2 = Min;
            Point te(Min.x, 1000000);
            Line test(Min, te);
            if (judge(b, test)) {
                printf("0.00\n");
                continue;
            }
        }
        
        
        
        Vector v1 = e1 - ins, v2 = e2 - ins;
        s = cross(v1, v2) / 2;
        
        printf("%.2lf\n", fabs(s));
    }
    return 0;
}


// poj 1410
#include <cstdio>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
struct Line {
    double x1, y1, x2, y2;
} k;

struct Vector {
    double x, y;
};

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge(Line a, Line b) {
    Vector v1, v2, x1, x2, x3, x4;
    v1.x = a.x2 - a.x1, v1.y = a.y2 - a.y1;
    v2.x = b.x2 - b.x1, v2.y = b.y2 - b.y1;
    x1.x = b.x1 - a.x1, x1.y = b.y1 - a.y1;
    x2.x = b.x2 - a.x1, x2.y = b.y2 - a.y1;
    x3.x = a.x1 - b.x1, x3.y = a.y1 - b.y1;
    x4.x = a.x2 - b.x1, x4.y = a.y2 - b.y1;
    return max(a.x1, a.x2) >= min(b.x1, b.x2)
        && max(a.y1, a.y2) >= min(b.y1, b.y2)
        && max(b.x1, b.x2) >= min(a.x1, a.x2)
        && max(b.y1, b.y2) >= min(a.y1, a.y2)
        && cross(v1, x1) * cross(v1, x2) < eps
        && cross(v2, x3) * cross(v2, x4) < eps;
}

int main() {
    int n;
    double x1, y1, x2, y2;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf%lf", &k.x1, &k.y1, &k.x2, &k.y2);
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 < y2) {
            swap(y1, y2);
        }
        int f = 1;
        Line b;
        b.x1 = x1, b.y1 = y1, b.x2 = x2, b.y2 = y1;
        if (f && judge(k, b))
            f = 0;
        
        b.x1 = x1, b.y1 = y1, b.x2 = x1, b.y2 = y2;
        if (f && judge(k, b))
            f = 0;
        
        b.x1 = x2, b.y1 = y1, b.x2 = x2, b.y2 = y2;
        if (f && judge(k, b))
            f = 0;
        
        b.x1 = x1, b.y1 = y2, b.x2 = x2, b.y2 = y2;
        if (f && judge(k, b))
            f = 0;
        
        if (f) {
            if (k.x1 >= x1 && k.x1 <= x2
                && k.y1 <= y1 && k.y1 >= y2
                && k.x2 >= x1 && k.x2 <= x2
                && k.y2 <= y1 && k.y2 >= y2) {
                f = 0;
            }
        }
        
        
        if (f == 0) {
            printf("T\n");
        } else {
            printf("F\n");
        }
    }
    return 0;
}


// poj 1066
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 110, inf = 0x3fffffff;
const double eps = 1e-8;
int Min;
int n;
struct Point {
    double x, y;
} s, e;

struct Line {
    double x1, y1, x2, y2;
    Line(Point a = s, Point b = e) {
        x1 = a.x, y1 = a.y;
        x2 = b.x, y2 = b.y;
    }
} line[maxn];

struct Vector {
    double x, y;
};

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge(Line a, Line b) {
    Vector v1, v2, x1, x2, x3, x4;
    v1.x = a.x2 - a.x1, v1.y = a.y2 - a.y1;
    v2.x = b.x2 - b.x1, v2.y = b.y2 - b.y1;
    x1.x = b.x1 - a.x1, x1.y = b.y1 - a.y1;
    x2.x = b.x2 - a.x1, x2.y = b.y2 - a.y1;
    x3.x = a.x1 - b.x1, x3.y = a.y1 - b.y1;
    x4.x = a.x2 - b.x1, x4.y = a.y2 - b.y1;
    double ans1 = cross(v1, x1) * cross(v1, x2);
    double ans2 = cross(v2, x3) * cross(v2, x4);
    return ans1 <= eps && ans2 <= eps;
}

void slove() {
    int num = 0;
    for (int i = 0; i < n; ++i) {
        num = 0;
        e.x = line[i].x1, e.y = line[i].y1;
        Line t1(s, e);
        for (int j = 0; j < n; ++j) {
            Line t2;
            t2.x1 = line[j].x1, t2.y1 = line[j].y1;
            t2.x2 = line[j].x2, t2.y2 = line[j].y2;
            if (judge(t1, t2)) {
                ++num;
            }
        }
        Min = min(Min, num);
        num = 0;
        t1.x2 = line[i].x2, t1.y2 = line[i].y2;
        for (int j = 0; j < n; ++j) {
            if (judge(t1, line[j])) {
                ++num;
            }
        }
        Min = min(Min, num);
    }
}

int main() {
    
    while (~scanf("%d", &n)) {
        Min = inf;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &line[i].x1, &line[i].y1,
                  &line[i].x2, &line[i].y2);
        }
        scanf("%lf%lf", &s.x, &s.y);
        if (n == 0) {
            printf("Number of doors = 1\n");
            continue;
        }
        slove();
        printf("Number of doors = %d\n", Min);
    }
    return 0;
}


// poj 2653
#include <cstdio>
using namespace std;
const int maxn = 100010;

struct Line {
    double x1, y1, x2, y2;
} line[maxn];

struct Vector {
    double x, y;
};

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool judge(Line a, Line b) {
    Vector v1, v2, x1, x2, x3, x4;
    v1.x = a.x2 - a.x1, v1.y = a.y2 - a.y1;
    v2.x = b.x2 - b.x1, v2.y = b.y2 - b.y1;
    
    x1.x = b.x1 - a.x1, x1.y = b.y1 - a.y1;
    x2.x = b.x2 - a.x1, x2.y = b.y2 - a.y1;
    x3.x = a.x1 - b.x1, x3.y = a.y1 - b.y1;
    x4.x = a.x2 - b.x1, x4.y = a.y2 - b.y1;
    if (cross(v1, x1) * cross(v1, x2) < 0
        && cross(v2, x3) * cross(v2, x4) < 0) {
        return 1;
    }
    return 0; // i 线段 和 j 线段相交
}

int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        printf("Top sticks: ");
        for (int i = 1; i <= n; ++i) {
            scanf("%lf%lf%lf%lf", &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);
        }
        for (int i = 1; i < n; ++i) {
            int f = 0;
            for (int j = i + 1; j <= n; ++j) {
                if (judge(line[i], line[j])) {
                    f = 1;
                    break;
                }
            }
            if (f == 0) {
                printf("%d, ", i);
            }
        }
        printf("%d.\n", n);
    }
    return 0;
}


// poj 1556
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 10010, inf = 0x3fffffff;
int num, cnt, head[maxn], n, s, e, vis[maxn], doornum;
double Dis[maxn];

struct Point {
    double x, y;
    int id;
} point[maxn];

struct Vector {
    double x, y;
};

struct Line {
    double x1, y1, x2, y2;
};

struct Door {
    double x, y1, y2;
} door[maxn];//THREE LINE

struct Edge {
    int to, next;
    double d;
} edge[maxn];

double dis(Point a, Point b) {
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

void insert(int i, int j) {
    edge[++cnt].to = j, edge[cnt].d = dis(point[i], point[j]), edge[cnt].next = head[i];
    head[i] = cnt;
}

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool is(Line a, Line b) {
    Vector x1, y1, x2, y2;
    Vector v1, v2;
    
    v1.x = a.x2 - a.x1, v1.y = a.y2 - a.y1;
    v2.x = b.x2 - b.x1, v2.y = b.y2 - b.y1;
    
    x1.x = b.x1 - a.x1, x1.y = b.y1 - a.y1;
    y1.x = b.x2 - a.x1, y1.y = b.y2 - a.y1;
    x2.x = a.x1 - b.x1, x2.y = a.y1 - b.y1;
    y2.x = a.x2 - b.x1, x2.y = a.y2 - b.y1;
    
    if(cross(v1, x1) * cross(v1, y1) < 0 && cross(v2, x2) * cross(v2, y2) < 0) {
        //printf("---");
        return true;
    }
    return false;
}

bool judge(int i, int j) {
    // JUDGE BETWEEN THE I-TH AND J-TH POINT;
    Line x, y;
    x.x1 = point[i].x, x.y1 = point[i].y;
    x.x2 = point[j].x, x.y2 = point[j].y;
    // X-SEGMENT CONNECT THE I-TH AND THE J-TH POINT;
    for (int k = 0; k < doornum; ++k) {
        if (k == point[i].id || k == point[j].id) continue;
        
        //TO ENUM ALL LINE.
        y.x1 = y.x2 = door[k].x;
        y.y1 = door[k].y1, y.y2 = door[k].y2;
        if (is(x, y)) return 0;
    }
    return 1;
}

double spfa(int s, int e) {
    fill(Dis, Dis + maxn, inf);
    memset(vis, 0, sizeof(vis));
    Dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = edge[i].next) {
            int to = edge[i].to;
            if (Dis[to] > Dis[now] + edge[i].d) {
                Dis[to] = Dis[now] + edge[i].d;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    return Dis[e];
}

int main() {
    point[s].x = 0, point[s].y = 5;
    while (~scanf("%d", &n) && n != -1) {
        memset(head, 0, sizeof(head));
        e = 4 * n + 1; // E IS THE NUMBER OF LINE
        point[e].x = 10, point[e].y = 5;
        doornum = cnt = 0, num = 1;
        // CNT IS THE ID OF EDGES; NUM: POINT
        double x, y1, y2, y3, y4;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf%lf", &x, &y1, &y2, &y3, &y4);
            // DOOR ARRAY SAVE THE Y-INFORMATION OF X-COORDINATE;
            //FIRST
            point[num].id = doornum;
            door[doornum].x = point[num].x = x;
            door[doornum].y1 = point[num++].y = y1;
            door[doornum++].y2 = 0;
            //SECOND
            point[num].id = doornum;
            door[doornum].x = point[num].x = x;
            door[doornum].y1 = point[num++].y = y2;
            
            point[num].id = doornum;
            point[num].x = x;
            door[doornum++].y2 = point[num++].y = y3;
            //THIRD
            point[num].id = doornum;
            door[doornum].x = point[num].x = x;
            door[doornum].y1 = point[num++].y = y4;
            door[doornum++].y2 = 10;
        }
        
        for (int i = 0; i < e; ++i) {
            //CONNECT THE EDGE TO THE END-POINT;
            for (int j = i + 1; j <= e; ++j) {
                if (judge(i, j)) {
                    insert(i, j);
                }
            }
        }
        printf("%.2lf\n", spfa(s, e));
    }
    return 0;
}


// poj 3304
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const double eps = 1e-8;
int t, n;
struct Line {
    double x1, y1, x2, y2;
} line[maxn];

struct Vector {
    double x, y;
};

double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool judge(int now1, int now2, double x1, double y1, double x2, double y2) {
    if (dis(x1, y1, x2, y2) < eps) return 0;
    for (int i = 0; i < n; ++i) {
        if (i == now1 || i == now2) continue;
        Vector a, b, c, d;
        a.x = x1 - line[i].x1, a.y = y1 - line[i].y1;
        b.x = x2 - line[i].x1, b.y = y2 - line[i].y1;
        c.x = x1 - line[i].x2, c.y = y1 - line[i].y2;
        d.x = x2 - line[i].x2, d.y = y2 - line[i].y2;
        if (cross(a, b) * cross(c, d) > 0) {
            // 不相交
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf",
                  &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);
        }
        int f = 0;
        for (int i = 0; i < n && !f; ++i) {
            if (judge(i, i, line[i].x1, line[i].y1, line[i].x2, line[i].y2)) {
                f = 1;
            }
            for (int j = i + 1; j < n && !f; ++j) {
                if (judge(i, j, line[i].x1, line[i].y1, line[j].x1, line[j].y1)
                    || judge(i, j, line[i].x1, line[i].y1, line[j].x2, line[j].y2)
                    || judge(i, j, line[i].x2, line[i].y2, line[j].x1, line[j].y1)
                    || judge(i, j, line[i].x2, line[i].y2, line[j].x2, line[j].y2)) {
                    f = 1;
                }
            }
        }
        if (f == 0) {
            printf("No!\n");
        } else {
            printf("Yes!\n");
        }
    }
    return 0;
}


// poj 1269
#include <cstdio>
#include <cmath>
using namespace std;
const double eps = 1e-4;
double x11, y11, x12, y12, x21, y21, x22, y22;

void judge() {
    if (fabs(x12 - x11) < eps && fabs(x21 - x22) < eps) {
        if (fabs(x11 - x22) < eps) {
            printf("LINE\n");
        } else {
            printf("NONE\n");
        }
    } else if (fabs(x12 - x11) < eps) {
        double k2 = (y22-y21)/(x22-x21);
        double b2 = y22 - k2 * x22;
        printf("POINT %.2lf %.2lf\n", x12, k2 * x12 + b2);
    } else if (fabs(x21 - x22) < eps) {
        double k1 = (y12-y11)/(x12-x11);
        double b1 = y12 - k1 * x12;
        printf("POINT %.2lf %.2lf\n", x22, k1 * x22 + b1);
    } else {
        double k1 = (y12-y11)/(x12-x11), k2 = (y22-y21)/(x22-x21);
        double b1 = y12 - k1 * x12, b2 = y22 - k2 * x22;
        if (fabs(k1 - k2) < eps) {
            if (fabs(b1 - b2) < eps) {
                printf("LINE\n");
            } else {
                printf("NONE\n");
            }
        } else {
            double x = (b2 - b1) / (k1 - k2);
            printf("POINT %.2lf %.2lf\n", x, k1 * x + b1);
        }
    }
}

int main() {
    
    int n;
    scanf("%d", &n);
    printf("INTERSECTING LINES OUTPUT\n");
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",
              &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22);
        judge();
    }
    printf("END OF OUTPUT\n");
    return 0;
}


// poj 2398
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1100;
int num[maxn], box[maxn], n, m;
double x1, y1, x2, y2;

struct Line {
    double x1, x2;
} line[maxn];

int judge(double x, double y) {
    int left = 0, right = n + 1, mid = 0;
    while (left < right - 1) {
        mid = (left + right) / 2;
        int a = line[mid].x1, b = line[mid].x2;
        if ((y1 + (y2-y1) * (x-a) / (b-a) < y && (y2-y1)/(b-a) < 0)
            || (y1 + (y2-y1) * (x-a) / (b-a) > y && (y2-y1)/(b-a) > 0)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    int a = line[mid].x1, b = line[mid].x2;
    if ((y1 + (y2-y1) * (x-a) / (b-a) < y && (y2-y1)/(b-a) < 0)
        || (y1 + (y2-y1) * (x-a) / (b-a) > y && (y2-y1)/(b-a) > 0))  {
        return mid;
    } else {
        return left;
    }
}

bool cmp(Line a, Line b) {
    return a.x1 < b.x1;
}

int main(int argc, const char * argv[]) {
    while (~scanf("%d", &n) && n) {
        scanf("%d%lf%lf%lf%lf", &m, &x1, &y1, &x2, &y2);
        line[0].x1 = line[0].x2 = x1;
        line[n + 1].x1 = line[n + 1].x1 = x2;
        
        memset(num, 0, sizeof(num));
        memset(box, 0, sizeof(box));
        for (int i = 1; i <= n; ++i) {
            scanf("%lf%lf", &line[i].x1, &line[i].x2);
        }
        sort(line + 1, line + n + 1, cmp);
        double x, y;
        for (int i = 0; i < m; ++i) {
            scanf("%lf%lf", &x, &y);
            if (x < x1 || x > x2 || y < y2 || y > y1) {
                continue;
            }
            int ans = judge(x, y);
            ++num[ans];
        }
        printf("Box\n");
        for (int i = 0; i <= n; ++i) {
            if (num[i]) {
                ++box[num[i]];
            }
        }
        for (int i = 1; i < maxn; ++i) {
            if (box[i]) {
                printf("%d: %d\n", i, box[i]);
            }
        }
    }
    return 0;
}


// poj 2318
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 5100;
int num[maxn], n, m;
double x1, y1, x2, y2;

struct Line {
    double x1, x2;
} line[maxn];

int judge(double x, double y) {
    int left = 0, right = n + 1, mid = 0;
    while (left < right - 1) {
        mid = (left + right) / 2;
        int a = line[mid].x1, b = line[mid].x2;
        if ((y1 + (y2-y1) * (x-a) / (b-a) < y && (y2-y1)/(b-a) < 0)
            || (y1 + (y2-y1) * (x-a) / (b-a) > y && (y2-y1)/(b-a) > 0)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    int a = line[mid].x1, b = line[mid].x2;
    if ((y1 + (y2-y1) * (x-a) / (b-a) < y && (y2-y1)/(b-a) < 0)
        || (y1 + (y2-y1) * (x-a) / (b-a) > y && (y2-y1)/(b-a) > 0))  {
        return mid;
    } else {
        return left;
    }
}

int main(int argc, const char * argv[]) {
    while (~scanf("%d", &n) && n) {
        scanf("%d%lf%lf%lf%lf", &m, &x1, &y1, &x2, &y2);
        line[0].x1 = line[0].x2 = x1;
        line[n + 1].x1 = line[n + 1].x1 = x2;
        
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= n; ++i) {
            scanf("%lf%lf", &line[i].x1, &line[i].x2);
        }
        double x, y;
        for (int i = 0; i < m; ++i) {
            scanf("%lf%lf", &x, &y);
            int ans = judge(x, y);
            ++num[ans];
        }
        for (int i = 0; i <= n; ++i) {
            printf("%d: %d\n", i, num[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
