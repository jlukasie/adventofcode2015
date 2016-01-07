#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static unsigned int smallest = 2999999999;
static unsigned int largest = 0;
static const vector<string> cities = { "Faerun", "Norrath", "Tristram", "AlphaCentauri", "Arbre", "Snowdin", "Tambi", "Straylight" };
static vector<string> city_perms = { };
static unordered_map<string, unsigned int> distances;

static const int NUM_CITIES;

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
            unsigned int distance = 0;
            // print out list
            for (int j = 0; j < perm.size() - 1; j++)
            {
                distance += distances[perm[j] + "_" + perm[j+1]];
                //cout << perm[j] << ", ";
            }
            if (smallest > distance)
            {
                smallest = distance;
            }

            if (largest < distance)
            {
                largest = distance;
            }
           // cout << endl;
        }

        perm.pop_back();
    }
}

int main()
{
    string city1 = "";
    string city2 = "";
    string junk = "";

    unsigned int distance = 0;

    // read in distances
    for (int i = 0; i < 28; i++)
    {
        // Faerun to Tristram = 58
        cin >> city1;
        cin >> junk;
        cin >> city2;
        cin >> junk;
        cin >> distance;

        // whatever order
        distances[city1 + "_" + city2] = distance;
        distances[city2 + "_" + city1] = distance;
    }

    // get all permutations and calculate shortest distance
    calculatePermutations(cities, city_perms);

    cout << "shortest distance: " << smallest << endl;
    cout << "largest distance: " << largest << endl;
    return 0;
}