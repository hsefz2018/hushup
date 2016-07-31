#include <cstdio>
#include <cassert>
#include <cmath>

template <typename T> inline T min(const T a, const T b) {
    return a < b ? a : b;
}

int main(int argc, char *argv[])
{
    FILE *out = fopen(argv[2], "r");
    FILE *ans = fopen(argv[3], "r");

    double jury_ans, ctst_ans;
    assert(fscanf(ans, "%lf", &jury_ans) == 1);
    if (fscanf(out, "%lf", &ctst_ans) != 1) {
        fprintf(stderr, "Incorrect format: must contain one decimal number");
        printf("0.0");
    } else {
        if (fabs(jury_ans - ctst_ans) > 1e-6) {
            fprintf(stderr, "Incorrect answer: absolute error is %.2e", fabs(jury_ans - ctst_ans));
            printf("0.0");
        } else {
            fprintf(stderr, "Correct (・ω・)ノ");
            printf("1.0");
        }
    }

    fclose(out); fclose(ans);
    return 0;
}

