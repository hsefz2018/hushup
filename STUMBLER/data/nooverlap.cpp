#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

static const int MAXN = 150005;
inline double dist(double x, double y) { return sqrt(x * x + y * y); }

int coord_max, min_dist, max_radius;
int ns, nc;
int cx[MAXN], cy[MAXN], cr[MAXN];
int sx1[MAXN], sx2[MAXN], sy1[MAXN], sy2[MAXN], sr[MAXN];
double begin[MAXN + MAXN], end[MAXN + MAXN];
bool sel[MAXN + MAXN] = { false };

double slice[MAXN + MAXN];
int slice_idx[MAXN + MAXN];

inline double orig_to_line(double x1, double y1, double x2, double y2) {
    // Equation of line (x1,y1)-(x2,y2)
    double a = y1 - y2, b = x2 - x1, c = a * x1 + b * y1;
    return fabs(a + b + c) / sqrt(a * a + b * b);
}

inline bool diff_nbr(const double &a, const double &b) { return fabs(a - b) < 10; }

inline void gen_circle_in_range(const double l, const double r, int &x, int &y, int &radius) {
    static double ang, d1, begin, end, ll, rr, wid, cen;
    static int d_min;
    // printf("< %.2lf %.2lf\n", l, r);
    do {
        radius = rand() % max_radius + 1;
        d_min = std::max(radius, std::max(min_dist, (int)ceil(radius / tan((r - l) / 2))));
        d1 = d_min + (double)rand() / RAND_MAX * (coord_max - d_min);
        wid = asin((double)radius / d1);
        ll = l + wid, rr = r - wid;
        ang = ll + (double)rand() / RAND_MAX * (rr - ll);
        x = (int)round(cos(ang) * d1);
        y = (int)round(sin(ang) * d1);
        d1 = dist(x, y);
        cen = atan2(y, x);
        begin = cen - wid;
        end = cen + wid;
    } while (begin < l || end > r);
    // printf("> %d %d %d | %.2lf %.2lf\n", x, y, radius, begin, end);
}

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d%d%d", &coord_max, &min_dist, &max_radius, &nc, &ns);
    slice[0] = -1;
    int real_ns = ns, real_nc = nc;
    for (int i = 1; i < ns + nc; ++i)
        slice[i] = rand() % 1048576;
    std::sort(slice, slice + ns + nc);
    int top = std::unique(slice, slice + ns + nc, diff_nbr) - &slice[0];
    slice[top] = M_PI;
    for (int i = 0; i < top; ++i) {
        slice[i] = -M_PI + (double)(slice[i] + 1) / 1048577 * 2 * M_PI;
    }
    for (int i = 0; i < (ns + nc - top); ++i) {
        if (!real_nc) --real_ns; else if (!real_ns) --real_nc;
        else if (rand() & 1) --real_ns;
        else --real_nc;
    }
    for (int i = 0; i < top; ++i) slice_idx[i] = i;
    std::random_shuffle(slice_idx, slice_idx + top);

    double ang, l, r;
    for (int i = 0; i < real_nc; ++i) {
        l = slice[slice_idx[i]];
        r = slice[slice_idx[i] + 1];
        gen_circle_in_range(l, r, cx[i], cy[i], cr[i]);
        // if (i % 100 == 0) fprintf(stderr, "# %d\n", i);
    }
    int r1, r2;
    for (int i = 0; i < real_ns; ++i) {
        l = slice[slice_idx[i + real_nc]];
        r = slice[slice_idx[i + real_nc] + 1];
        gen_circle_in_range(l, r, sx1[i], sy1[i], r1);
        gen_circle_in_range(l, r, sx2[i], sy2[i], r2);
        sr[i] = std::min(r1, r2);
        if ((long long)sx1[i] * sy2[i] - (long long)sx2[i] * sy1[i] < 0) {
            std::swap(sx1[i], sx2[i]);
            std::swap(sy1[i], sy2[i]);
        }
    }

    // Flip. Get something go across the +/-PI ray.
    printf("%d %d\n", real_nc, real_ns);
    for (int i = 0; i < real_nc; ++i) {
        printf("%d %d %d\n", cy[i], cx[i], cr[i]);
    }
    for (int i = 0; i < real_ns; ++i) {
        printf("%d %d %d %d %d\n", sy1[i], sx1[i], sy2[i], sx2[i], sr[i]);
    }

    return 0;
}

