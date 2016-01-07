#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned int uint;

int main()
{
    char pass[] = "hxbxxyzz";
    uint length = strlen(pass);
    uint pairs = 0;
    uint consecutive = 0;
    char prev_pair_char = 0;
    uint prev_pair_idx = 0;
    uint not_allowed = 0;

    while (1)
    {
        pairs = 0;
        consecutive = 0;
        not_allowed = 0;

        // increment password
        for (uint i = length-1; i > 0; i--)
        {
            if (pass[i] == 'z')
            {
                pass[i] = 'a';
            }
            else
            {
                pass[i]++;
                break;
            }
        }

        // check rules
        char* ptr = pass;

        for (uint i = 0; i < length-1; i++, ptr++)
        {
            if (*ptr == 'i' ||
                *ptr == 'o' ||
                *ptr == 'l')
            {
                not_allowed = 1;
                break;
            }

            if (i >= 2)
            {
                if (*ptr == (*(ptr - 1) + 1) && *ptr == (*(ptr - 2) + 2))
                {
                    consecutive = 1;
                }
            }

            if (i < length - 1)
            {
                if (*ptr == *(ptr + 1))
                {
                    if (pairs == 0)
                    {
                        prev_pair_char = *ptr;
                        prev_pair_idx = i+1;
                        pairs++;
                    }
                    if (pairs == 1 && prev_pair_char != *ptr && prev_pair_idx != i)
                    {
                        pairs++;
                    }
                }
            }
        }

        if (pairs >= 2 && consecutive && !not_allowed)
        {
            break;
        }
    }

    cout << "new pass: " << pass << endl;

    return 0;
}