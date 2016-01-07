#include <iostream>
#include <string>
#include <cassert> 

using namespace std;
typedef unsigned int uint;

int process_object(string &json, uint &i)
{
    int local_sum = 0;
    const char *ptr = json.c_str();
    uint outstanding = 0;

    while (ptr[i] != '}' && ptr[i] != '\0')
    {
        if (ptr[i] == '{')
        {
            i++;
            local_sum += process_object(json, i);
        }
        else if (ptr[i] == '-')
        {
            uint tmp = 0;
            i++;
            while (ptr[i] >= '0' && ptr[i] <= '9')
            {
                tmp = tmp * 10;
                tmp += ptr[i] - '0';
                i++;
            }
            i--;
            local_sum -= tmp;
        }
        else if (ptr[i] >= '0' && ptr[i] <= '9')
        {
            uint tmp = ptr[i] - '0';
            i++;
            while (ptr[i] >= '0' && ptr[i] <= '9')
            {
                tmp = tmp * 10;
                tmp += ptr[i] - '0';
                i++;
            }
            i--;
            local_sum += tmp;
        }
        else if (ptr[i] == 'r' && ptr[i + 1] == 'e' && ptr[i + 2] == 'd' && ptr[i-1] == '\"' && ptr[i-2] == ':')
        {
            // increment until close bracket and bounce with 0
            while (1)
            {
                if (ptr[i] == '{')
                {
                    outstanding++;
                }

                if (ptr[i] == '}')
                {
                    if (outstanding == 0)
                    {
                        return 0;
                    }
                    else
                    {
                        outstanding--;
                    }
                }
                i++;
            }
        }
        i++;
    }

    return local_sum;
}

int main()
{
    string json;
    cin >> json;

    const char *ptr = json.c_str();

    uint sum = 0;

    for (uint i = 0; i < json.length(); i++)
    {
        if (ptr[i] == '{')
        {
            i++;
            sum += process_object(json, i);
        }
        else if (ptr[i] == '-')
        {
            uint tmp = 0;
            i++;
            while (ptr[i] >= '0' && ptr[i] <= '9')
            {
                tmp = tmp * 10;
                tmp += ptr[i] - '0';
                i++;
            }

            sum -= tmp;
            i--;
        }
        else if (ptr[i] >= '0' && ptr[i] <= '9')
        {
            uint tmp = ptr[i] - '0';
            i++;
            while (ptr[i] >= '0' && ptr[i] <= '9')
            {
                tmp = tmp * 10;
                tmp += ptr[i] - '0';
                i++;
            }

            sum += tmp;
            i--;
        }
    }

    cout << "sum: " << sum << endl;

    return 0;
}