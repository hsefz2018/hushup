#include <stdio.h>

#include "caccept.h"
static const int MAX_TESTS = 131072;

char lcase(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32; else return c;
}
bool isalpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static char s[5];
static long long attempts;
static bool successful[MAX_TESTS];
static int succ_cases = 0, tot_cases = 0;
static long long atts[MAX_TESTS];

bool validate()
{
    int i, j;
    for (i = 0; i < 5; ++i)
        for (j = 0; j < 5; ++j)
            if (i != j && s[i] == s[j]) {
                fprintf(stderr, "Invalid input: duplicate characters ('%c')\n", s[i]);
                return 0;
            }
    return 1;
}

int makeAttempt(char a, char b, char c, char d, char e)
{
    ++attempts;

    static char t[5];
    t[0] = lcase(a); t[1] = lcase(b);
    t[2] = lcase(c); t[3] = lcase(d); t[4] = lcase(e);
    int i, j, matched = 0, distinct = 0;
    for (i = 0; i < 5; ++i)
        if (s[i] == t[i]) ++matched;
    for (i = 0; i < 5; ++i)
        for (j = 0; j < 5; ++j)
            if (s[i] == t[j]) { ++distinct; break; }
    if (matched == 5) successful[tot_cases - 1] = 1;
    return matched * 10 + (distinct - matched);
}

int main()
{
    int i;
    while (!feof(stdin)) {
        for (i = 0; i < 5; ++i)
            do s[i] = lcase(getchar()); while (!isalpha(s[i]) && s[i] != EOF);
        if (i < 5) break;
        if (validate()) {
            ++tot_cases;
            attempts = 0;
            successful[tot_cases - 1] = 0;
            newGame();
            if (successful[tot_cases - 1]) {
                ++succ_cases;
                atts[tot_cases - 1] = attempts;
            }
        }
    }

    printf("Passed %d test(s) out of %d\n", succ_cases, tot_cases);
    for (int i = 0; i < tot_cases; ++i) {
        printf("Case #%d: ", i + 1);
        if (successful[i]) {
            printf("passed within %lld attempts\n", atts[i]);
        } else {
            printf("failed  T^T\n");
        }
    }
    return 0;
}

