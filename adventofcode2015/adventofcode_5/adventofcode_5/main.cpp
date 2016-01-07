#include <iostream>
#include <string>

using namespace std;

int is_vowel(char c)
{
    if (c == 'a' ||
        c == 'e' ||
        c == 'i' ||
        c == 'o' ||
        c == 'u')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool is_evil(const char* str)
{
    if (!strncmp(str, "ab", 2) ||
        !strncmp(str, "cd", 2) ||
        !strncmp(str, "pq", 2) ||
        !strncmp(str, "xy", 2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    string str;

    unsigned int double_cnt = 0;
    unsigned int vowel_cnt = 0;
    bool evil = false;
    unsigned int good_cnt = 0;

    for (int i = 0; i < 1000; i++)
    {
        cin >> str;
        const char *ptr = str.c_str();

        for (int i = 0; i < 16; i++)
        {
            if (is_evil(ptr))
            {
                evil = true;
                break;
            }

            vowel_cnt += is_vowel(*ptr);
            double_cnt += (*(ptr + 1) == *ptr) ? 1 : 0;

            ptr++;
        }

        if (vowel_cnt >= 3 &&
            double_cnt > 0 &&
            !evil)
        {
            good_cnt++;
        }

        vowel_cnt = 0;
        double_cnt = 0;
        evil = false;
    }

    return 0;
}