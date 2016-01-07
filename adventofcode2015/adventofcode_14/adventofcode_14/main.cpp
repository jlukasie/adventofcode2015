#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

enum STATE
{
    RESTING,
    FLYING
};
struct ReindeerState
{
    STATE state;
    string name;
    uint v;
    uint t;
    uint r;
    uint cur_v;
    uint cur_r;
    uint cur_t;
    uint pos;
    uint points;
};

int main()
{
    uint target_time = 2503;
    vector<ReindeerState> reindeers;
    string junk;
    string winner = "";
    uint winning_pos = 0;
    uint cur_winner_pos = 0;
    
    // read in inputs
    for (int i = 0; i < 9; i++)
    {
        ReindeerState rs{ FLYING, "", 0, 0, 0, 0, 0, 0, 0, 0 };

        //Vixen can fly 19 km/s for 7 seconds, but then must rest for 124 seconds.
        cin >> rs.name;
        cin >> junk;
        cin >> junk;
        cin >> rs.v;
        cin >> junk;
        cin >> junk;
        cin >> rs.t;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> rs.r;
        cin >> junk;

        rs.cur_r = rs.r;
        rs.cur_v = rs.v;
        rs.cur_t = rs.t;
        reindeers.push_back(rs);
    }

    while (target_time--)
    {
        for (int i = 0; i < reindeers.size(); i++)
        {
            if (reindeers[i].cur_t > 0)
            {
                reindeers[i].cur_t--;
                reindeers[i].pos += reindeers[i].v;
            }
            else if (reindeers[i].cur_r > 0)
            {
                reindeers[i].cur_r--;

                if (reindeers[i].cur_r == 0)
                {
                    reindeers[i].cur_v = reindeers[i].v;
                    reindeers[i].cur_t = reindeers[i].t;
                    reindeers[i].cur_r = reindeers[i].r;
                }
            }
        }

        //get max
        for (int i = 0; i < 9; i++)
        {
            if (reindeers[i].pos > cur_winner_pos)
            {
                cur_winner_pos = reindeers[i].pos;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (reindeers[i].pos == cur_winner_pos)
            {
                reindeers[i].points++;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (reindeers[i].points > winning_pos)
        {
            winning_pos = reindeers[i].points;
            winner = reindeers[i].name;
        }
    }

    cout << "winner: " << winning_pos << endl;

    return 0;
}