#include <cstdio>
#include <cstdlib>
#include <ctime>

int n, m;

int main(int argc, char *argv[])
{
    unsigned int seed = 0;
    if (argc >= 2) seed = atoi(argv[1]);
    if (seed == 0) seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    double don_prob, kat_prob, invrt_prob, nspct_prob, sum_prob;
    scanf("%d%d", &n, &m);
    scanf("%lf%lf%lf%lf", &don_prob, &kat_prob, &invrt_prob, &nspct_prob);
    sum_prob = don_prob + kat_prob + invrt_prob + nspct_prob;

    printf("%d %d\n", n, m);
    int u, v, t, s;
    double r;
    for (int i = 0; i < m; ++i) {
        r = (double)rand() / RAND_MAX;
        if (r < don_prob / sum_prob) s = 0;
        else if (r < (don_prob + kat_prob) / sum_prob) s = 1;
        else if (r < (don_prob + kat_prob + invrt_prob) / sum_prob) s = 2;
        else s = 3;
        switch (s) {
            case 0: printf("Don %d\n", rand() % n + 1); break;
            case 1: printf("Kat %d\n", rand() % n + 1); break;
            case 2: case 3:
                u = rand() % n + 1; v = rand() % n + 1;
                if (u > v) { t = u; u = v; v = t; }
                printf(s == 2 ? "Invert %d %d\n" : "Inspect %d %d\n", u, v);
        }
    }

    return 0;
}

