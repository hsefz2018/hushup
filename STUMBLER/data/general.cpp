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

int coord_max;
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

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d", &coord_max, &ns, &nc);
    for (int i = 0; i < MAXN; ++i) {
        cx[i] = rand() % (coord_max * 2 + 1) - coord_max;
        cy[i] = rand() % (coord_max * 2 + 1) - coord_max;
        cd[i] = dist(cx[i], cy[i]);
        //cr[i] = std::min((int)(cd[i] - 1e-6), rand() % coord_max + 1);
        if (cd[i] <= 1) { cbegin[i] = NAN; continue; }
        cr[i] = rand() % (int)(cd[i] - 1e-6) + 1;
        double cen = atan2(cy[i], cx[i]);
        double wid = asin((double)cr[i] / cd[i]);
        cbegin[i] = cen - wid;
        cend[i] = cen + wid;
        //printf("(%d) %d %d %d\n", i, cx[i], cy[i], cr[i]);
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
        //sr[i] = std::min((int)(std::min(sd1[i], sd2[i]) - 1e-6), rand() % coord_max + 1);
        if (std::min(sd1[i], sd2[i]) <= 1) { sbegin[i] = NAN; continue; }
        sr[i] = rand() % (int)(std::min(sd1[i], sd2[i]) - 1e-6) + 1;
        sbegin[i] = atan2(sy1[i], sx1[i]) - asin((double)sr[i] / sd1[i]);
        send[i] = atan2(sy2[i], sx2[i]) - asin((double)sr[i] / sd2[i]);
        //printf("(%d) %d %d %d %d %d\n", i, sx1[i], sy1[i], sx2[i], sy2[i], sr[i]);
    }

    for (int i = 0; i < MAXN; ++i) p[i].first = isnan(cbegin[i]) ? -1e8 : cbegin[i];
    for (int i = 0; i < MAXN; ++i) p[i + MAXN].first = isnan(sbegin[i]) ? -1e8 : sbegin[i];
    for (int i = 0; i < MAXN * 2; ++i) p[i].second = i;
    std::sort(p, p + MAXN + MAXN);
    for (int j = 0; j < MAXN + MAXN; ++j) {
        int i = p[j].second;
        printf("%lf~%lf | ", p[j].first, get_end(i));
        if (i < MAXN) printf("%d %d %d\n", cx[i], cy[i], cr[i]);
        else printf("%d %d %d %d %d\n",
            sx1[i - MAXN], sy1[i - MAXN], sx2[i - MAXN], sy2[i - MAXN], sr[i - MAXN]);
    }
    /*for (int i = 0; i < MAXN + MAXN; ++i) {
        printf("[%d] %lf %d\n", i, p[i].first, p[i].second);
    }*/
    puts("A"); fflush(stdout);

    double ang = -M_PI, furthest;
    int idx = 0, furthest_idx;
    while (idx < MAXN + MAXN && p[idx].first == -1e8) ++idx;
    while (ang <= M_PI && idx < MAXN + MAXN) {
        puts("B"); fflush(stdout);
        furthest = -M_PI * 1000;
        furthest_idx = -1;
        while (idx < MAXN + MAXN && p[idx].first < ang) {
            if (furthest < p[idx].first + get_end(p[idx].second)) {
                furthest = p[idx].first + get_end(p[idx].second);
                furthest_idx = p[idx].second;
            }
            ++idx;
        }
        printf("%d %d %lf %lf\n", idx, furthest_idx, p[idx].first, furthest); fflush(stdout);
        if (furthest_idx != -1) sel[furthest_idx] = true;
        ang = furthest;
        if (idx >= MAXN + MAXN) break;
    }

    for (int i = 0; i < MAXN + MAXN; ++i) if (sel[i]) {
        if (i < MAXN) printf("%d %d %d\n", cx[i], cy[i], cr[i]);
        else printf("%d %d %d %d %d\n",
            sx1[i - MAXN], sy1[i - MAXN], sx2[i - MAXN], sy2[i - MAXN], sr[i - MAXN]);
    }

    return 0;
}

