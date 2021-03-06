#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

static const int MAXN = 50005;
inline double dist(double x, double y) { return sqrt(x * x + y * y); }

int coord_max, min_dist, max_radius;
int ns, nc;
int cx[MAXN], cy[MAXN], cr[MAXN];
int sx1[MAXN], sx2[MAXN], sy1[MAXN], sy2[MAXN], sr[MAXN];
double begin[MAXN + MAXN], end[MAXN + MAXN];
bool sel[MAXN + MAXN] = { false };

inline double orig_to_line(double x1, double y1, double x2, double y2) {
    // Equation of line (x1,y1)-(x2,y2)
    double a = y1 - y2, b = x2 - x1, c = a * x1 + b * y1;
    return fabs(a + b + c) / sqrt(a * a + b * b);
}

inline double in_arc(const double a, const double b, const double c) {
    if (a > b) return (c > a || c < b); else return (c > a && c < b);
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d%d%d", &coord_max, &min_dist, &max_radius, &nc, &ns);
    double nail = (double)rand() / RAND_MAX * M_PI * 2 - M_PI;
    double d1, d2, d3;
    for (int i = 0; i < MAXN; ++i) do {
        do {
            cx[i] = rand() % (coord_max * 2 + 1) - coord_max;
            cy[i] = rand() % (coord_max * 2 + 1) - coord_max;
            d1 = dist(cx[i], cy[i]);
        } while (d1 <= min_dist);
        cr[i] = rand() % std::min(max_radius, (int)(d1 - 1e-6)) + 1;
        double cen = atan2(cy[i], cx[i]);
        double wid = asin((double)cr[i] / d1);
        begin[i] = cen - wid;
        end[i] = cen + wid;
    } while (!in_arc(begin[i], end[i], nail));
    for (int i = 0; i < MAXN; ++i) do {
        do {
            sx1[i] = rand() % (coord_max * 2 + 1) - coord_max;
            sy1[i] = rand() % (coord_max * 2 + 1) - coord_max;
            sx2[i] = rand() % (coord_max * 2 + 1) - coord_max;
            sy2[i] = rand() % (coord_max * 2 + 1) - coord_max;
            if ((long long)sx1[i] * sy2[i] - (long long)sx2[i] * sy1[i] < 0) {
                std::swap(sx1[i], sx2[i]);
                std::swap(sy1[i], sy2[i]);
            }
            while (dist(sx1[i] - sx2[i], sy1[i] - sy2[i]) > max_radius * 4) {
                sx2[i] = sx1[i] + (sx2[i] - sx1[i]) / 2;
                sy2[i] = sy1[i] + (sy2[i] - sy1[i]) / 2;
            }
            d1 = dist(sx1[i], sy1[i]);
            d2 = dist(sx2[i], sy2[i]);
            d3 = orig_to_line(sx1[i], sy1[i], sx2[i], sy2[i]);
        } while (d3 <= min_dist);
        sr[i] = rand() % std::min(max_radius, (int)(d3 - 1e-6)) + 1;
        begin[i + MAXN] = atan2(sy1[i], sx1[i]) - asin((double)sr[i] / d1);
        end[i + MAXN] = atan2(sy2[i], sx2[i]) - asin((double)sr[i] / d2);
    } while (!in_arc(begin[i + MAXN], end[i + MAXN], nail));

    printf("%d %d\n", nc, ns);
    for (int i = 0; i < nc; ++i) {
        printf("%d %d %d\n", cx[i], cy[i], cr[i]);
    }
    for (int i = 0; i < ns; ++i) {
        printf("%d %d %d %d %d\n",
            sx1[i], sy1[i], sx2[i], sy2[i], sr[i]);
    }

    return 0;
}

