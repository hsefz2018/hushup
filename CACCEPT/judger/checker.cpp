#include <cstdio>
#include <cstring>

template <typename T> inline T min(const T a, const T b) {
    return a < b ? a : b;
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[3], "r");
    char passphrase[64];
    fgets(passphrase, 64, fp);
    if (strcmp(passphrase, "mekkadondondondondon\n") != 0) {
        fprintf(stderr, "Your program should not write to output itself.\n");
        printf("0.0");
        return 0;
    }
    int succ_cases, tot_cases;
    long long atts[32];
    long long tot_att = 0, max_att = 0;
    if (fscanf(fp, "%d%d", &tot_cases, &succ_cases) != 2) {
        fprintf(stderr, "Invalid output. Please contact NPCs OvO");
        printf("0.0");
        return 0;
    }
    for (int i = 0; i < tot_cases; ++i)
        if (fscanf(fp, "%lld", &atts[i]) != 1) {
            fprintf(stderr, "Invalid output. Please contact NPCs OvO");
            printf("0.0");
            return 0;
        } else {
            tot_att += atts[i];
            if (max_att < atts[i]) max_att = atts[i];
        }
    fclose(fp);
    fprintf(stderr, "Correct %d/%d with %lld attempts total and"
        " %lld max. per case", succ_cases, tot_cases, tot_att, max_att);
    if (succ_cases != tot_cases) {
        printf("%.3lf", 0.2 * succ_cases / tot_cases);
    } else {
        double eff_score = 0;
        for (int i = 0; i < tot_cases; ++i)
            eff_score += min(1.0, 11.0 / atts[i]);
        eff_score /= tot_cases;
        eff_score *= eff_score;
        double score = 0.2 + 0.8 * eff_score;
        printf("%.3lf", score);
    }
    return 0;
}

