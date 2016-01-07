#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>
#include <sstream>

using namespace std;

struct node
{
    node()
        : north(0), south(0), east(0), west(0)
    {

    }
    struct node* north;
    struct node* south;
    struct node* east;
    struct node* west;
};

string make_key(int x, int y)
{
    stringstream ss;
    ss << x << "_" << y;
    return ss.str();
}

void update_dir(const char *ptr, int &x, int &y)
{
    switch (*ptr)
    {
    case '^':
        y++;
        break;
    case 'v':
        y--;
        break;
    case '>':
        x++;
        break;
    case '<':
        x--;
        break;
    default:
        assert(!"invalid character!\n");
    }
}

int main()
{
    int x = 0;
    int y = 0;

    int rx = 0;
    int ry = 0;

    unsigned int idx = 1;

    string in;
    cin >> in;

    unordered_map<string, bool> visited_house;

    visited_house[make_key(x, y)] = true;

    const char* ptr = in.c_str();

    while (*ptr != '\0')
    {
        cout << *ptr << endl;
        
        if (idx % 2)
        {
            update_dir(ptr, x, y);
            visited_house[make_key(x, y)] = true;
        }
        else
        {
            update_dir(ptr, rx, ry);
            visited_house[make_key(rx, ry)] = true;
        }

        idx++;
        ptr++;
    }

    cout << visited_house.size() << endl;

    return 0;
}