#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct ingredient
{
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

vector<ingredient> ingredients;
vector<int> amounts = {};
static int largest = 0;

void calculatePermutations(const vector<ingredient> ingredients, int amt_left)
{
    for (int i = 0; i <= amt_left; i++)
    {
        amounts.push_back(i);
        if (amounts.size() < 4)
        {
            calculatePermutations(ingredients, amt_left - i);
        }
        else
        {
            if (amounts[0] + amounts[1] + amounts[2] + amounts[3] == 100 && 
                (amounts[0] * ingredients[0].calories +
                amounts[1] * ingredients[1].calories + 
                amounts[2] * ingredients[2].calories + 
                amounts[3] * ingredients[3].calories) == 500)
            {
                int totalCapacity = 0;
                totalCapacity = max(0, ingredients[0].capacity * amounts[0] +
                    ingredients[1].capacity * amounts[1] +
                    ingredients[2].capacity * amounts[2] +
                    ingredients[3].capacity * amounts[3]);

                int totalDurability = max(0, ingredients[0].durability * amounts[0] +
                    ingredients[1].durability * amounts[1] +
                    ingredients[2].durability * amounts[2] +
                    ingredients[3].durability * amounts[3]);

                int totalFlavor = max(0, ingredients[0].flavor * amounts[0] +
                    ingredients[1].flavor * amounts[1] +
                    ingredients[2].flavor * amounts[2] +
                    ingredients[3].flavor * amounts[3]);

                int totalTexture = max(0, ingredients[0].texture * amounts[0] +
                    ingredients[1].texture * amounts[1] +
                    ingredients[2].texture * amounts[2] +
                    ingredients[3].texture * amounts[3]);

                if (totalDurability *totalFlavor * totalTexture *totalCapacity > largest)
                {
                    largest = totalDurability *totalFlavor * totalTexture *totalCapacity;
                }
            }
        }
        amounts.pop_back();
    }
}

int main()
{
    string junk;
    for (int i = 0; i < 4; i++)
    {
        ingredient ing = {};
        //Frosting: capacity 4, durability -2, flavor 0, texture 0, calories 5
        cin >> junk;
        cin >> junk;
        cin >> ing.capacity;
        cin >> junk;
        cin >> junk;
        cin >> ing.durability;
        cin >> junk;
        cin >> junk;
        cin >> ing.flavor;
        cin >> junk;
        cin >> junk;
        cin >> ing.texture;
        cin >> junk;
        cin >> junk;
        cin >> ing.calories;

        ingredients.push_back(ing);
    }

    calculatePermutations(ingredients, 100);

    cout << "largest: " << largest << endl;

    return 0;
}