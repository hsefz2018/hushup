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

double slice[MAXN + MAXN];
int slice_idx[MAXN + MAXN];

inline double orig_to_line(double x1, double y1, double x2, double y2) {
    // Equation of line (x1,y1)-(x2,y2)
    double a = y1 - y2, b = x2 - x1, c = a * x1 + b * y1;
    return fabs(a + b + c) / sqrt(a * a + b * b);
}

inline bool diff_lt3(const double &a, const double &b) { return fabs(a - b) < 3; }

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
    int top = std::unique(slice, slice + ns + nc, diff_lt3) - &slice[0];
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

    double ang;
    double d1, d2, d3;
    for (int i = 0; i < real_nc; ++i) {
        // printf("%.2lf %.2lf\n", slice[slice_idx[i]], slice[slice_idx[i] + 1]);
        do {
            ang = slice[slice_idx[i]] +
                (double)rand() / RAND_MAX * (slice[slice_idx[i] + 1] - slice[slice_idx[i]]);
            d1 = min_dist + (double)rand() / RAND_MAX * (coord_max - min_dist);
            cx[i] = (int)round(cos(ang) * d1);
            cy[i] = (int)round(sin(ang) * d1);
            d1 = dist(cx[i], cy[i]);
            cr[i] = rand() % std::min(max_radius, (int)(d1 - 1e-6)) + 1;
            double cen = atan2(cy[i], cx[i]);
            double wid = asin((double)cr[i] / d1);
            begin[i] = cen - wid;
            end[i] = cen + wid;
        } while (begin[i] < slice[slice_idx[i]] || end[i] > slice[slice_idx[i] + 1]);
    }
    for (int i = 0; i < real_ns; ++i) {
        do {
            ang = slice[slice_idx[i + real_nc]] +
                (double)rand() / RAND_MAX * (slice[slice_idx[i + real_nc] + 1] - slice[slice_idx[i + real_nc]]);
            d1 = min_dist + (double)rand() / RAND_MAX * (coord_max - min_dist);
            sx1[i] = (int)round(cos(ang) * d1);
            sy1[i] = (int)round(sin(ang) * d1);
            d1 = dist(sx1[i], sy1[i]);
            ang = slice[slice_idx[i + real_nc]] +
                (double)rand() / RAND_MAX * (slice[slice_idx[i + real_nc] + 1] - slice[slice_idx[i + real_nc]]);
            d2 = min_dist + (double)rand() / RAND_MAX * (coord_max - min_dist);
            sx2[i] = (int)round(cos(ang) * d2);
            sy2[i] = (int)round(sin(ang) * d2);
            d2 = dist(sx2[i], sy2[i]);
            if (sx1[i] * sy2[i] - sx2[i] * sy1[i] < 0) {
                std::swap(sx1[i], sx2[i]);
                std::swap(sy1[i], sy2[i]);
            }
            while (dist(sx1[i] - sx2[i], sy1[i] - sy2[i]) > max_radius * 4) {
                sx2[i] = sx1[i] + (sx2[i] - sx1[i]) / 2;
                sy2[i] = sy1[i] + (sy2[i] - sy1[i]) / 2;
            }
            d3 = orig_to_line(sx1[i], sy1[i], sx2[i], sy2[i]);
            sr[i] = rand() % std::min(max_radius, (int)(d3 - 1e-6)) + 1;
            begin[i + MAXN] = atan2(sy1[i], sx1[i]) - asin((double)sr[i] / d1);
            end[i + MAXN] = atan2(sy2[i], sx2[i]) - asin((double)sr[i] / d2);
        } while (d3 <= min_dist || begin[i + MAXN] < slice[slice_idx[i + real_nc]] ||
            end[i + MAXN] > slice[slice_idx[i + real_nc] + 1]);
    }

    printf("%d %d\n", real_nc, real_ns);
    for (int i = 0; i < real_nc; ++i) {
        printf("%d %d %d\n", cx[i], cy[i], cr[i]);
    }
    for (int i = 0; i < real_ns; ++i) {
        printf("%d %d %d %d %d\n", sx1[i], sy1[i], sx2[i], sy2[i], sr[i]);
    }

    return 0;
}

