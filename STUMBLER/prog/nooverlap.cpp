#include <cstdio>
#include <cmath>

static const int MAXN = 50008 * 8;
inline double dist(const double x, const double y) {
    return sqrt(x * x + y * y);
}

int nc, ns;
int ct = 0;

double ans = 0;
inline void add_range(const double a, const double b) {
    if (a > b) ans += 2 * M_PI - (b - a); else ans += (b - a);
}

int main()
{
    freopen("stumbler.in", "r", stdin);
    freopen("stumbler.out", "w", stdout);

    scanf("%d%d", &nc, &ns);
    int x1, y1, x2, y2, r;
    for (int i = 0; i < nc; ++i) {
        scanf("%d%d%d", &x1, &y1, &r);
        double cen = atan2(y1, x1);
        double wid = asin((double)r / dist(x1, y1));
        add_range(cen - wid, cen + wid);
    }
    for (int i = 0; i < ns; ++i) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &r);
        double a1 = atan2(y1, x1) - asin((double)r / dist(x1, y1));
        double a2 = atan2(y2, x2) + asin((double)r / dist(x2, y2));
        add_range(a1, a2);
    }

    printf("%.12lf\n", ans / (2 * M_PI));

    fclose(stdin); fclose(stdout);
    return 0;
}

