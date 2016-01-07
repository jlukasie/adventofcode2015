#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;

enum GATE_TYPE
{
    INPUT = 0,
    RSHIFT,
    LSHIFT,
    AND,
    OR,
    NOT,
    NUM_GATE_TYPES
};

struct Gate
{
    GATE_TYPE type;
    string input1;
    string input2;
    string output;
};

static const char Num_Inputs[NUM_GATE_TYPES] = { 1, 2, 2, 2, 2, 1 };
static const unsigned int NUM_GATES = 339;
Gate gates[NUM_GATES];

unsigned int getValue(string wire)
{
    unsigned int output_val = 0;
    stringstream ss;
    // if immediate value just return it
    if (wire.c_str()[0] >= '0' && wire.c_str()[0] <= '9')
    {
        return atoi(wire.c_str());
    }

    // find the gate
    for (int i = 0; i < NUM_GATES; i++)
    {
        if (gates[i].output == wire)
        {
            if (Num_Inputs[gates[i].type] == 1)
            {
                unsigned int value = getValue(gates[i].input1);
                ss << value;
                gates[i].input1 = ss.str();
                ss = std::stringstream();

                switch (gates[i].type)
                {
                case NOT:
                    output_val = ~value;
                    break;
                case INPUT:
                    output_val = value;
                    break;
                default:
                    assert(!"Error in single input gate getValue()");
                }
            }
            else
            {
                unsigned int value1 = getValue(gates[i].input1);
                ss << value1;
                gates[i].input1 = ss.str();
                ss = std::stringstream();

                unsigned int value2 = getValue(gates[i].input2);
                ss << value2;
                gates[i].input2 = ss.str();
                ss = std::stringstream();

                switch (gates[i].type)
                {
                case RSHIFT:
                    output_val = value1 >>= value2;
                    break;
                case LSHIFT:
                    output_val = value1 <<= value2;
                    break;
                case AND:
                    output_val = value1 & value2;
                    break;
                case OR:
                    output_val = value1 | value2;
                    break;
                default:
                    assert(!"Error in dual input gate getValue()");
                }
            }
            break;
        }
    }

   // cout << "value of wire " << wire << " is: " << output_val << endl;
    return output_val & 0x0000FFFF;
}

int main()
{
    // read in gates
    string in1 = "";
    string in2 = "";
    string in3 = "";

    for (int i = 0; i < NUM_GATES; i++)
    {
        cin >> in1;

        if (in1 == "NOT")
        {
            // input
            cin >> in1;

            // skip "->"
            cin >> in2;

            // output
            cin >> in2;
            gates[i] = { NOT, in1, "", in2 };
        }
        else if (in1.c_str()[0] >= '0' && in1.c_str()[0] <= 'z')
        {
            cin >> in2;

            // input type

            if (in2 == "->")
            {
                // read in output
                cin >> in2;

                gates[i] = { INPUT, in1, "", in2 };
            }
            else if (in2 == "AND")
            {
                cin >> in2;

                // read in "->"
                cin >> in3;

                // read in output
                cin >> in3;

                gates[i] = { AND, in1, in2, in3 };
            }
            else if (in2 == "OR")
            {
                cin >> in2;

                // read in "->"
                cin >> in3;

                // read in output
                cin >> in3;

                gates[i] = { OR, in1, in2, in3 };
            }
            else if (in2 == "LSHIFT")
            {
                cin >> in2;

                // skip "->"
                cin >> in3;

                cin >> in3;

                gates[i] = { LSHIFT, in1, in2, in3 };
            }
            else if (in2 == "RSHIFT")
            {
                cin >> in2;

                // skip "->"
                cin >> in3;

                cin >> in3;

                gates[i] = { RSHIFT, in1, in2, in3 };
            }
            else
            {
                assert(!"parse error");
            }           
        }
    }

    cout << "value of a is " << getValue("a") << endl;

    return 0;
}