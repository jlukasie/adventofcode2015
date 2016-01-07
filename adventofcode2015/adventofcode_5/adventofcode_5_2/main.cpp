#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

string make_key(char a, char b)
{
    stringstream ss;

    ss << a << b;

    return ss.str();
}

int main()
{
    string str;

    unordered_map<string, int> pairs;
    bool in_between = false;
    bool has_pair = false;
    int good_cnt = 0;
    for (int i = 0; i < 1000; i++)
    {
        pairs.clear();
        in_between = false;
        has_pair = false;

        cin >> str;
        const char *ptr = str.c_str();

        for (int i = 0; i < str.length(); i++)
        {
            if (i < str.length()-1)
            {
                string key = make_key(*ptr, *(ptr + 1));
                if (pairs.find(key) != pairs.end())
                {
                    if (!(*ptr == *(ptr+1) && *ptr == *(ptr-1)))
                    {
                        pairs[key]++;
                    }
                }
                else
                {
                    pairs[key] = 1;
                }
            }

            if (i < str.length() - 2)
            {
                if (*ptr == *(ptr + 2))
                {
                    in_between = true;
                }
            }
            
            ptr++;
        }

        for (auto pair : pairs)
        {
            if (pair.second > 1)
            {
                has_pair = true;
                break;
            }
        }

        if (has_pair && in_between)
        {
            good_cnt++;
        }
    }

    cout << good_cnt << endl;

    return 0;
}