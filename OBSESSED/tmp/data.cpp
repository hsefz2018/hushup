#include <cstdio>
#include <cstdlib>
#include <ctime>

int n, m;

int main()
{
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    fprintf(stderr, "Seed: %u\n", seed);

    scanf("%d%d", &n, &m);
    printf("%d %d\n", n, m);
    int u, v, t, r;
    for (int i = 0; i < m; ++i) {
        switch (r = rand() % 4) {
            case 0: printf("Don %d\n", rand() % n + 1); break;
            case 1: printf("Kat %d\n", rand() % n + 1); break;
            case 2: case 3:
                u = rand() % n + 1; v = rand() % n + 1;
                if (u > v) { t = u; u = v; v = t; }
                printf(r == 2 ? "Invert %d %d\n" : "Inspect %d %d\n", u, v);
        }
    }

    return 0;
}

