#include <cstdio>
#include <cmath>
#include <utility>

int ct[6][6] = {{ 0 }};

std::pair<int, int> check(const char *ans, const char *val)
{
    int matched = 0, distinct = 0;
    for (int i = 0; i < 5; ++i)
        if (val[i] == ans[i]) ++matched;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            if (ans[i] == val[j]) { ++distinct; break; }
    }
    return std::make_pair(matched, distinct - matched);
}

int main()
{
    const char *ans = "mikan";
    char str[5];
#define a str[0]
#define b str[1]
#define c str[2]
#define d str[3]
#define e str[4]
    for (a = 'a'; a <= 'z'; ++a)
        for (b = 'a'; b <= 'z'; ++b) if (b != a)
            for (c = 'a'; c <= 'z'; ++c) if (c != a && c != b)
                for (d = 'a'; d <= 'z'; ++d) if (d != a && d != b && d != c)
                    for (e = 'a'; e <= 'z'; ++e) if (e != a && e != b && e != c && e != d) {
                        std::pair<int, int> result = check(ans, str);
                        ++ct[result.first][result.second];
                    }
    double entropy = 0.0;
    for (int i = 0; i <= 5; ++i)
        for (int j = 0; j <= 5; ++j) if (ct[i][j]) {
            double p = (double)ct[i][j] / (26 * 25 * 24 * 23 * 22);
            printf("Matched %d, distinct %d: Cases = %d\tProb = %.6lf\n", i, j, ct[i][j], p);
            entropy -= p * log(p) / log(2);
        }
    printf("Entropy = %.6lf\n", entropy);
    return 0;
}
