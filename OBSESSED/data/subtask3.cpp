#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
static const int MAXN = 300008;

int n, don_cnt, nspct_cnt;
bool is_don[MAXN] = { false };
int don_p[MAXN];

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d%d", &n, &don_cnt, &nspct_cnt);

    printf("%d %d\n", n, don_cnt + nspct_cnt);
    for (int i = 0; i < don_cnt; ++i) is_don[i] = true;
    std::random_shuffle(is_don, is_don + don_cnt + nspct_cnt);
    for (int i = 0; i < n; ++i) don_p[i] = i;
    std::random_shuffle(don_p, don_p + n);
    std::sort(don_p, don_p + don_cnt);

    int u, v, t;
    int dons_passed = 0;
    for (int i = 0; i < don_cnt + nspct_cnt; ++i) {
        if (is_don[i]) {
            printf("Don %d\n", don_p[dons_passed++] + 1);
        } else {
            u = rand() % n + 1; v = rand() % n + 1;
            if (u > v) { t = u; u = v; v = t; }
            printf("Inspect %d %d\n", u, v);
        }
    }

    return 0;
}

