#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>
static const int MAXN = 1024;
static const double EPS = 1e-8;

template <typename T> inline T sqr(const T x) { return x * x; }
inline double dist(double x, double y) { return sqrt(x * x + y * y); }
inline double dist_sqr(double x, double y) { return x * x + y * y; }
template <typename T> inline char sign(const T x) { return x < -EPS ? -1 : (x > EPS ? 1 : 0); }

int nc, ns;
int cx[MAXN], cy[MAXN], cr[MAXN];
int sx1[MAXN], sy1[MAXN], sx2[MAXN], sy2[MAXN], sr[MAXN];

inline double angle_dist(double a, double b) {
    return std::min(fabs(a - b), 2 * M_PI - fabs(a - b));
}
// (x, y) - line sin(slope_ang) x - cos(slope_ang) y = 0
inline double dist_p2l(double x, double y, double slope_ang) {
    return fabs(sin(slope_ang) * x - cos(slope_ang) * y);
}
inline void upd_by_circle(double &ans, const double ang, const int x, const int y, const int r)
{
    static double d, l;
    if (angle_dist(atan2(y, x), ang) <= M_PI / 2 + EPS &&
        (d = dist_p2l(x, y, ang)) <= r + EPS)
    {
        l = sqrt(sqr(r) - sqr(d));
        ans = std::min(ans, sqrt(dist_sqr(x, y) - sqr(d)) - l);
    }
}
inline void upd_by_line(double &ans, const double ang,
    const double x1, const double y1, const double x2, const double y2)
{
    double seg_begin = atan2(y1, x1), seg_end = atan2(y2, x2);
    if (seg_begin < seg_end) {
        if (ang < seg_begin - EPS || ang > seg_end + EPS) return;
    } else {
        if (ang > seg_end + EPS && ang < seg_begin - EPS) return;
    }
    //printf("%.2lf - %.2lf | %.2lf\n",
    //    seg_begin / M_PI * 180, seg_end / M_PI * 180, ang / M_PI * 180);
    // Equation of line (x1,y1)-(x2,y2)
    double a = y1 - y2, b = x2 - x1, c = a * x1 + b * y1;
    double h = fabs(c) / sqrt(a * a + b * b);
    double h_ang = atan2(y1 - y2, x1 - x2) + M_PI / 2;
    double d = fabs(h / cos(h_ang - ang));
    //printf("(%.2lf,%.2lf) - (%.2lf,%.2lf) | Angle = %.3lf | Ans = %.3lf\n",
    //    x1, y1, x2, y2, ang / M_PI * 180, d);
    ans = std::min(ans, d);
}
inline double calc(double ang)
{
    double ans = 1e9;
    // Brute force
    for (int i = 0; i < nc; ++i)
        upd_by_circle(ans, ang, cx[i], cy[i], cr[i]);
    for (int i = 0; i < ns; ++i) {
        upd_by_circle(ans, ang, sx1[i], sy1[i], sr[i]);
        upd_by_circle(ans, ang, sx2[i], sy2[i], sr[i]);
        double len = dist(sx1[i] - sx2[i], sy1[i] - sy2[i]);
        upd_by_line(ans, ang,
            sx1[i] + (double)(sy1[i] - sy2[i]) * sr[i] / len,
            sy1[i] + (double)(sx2[i] - sx1[i]) * sr[i] / len,
            sx2[i] + (double)(sy1[i] - sy2[i]) * sr[i] / len,
            sy2[i] + (double)(sx2[i] - sx1[i]) * sr[i] / len);
    }
    return ans;
}

inline double area(const double lf, const double rg) {
    return (rg - lf) * sqr(calc(lf) + 4 * calc((lf + rg) / 2) + calc(rg)) / 72;
}
double simpson(const double lf, const double rg, const double eps, const double area_est) {
    double mid = (lf + rg) / 2;
    double area_lf = area(lf, mid), area_rg = area(mid, rg);
    if (fabs(area_lf + area_rg - area_est) < 15 * eps) {
        return area_lf + area_rg + (area_lf + area_rg - area_est) / 15;
    } else {
        return simpson(lf, mid, eps / 2, area_lf) + simpson(mid, rg, eps / 2, area_rg);
    }
}
inline double simpson(const double lf, const double rg, const double eps) {
    return simpson(lf, rg, eps, area(lf, rg));
}

int main()
{
    scanf("%d%d", &nc, &ns);
    for (int i = 0; i < nc; ++i)
        scanf("%d%d%d", &cx[i], &cy[i], &cr[i]);
    for (int i = 0; i < ns; ++i)
        scanf("%d%d%d%d%d", &sx1[i], &sy1[i], &sx2[i], &sy2[i], &sr[i]);

    //printf("%.12lf\n", calc(36.87 / 180 * M_PI));

    /*double a[] = {
        -180.000000,
        -138.590378,
        -129.516274,
        -121.366978,
        -56.655723 ,
        -50.700685 ,
        -41.409622 ,
        36.869898 ,
        44.012951 ,
        44.606943 ,
        59.160409 ,
        61.389540 ,
        61.927513 ,
        103.644085 ,
        118.610460 ,
        120.839591 ,
        124.817933 ,
        129.486018 ,
        144.861844 ,
        145.182067 ,
        145.973312 ,180};
    for (int i = 0; i < 21; ++i) {
        printf("%.4lf %.4lf | %.12lf\n",
            a[i], a[i + 1], simpson(a[i] / 180 * M_PI, a[i + 1] / 180 * M_PI, EPS));
    }*/
    double tot_area = simpson(-M_PI, M_PI - EPS, EPS);
    //double tot_area = simpson(-41.41 / 180 * M_PI, 36.87 / 180 * M_PI, EPS);
    printf("%.12lf\n", tot_area);

    return 0;
}
