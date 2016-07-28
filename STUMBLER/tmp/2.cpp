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
inline double calc(double ang)
{
    double ans = 1e9;
    // Brute force
    double d, l;
    for (int i = 0; i < nc; ++i) {
        if (angle_dist(atan2(cy[i], cx[i]), ang) <= M_PI / 2 + EPS && (d = dist_p2l(cx[i], cy[i], ang)) <= cr[i] + EPS) {
            l = sqrt(sqr(cr[i]) - sqr(d));
            ans = std::min(ans, sqrt(dist_sqr(cx[i], cy[i]) - sqr(d)) - l);
            //printf("> (%d,%d)R=%d | %.4lf\n", cx[i], cy[i], cr[i], sqrt(dist_sqr(cx[i], cy[i]) - sqr(d)) - l);
        }
        //printf("> (%d,%d)R=%d | %d | D=%.4lf\n", cx[i], cy[i], cr[i], cx[i] * sign(ang) >= 0, dist_p2l(cx[i], cy[i], ang));
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

    printf("%.12lf\n", calc(-60.0 / 180 * M_PI));
    //return 0;
    double a[18] = {
        -180.000000,
        -138.406857,
        -138.189685,
        -137.349826,
        -115.332939,
        -67.906346 ,
        -65.270039 ,
        -48.590378 ,
        -41.018298 ,
        22.232277 ,
        48.590378 ,
        60.000000 ,
        61.034802 ,
        116.683269 ,
        120.000000 ,
        138.189685 ,
        153.316731 , 180};
    for (int i = 0; i < 17; ++i) {
        double tot_area = simpson(a[i] / 180 * M_PI, a[i + 1] / 180 * M_PI, EPS);
        printf("%.2lf %.2lf %.12lf\n", a[i], a[i + 1], tot_area);
    }
    double tot_area = simpson(-M_PI, M_PI - EPS, EPS);
    printf("%.12lf\n", tot_area);

    return 0;
}

