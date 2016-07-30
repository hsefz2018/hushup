#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

static const int MAXN = 10000;
template <typename T> inline T sqr(const T x) { return x * x; }
inline double dist(double x, double y) { return sqrt(x * x + y * y); }
inline double arc(double alpha, double beta)
{
    if (fabs(alpha - beta) < M_PI) return alpha - beta;
    else return 2 * M_PI + alpha - beta;
}

int coord_max, mul;
int ns, nc;
int cx[MAXN], cy[MAXN], cr[MAXN];
int sx1[MAXN], sx2[MAXN], sy1[MAXN], sy2[MAXN], sr[MAXN];
double cd[MAXN], sd1[MAXN], sd2[MAXN];
double cbegin[MAXN], cend[MAXN], sbegin[MAXN], send[MAXN];
std::pair<double, int> p[MAXN + MAXN];
bool sel[MAXN + MAXN] = { false };

inline double get_end(int idx) {
    if (idx < MAXN) return cend[idx]; else return send[idx - MAXN];
}
inline double orig_to_line(double x1, double y1, double x2, double y2) {
    // Equation of line (x1,y1)-(x2,y2)
    double a = y1 - y2, b = x2 - x1, c = a * x1 + b * y1;
    return fabs(a + b + c) / sqrt(a * a + b * b);
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d%d", &coord_max, &mul, &ns, &nc);
    for (int i = 0; i < MAXN; ++i) {
        cx[i] = rand() % (coord_max * 2 + 1) - coord_max;
        cy[i] = rand() % (coord_max * 2 + 1) - coord_max;
        cd[i] = dist(cx[i], cy[i]);
        if (cd[i] <= 1) { cbegin[i] = NAN; continue; }
        cr[i] = rand() % (int)(cd[i] - 1e-6) + 1;
        double cen = atan2(cy[i], cx[i]);
        double wid = asin((double)cr[i] / cd[i]);
        cbegin[i] = cen - wid;
        cend[i] = cen + wid;
    }
    for (int i = 0; i < MAXN; ++i) {
        sx1[i] = rand() % (coord_max * 2 + 1) - coord_max;
        sy1[i] = rand() % (coord_max * 2 + 1) - coord_max;
        sx2[i] = rand() % (coord_max * 2 + 1) - coord_max;
        sy2[i] = rand() % (coord_max * 2 + 1) - coord_max;
        if (sx1[i] * sy2[i] - sx2[i] * sy1[i] < 0) {
            std::swap(sx1[i], sx2[i]);
            std::swap(sy1[i], sy2[i]);
        }
        sd1[i] = dist(sx1[i], sy1[i]);
        sd2[i] = dist(sx2[i], sy2[i]);
        double dis = orig_to_line(sx1[i], sy1[i], sx2[i], sy2[i]);
        if (std::min(sd1[i], sd2[i]) <= 1 || dis <= 1) { sbegin[i] = NAN; continue; }
        sr[i] = rand() % (int)(dis - 1e-6) + 1;
        sbegin[i] = atan2(sy1[i], sx1[i]) - asin((double)sr[i] / sd1[i]);
        send[i] = atan2(sy2[i], sx2[i]) - asin((double)sr[i] / sd2[i]);
    }

    for (int i = 0; i < MAXN; ++i) p[i].first = isnan(cbegin[i]) ? -1e8 : cbegin[i];
    for (int i = 0; i < MAXN; ++i) p[i + MAXN].first = isnan(sbegin[i]) ? -1e8 : sbegin[i];
    for (int i = 0; i < MAXN * 2; ++i) p[i].second = i;
    std::sort(p, p + MAXN + MAXN);

    double ang = -M_PI;
    int idx = 0, last_idx;
    while (idx < MAXN + MAXN && p[idx].first == -1e8) ++idx;
    while (ang <= M_PI && idx < MAXN + MAXN) {
        last_idx = idx;
        while (idx < MAXN + MAXN && p[idx].first < ang) ++idx;
        if (idx == last_idx) {
            last_idx = 0;
        }
        int u = last_idx + rand() % (idx - last_idx);
        sel[u] = true;
        ang = std::max(ang, get_end(p[u].second));
        if (idx >= MAXN + MAXN) break;
    }

    int real_nc = 0, real_ns = 0;
    for (int i = 0; i < MAXN + MAXN; ++i) if (sel[i]) {
        if (i < MAXN) ++real_nc; else ++real_ns;
    }
    int u;
    while (real_nc < nc) {
        do u = rand() % MAXN; while (sel[u]);
        sel[u] = true; ++real_nc;
    }
    while (real_ns < ns) {
        do u = rand() % MAXN + MAXN; while (sel[u]);
        sel[u] = true; ++real_ns;
    }

    printf("%d %d\n", real_nc, real_ns);
    for (int i = 0; i < MAXN + MAXN; ++i) if (sel[i]) {
        if (i < MAXN) printf("%d %d %d\n", cx[i] * mul, cy[i] * mul, cr[i] * mul);
        else printf("%d %d %d %d %d\n",
            sx1[i - MAXN] * mul, sy1[i - MAXN] * mul,
            sx2[i - MAXN] * mul, sy2[i - MAXN] * mul, sr[i - MAXN] * mul);
    }

    return 0;
}

