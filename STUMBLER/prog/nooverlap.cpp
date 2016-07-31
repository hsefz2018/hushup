#include <cstdio>
#include <cmath>
#include <algorithm>

static const int MAXN = 50008 * 8;
inline double dist(const double x, const double y) {
    return sqrt(x * x + y * y);
}

int nc, ns;
int ct = 0;

double ans = 0;
inline double get_range(const double a, const double b) {
    if (a > b) {
        if (2 * M_PI - (b - a) < M_PI) return 2 * M_PI - (b - a);
        else return -1;
    } else return (b - a);
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
        ans += get_range(cen - wid, cen + wid);
        //printf(" [%.2lf, %.2lf]\n", (cen - wid) / M_PI * 180, (cen + wid) / M_PI * 180);
        //printf("%d %.12lf\n", i, ans / (2 * M_PI));
    }
    for (int i = 0; i < ns; ++i) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &r);
        double a1 = atan2(y1, x1) - asin((double)r / dist(x1, y1));
        double a2 = atan2(y1, x1) + asin((double)r / dist(x1, y1));
        double a3 = atan2(y2, x2) - asin((double)r / dist(x2, y2));
        double a4 = atan2(y2, x2) + asin((double)r / dist(x2, y2));
        ans += std::max(get_range(a1, a4), std::max(get_range(a1, a2), get_range(a3, a4)));
        //printf("%d %d %d %d %d\n", x1, y1, x2, y2, r);
        //printf(" [%.2lf, %.2lf]\n", a1 / M_PI * 180, a2 / M_PI * 180);
        //printf("%d %.12lf\n", i, ans / (2 * M_PI));
    }

    printf("%.12lf\n", ans / (2 * M_PI));

    fclose(stdin); fclose(stdout);
    return 0;
}

