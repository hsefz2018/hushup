#include <stdio.h>

#include "caccept.h"

char lcase(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32; else return c;
}
unsigned int isalpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static char s[5];
static long long attempts;
static unsigned int successful;
static int succ_cases = 0, tot_cases = 0;
static long long atts[32];

unsigned int validate()
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
    if (matched == 5) successful = 1;
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
            fprintf(stderr, "Test case #%d\n", tot_cases);
            attempts = 0;
            successful = 0;
            newGame();
            if (successful) {
                ++succ_cases;
                atts[tot_cases - 1] = attempts;
            }
        }
    }

    printf("mekkadondondondondon\n");
    printf("%d %d\n", tot_cases, succ_cases);
    for (int i = 0; i < tot_cases; ++i)
        printf("%lld%c", atts[i], i == tot_cases - 1 ? '\n' : ' ');
    return 0;
}

