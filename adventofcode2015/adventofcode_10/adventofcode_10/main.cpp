#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef unsigned int uint;
int main()
{
    string input = "1113222113";
    stringstream ss;

    const char *ptr = input.c_str();

    uint cur_char = 0;

    for (int i = 0; i < 50; i++)
    {
        const char *ptr = input.c_str();
        uint cur_char = 1;
        ss = std::stringstream();

        while (*ptr != '\0')
        {
            while(*ptr == *(ptr + 1))
            {
                cur_char++;
                ptr++;
            }

            ss << cur_char << *ptr;
            cur_char = 1;
            ptr++;
        }

        input = ss.str();
    }

    cout << "length is: " << input.length() << endl;

    return 0;
}