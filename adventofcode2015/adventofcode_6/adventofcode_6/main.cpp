#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

enum OP {
    ON = 0,
    OFF,
    TOGGLE
};

void op(char *lights, OP op, int x1, int y1, int x2, int  y2)
{
    for (int y = y1; y <= y2; y++)
    {
        for (int x = x1; x <= x2; x++)
        {
            switch (op)
            {
            case ON:
                assert(lights[y * 1000 + x] < 255);
                lights[y * 1000 + x] += 1;
                break;
            case OFF:
                lights[y * 1000 + x] = max(0, lights[y * 1000 + x] - 1);
                break;
            case TOGGLE:
                assert(lights[y * 1000 + x] < 255);
                lights[y * 1000 + x] += 2;
                break;
            }
        }
    }
}

int main()
{
    char* light = new char[1000 * 1000];
    memset(light, 0, 1000 * 1000);

    string instruction;
    int firstx = 0;
    int firsty = 0;
    int secondx = 0;
    int secondy = 0;
    int final_cnt = 0;

    for (int i = 0; i < 300; i++)
    {
        cin >> instruction;

        if (instruction == "turn")
        {
            cin >> instruction;

            if (instruction == "on")
            {
                scanf_s("%d,%d", &firstx, &firsty);
                cin >> instruction; // junk
                scanf_s("%d,%d", &secondx, &secondy);

                op(light, ON, firstx, firsty, secondx, secondy);
            }
            else
            {
                scanf_s("%d,%d", &firstx, &firsty);
                cin >> instruction; // junk
                scanf_s("%d,%d", &secondx, &secondy);
                op(light, OFF, firstx, firsty, secondx, secondy);
            }
        }
        else // toggle
        {
            scanf_s("%d,%d", &firstx, &firsty);
            cin >> instruction; // junk
            scanf_s("%d,%d", &secondx, &secondy);
            op(light, TOGGLE, firstx, firsty, secondx, secondy);
        }
    }

    for (int i = 0; i < 1000 * 1000; i++)
    {
        final_cnt += light[i];
    }

    cout << final_cnt << endl;
    return 0;
}