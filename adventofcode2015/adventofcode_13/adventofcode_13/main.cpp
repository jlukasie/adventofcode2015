#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static int smallest = 2000000000;
static int largest = 0;
static const vector<string> people = { "Alice", "Bob", "Carol", "David", "Eric", "Frank", "George", "Mallory", "John" };
static vector<string> people_perms = {};
static unordered_map<string, int> happinesses;

static const int NUM_GUESTS = 4;

void calculatePermutations(const vector<string> list, vector<string> perm)
{
    for (int i = 0; i < list.size(); i++)
    {
        perm.push_back(list[i]);

        if (list.size() > 1)
        {
            vector<string> list_minus_one = list;
            list_minus_one.erase(list_minus_one.begin() + i);
            calculatePermutations(list_minus_one, perm);
        }
        else
        {
            int happiness = 0;
            // print out list
            for (int j = 0; j < perm.size() - 1; j++)
            {
                happiness += happinesses[perm[j] + "_" + perm[j + 1]];
                happiness += happinesses[perm[j+1] + "_" + perm[j]];
                //cout << perm[j] << ", ";
            }

            happiness += happinesses[perm[0] + "_" + perm[perm.size() - 1]];
            happiness += happinesses[perm[perm.size() - 1] + "_" + perm[0]];

            if (smallest > happiness)
            {
                smallest = happiness;
            }

            if (largest < happiness)
            {
                largest = happiness;
            }
            //cout << perm[perm.size()-1] << " happiness: " << happiness << endl;
        }

        perm.pop_back();
    }
}

int main()
{
    string person1 = "";
    string person2 = "";
    int happiness = 0;
    string junk = "";
    string sign = "";

    // read in happinesses
    for (int i = 0; i < 56; i++)
    {
        // Alice would gain 54 happiness units by sitting next to Bob.
        cin >> person1;
        cin >> junk;
        cin >> sign;
        cin >> happiness;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> junk;
        cin >> person2;

        if (sign == "lose")
        {
            happiness *= -1;
        }

        happinesses[person1 + "_" + person2] = happiness;

        cout << person1 << " " << person2 << ": " << happiness << endl;;
    }

    // get all permutations and calculate shortest distance
    calculatePermutations(people, people_perms);

    cout << "smallest happiness: " << smallest << endl;
    cout << "largest happiness: " << largest << endl;
    return 0;
}