#include "caccept.h"

void newGame()
{
    char a, b, c, d, e;
    for (a = 'a'; a <= 'z'; ++a)
        for (b = 'a'; b <= 'z'; ++b)
            for (c = 'a'; c <= 'z'; ++c)
                for (d = 'a'; d <= 'z'; ++d)
                    for (e = 'a'; e <= 'z'; ++e)
                        if (makeAttempt(a, b, c, d, e) == 50) return;
}

