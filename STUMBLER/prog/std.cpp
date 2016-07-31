#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

static const int MAXN = 50008 * 8;
inline double dist(const double x, const double y) {
    return sqrt(x * x + y * y);
}

int nc, ns;
std::pair<double, char> p[MAXN];
int ct = 0;

inline void add_events(const double a, const double b) {
    p[ct++] = std::make_pair(a, +1);
    p[ct++] = std::make_pair(b, -1);
}
inline void add_range(const double a, const double b) {
    if (a < -M_PI) {
        add_events(a + 2 * M_PI, M_PI);
        add_events(-M_PI, b);
    } else if (b > M_PI) {
        add_events(a, M_PI);
        add_events(-M_PI, b - 2 * M_PI);
    } else if (a > b) {
        add_events(a, M_PI);
        add_events(-M_PI, b);
    } else {
        add_events(a, b);
    }
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

    std::sort(p, p + ct);
    int cur_layers = 0;
    double last_ang = -M_PI * 2333;
    double ans = 0.0;
    for (int i = 0; i < ct; ++i) {
        if (cur_layers == 1) ans += (p[i].first - last_ang);
        cur_layers += p[i].second;
        last_ang = p[i].first;
    }
    printf("%.12lf\n", ans / (2 * M_PI));

    fclose(stdin); fclose(stdout);
    return 0;
}

