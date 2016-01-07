#include <iostream>
#include <string>

using namespace std;

int main()
{
    string in;
    cin >> in;
    int floor = 0;
    int negative_idx = 0;
    const char *ptr = in.c_str();

    for (int i = 0; i < in.size(); i++)
    {
        if (ptr[i] == '(')
        {
            floor++;
        }
        else
        {
            floor--;
        }

        if (floor < 0)
        {
            negative_idx = i;
            break;
        }
    }

    cout << negative_idx + 1 << endl;

    return 0;
}