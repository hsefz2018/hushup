#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

#include "caccept.h"
static const int NUM_PERMS = 26 * 25 * 24 * 23 * 22 + 15;

int pperm_ct = 0, perm_ct;
char _pool[NUM_PERMS * 5];
char *p[NUM_PERMS], *pp[NUM_PERMS];
std::pair<int, int> pp_res[NUM_PERMS];

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

char *get_random_query()
{
    return pp[rand() % pperm_ct];
}

int eval_entropy(char *query)
{
    static int ct[6][6];
    static std::pair<int, int> result;
    std::fill(&ct[0][0], &ct[0][0] + 36, 0);
    for (int i = 0; i < std::min(perm_ct, 768); ++i) {
        result = check(p[i], query);
        ++ct[result.first][result.second];
    }
    int ans = 0;
    for (int i = 0; i <= 5; ++i)
        for (int j = 0; j <= 5; ++j) if (ans < ct[i][j]) ans = ct[i][j];
    return ans;
}

inline std::pair<int, int> sendAttempt(const char *s) {
    int res = makeAttempt(s[0], s[1], s[2], s[3], s[4]);
    return std::make_pair(res / 10, res % 10);
}

void newGame()
{
    srand((unsigned)time(NULL));
    const char *first_query = "mikan";
    std::pair<int, int> first_result;
    first_result = sendAttempt(first_query);

    if (pperm_ct == 0) {
        for (char a = 'a'; a <= 'z'; ++a)
            for (char b = 'a'; b <= 'z'; ++b) if (b != a)
                for (char c = 'a'; c <= 'z'; ++c) if (c != a && c != b)
                    for (char d = 'a'; d <= 'z'; ++d) if (d != a && d != b && d != c)
                        for (register char e = 'a'; e <= 'z'; ++e) if (e != a && e != b && e != c && e != d) {
                            char *s = _pool + pperm_ct * 5 * sizeof(char);
                            s[0] = a; s[1] = b; s[2] = c; s[3] = d; s[4] = e;
                            pp[pperm_ct] = s;
                            pp_res[pperm_ct] = check(pp[pperm_ct], first_query);
                            ++pperm_ct;
                        }
        //std::random_shuffle(pp, pp + pperm_ct);
        for (int i = pperm_ct - 64; i < pperm_ct; ++i) {
            int j = rand() % i;
            std::swap(pp[i], pp[j]);
            std::swap(pp_res[i], pp_res[j]);
        }
    }

    perm_ct = 0;
    for (int i = 0; i < pperm_ct; ++i)
        if (pp_res[i] == first_result) p[perm_ct++] = pp[i];
    while (perm_ct > 1) {
        static std::pair<int, char *> q_cur, q_best;
        q_best = std::make_pair(0x7fffffff, nullptr);
        for (int i = 0; i < 4096; ++i) {
            q_cur.second = get_random_query();
            q_cur.first = eval_entropy(q_cur.second);
            if (q_best.first > q_cur.first) q_best = q_cur;
        }

        std::pair<int, int> result = sendAttempt(q_best.second);
        for (int i = 0; i < perm_ct; ) {
            if (check(p[i], q_best.second) == result) {
                ++i;
            } else {
                std::swap(p[i], p[perm_ct - 1]);
                --perm_ct;
            }
        }
    }
    // The answer
    sendAttempt(p[0]);
}
