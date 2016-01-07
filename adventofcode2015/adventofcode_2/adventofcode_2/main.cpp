#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    int w = 0;
    int h = 0;
    int d = 0;
    int area = 0;
    int ribbon = 0;

    for (int i = 0; i < 1000; i++)
    {
        scanf_s("%dx%dx%d\n", &w, &h, &d);
        //cout << w << "x" << h << "x" << d << endl;
        area += (2 * w * h) + (2 * h * d) + (2 * w * d);
        area += min(w * h, min(h * d, w * d));

        // calculate ribbon
        int values[3] = { w, h, d };

        sort(values, values + 3, [](int a, int b) {return a < b; });

        int small1 = values[0];
        int small2 = values[1];

        ribbon += small1 + small1 + small2 + small2 + (w * h * d);
    }

    cout << "area: " << area << endl;
    cout << "ribbon: " << ribbon << endl;

    return 0;
}