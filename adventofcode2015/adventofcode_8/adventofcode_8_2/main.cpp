#include <iostream>
#include <string>
#include <cassert>

using namespace std;

static unsigned int code_char;
static unsigned int string_char;
static unsigned int new_encoded_code;
static unsigned int new_encoded_string;

static const unsigned int num_strings = 300;

int main()
{
    string str;
    const char *ptr = 0;
    for (int i = 0; i < num_strings; i++)
    {
        cin >> str;
        ptr = str.c_str();

        code_char += 2;
        new_encoded_code += 6;

        while (*ptr != '\0')
        {
            if (*ptr == '\\')
            {
                if (*(ptr + 1) == '\\') 
                {
                    code_char += 2;
                    new_encoded_code += 4;
                    string_char += 1;
                    ptr += 2;
                }
                else if (*(ptr + 1) == '"')
                {
                    code_char += 2;
                    new_encoded_code += 4;
                    string_char += 1;
                    ptr += 2;
                }
                else if (*(ptr + 1) == 'x')
                {
                    code_char += 4;
                    new_encoded_code += 5;
                    string_char += 1;
                    ptr += 4;
                }
                else
                {
                    assert(!"string escape parse error!\n");
                }
            }
            else
            {
                code_char += 1;
                new_encoded_code += 1;
                string_char += 1;
                ptr++;
            }
        }
    }

    cout << "result is " << new_encoded_code - code_char << endl;
    return 0;
}