#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>
static const int MAXN = 1024;
static const double EPS = 1e-6;

template <typename T> inline T sqr(const T x) { return x * x; }
inline double dist(double x, double y) { return sqrt(x * x + y * y); }

template <typename T> int* discretize(int n, T *a)
{
    static std::pair<T, int> p[MAXN * 4];
    for (int i = 0; i < n; ++i) {
        p[i].first = a[i]; p[i].second = i;
    }
    std::sort(p, p + n);
    int *ret = new int[n]();
    int rk = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || p[i].first != p[i - 1].first) {
            a[rk] = p[i].first;
            ret[p[i].second] = rk++;
        } else {
            ret[p[i].second] = rk;
        }
    }
    return ret;
}

int nc, ns;
int cx[MAXN], cy[MAXN], cr[MAXN];
int sx1[MAXN], sy1[MAXN], sx2[MAXN], sy2[MAXN], sr[MAXN];
double cd[MAXN], sd1[MAXN], sd2[MAXN];
int pts;
double ang[MAXN * 4];
int *idx;
double area[MAXN * 4];

inline double arc(double alpha, double beta)
{
    if (fabs(alpha - beta) < M_PI) return alpha - beta;
    else return 2 * M_PI + alpha - beta;
}

inline double circle_area(double d, double r, double alpha)
{
    double x, beta;
    x = r * r - sqr(d * sin(alpha));
    if (fabs(x) <= EPS) {
        x = d * cos(alpha);
        beta = (alpha < 0 ? alpha + M_PI / 2 : M_PI / 2 - alpha);
    } else {
        x = d * cos(alpha) - sqrt(x);
        beta = acos((d * d + r * r - x * x) / (2.0 * d * r));
    }
    printf("# %.3lf %.3lf %.3lf\n%% %.3lf\n",
        alpha / M_PI * 180, x, beta / M_PI * 180, 0.5 * (d * x * sin(alpha) - beta * r * r * (alpha < 0 ? -1 : 1)));
    //printf("%.2lf %.2lf %.2lf    ", d, r, alpha / M_PI * 180);
    //printf("\t-> %.4lf\n", 0.5 * (d * x * sin(alpha) - beta * r * r * (alpha < 0 ? -1 : 1)));
    return 0.5 * (d * x * sin(alpha) - beta * r * r * (alpha < 0 ? -1 : 1));
}

inline void update_circle(int l, int r, int x, int y, int radius)
{
    //printf("Angle = %.2lf ~ %.2lf   \t(%d, %d) R = %d\n",
    //    ang[l] / M_PI * 180, ang[r] / M_PI * 180, x, y, radius);
    if (l > r) {
        update_circle(l, pts - 1, x, y, radius);
        update_circle(0, r, x, y, radius);
    } else {
        double cen = atan2(y, x);
        double dis = dist(x, y);
        //printf("> %d %d %d\n", x, y, radius);
        for (int i = l; i < r; ++i) {
            //if (i == 0)
            //    printf("> %.4lf %.4lf\n", ang[i + 1] / M_PI * 180, cen / M_PI * 180);
                    //circle_area(dis, radius, ang[i + 1] - cen),
                    //circle_area(dis, radius, ang[i] - cen));
            area[i] = std::min(area[i],
                circle_area(dis, radius, arc(ang[i + 1], cen)) -
                circle_area(dis, radius, arc(ang[i], cen)));
        }
    }
}

inline void update_line(int l, int r, int x1, int y1, int x2, int y2)
{
}

int main()
{
    //printf("%.12lf\n", circle_area(5.22, 2.50, 19.51 / 180 * M_PI));
    //printf("%.12lf\n", circle_area(5.22, 2.50, -19.51 / 180 * M_PI));
    scanf("%d%d", &nc, &ns);
    pts = 0;
    for (int i = 0; i < nc; ++i) {
        scanf("%d%d%d", &cx[i], &cy[i], &cr[i]);
        cd[i] = dist(cx[i], cy[i]);
        double cen = atan2(cy[i], cx[i]);
        double wid = asin((double)cr[i] / cd[i]);
        ang[pts++] = cen - wid;
        ang[pts++] = cen + wid;
    }
    for (int i = 0; i < ns; ++i) {
        scanf("%d%d%d%d%d", &sx1[i], &sy1[i], &sx2[i], &sy2[i], &sr[i]);
        sd1[i] = dist(sx1[i], sy1[i]);
        sd2[i] = dist(sx2[i], sy2[i]);
        double len = dist(sx1[i] - sx2[i], sy1[i] - sy2[i]);
        ang[pts++] = atan2(sy1[i], sx1[i]) - asin((double)sr[i] / sd1[i]);
        ang[pts++] = atan2(sy1[i] + (double)(sx2[i] - sx1[i]) / len,
                           sx1[i] + (double)(sy1[i] - sy2[i]) / len);
        ang[pts++] = atan2(sy2[i] + (double)(sx2[i] - sx1[i]) / len,
                           sx2[i] + (double)(sy1[i] - sy2[i]) / len);
        ang[pts++] = atan2(sy2[i], sx2[i]) + asin((double)sr[i] / sd2[i]);
    }
    for (int i = 0; i < pts; ++i)
        if (ang[i] < -M_PI) ang[i] += M_PI * 2;
        else if (ang[i] >= M_PI) ang[i] -= M_PI * 2;
    ang[pts++] = -M_PI;
    ang[pts++] = M_PI;

    idx = discretize(pts, ang);

    for (int i = 0; i < pts; ++i) area[i] = 1e18;
    for (int i = 0; i < nc; ++i) {
        update_circle(idx[i + i], idx[i + i + 1], cx[i], cy[i], cr[i]);
    }
    for (int i = 0; i < ns; ++i) {
        update_circle(idx[nc * 2 + i * 4], idx[nc * 2 + i * 4 + 1], sx1[i], sy1[i], sr[i]);
        update_circle(idx[nc * 2 + i * 4 + 2], idx[nc * 2 + i * 4 + 3], sx2[i], sy2[i], sr[i]);
        double len = dist(sx1[i] - sx2[i], sy1[i] - sy2[i]);
        update_line(idx[nc * 2 + i * 4 + 1], idx[nc * 2 + i * 4 + 2],
            sy1[i] + (double)(sx2[i] - sx1[i]) / len,
            sx1[i] + (double)(sy1[i] - sy2[i]) / len,
            sy2[i] + (double)(sx2[i] - sx1[i]) / len,
            sx2[i] + (double)(sy1[i] - sy2[i]) / len);
    }

    double ans = 0;
    for (int i = 0; i < pts - 1; ++i) ans += area[i];
    printf("%.12lf\n", ans);
    for (int i = 0; i < pts - 1; ++i)
        printf("%.2lf %.2lf\t%.4lf\n", ang[i] / M_PI * 180, ang[i + 1] / M_PI * 180, area[i]);

    return 0;
}

