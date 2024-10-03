#include <iostream>
#include <string>
#include "simple_validator.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)  
    {
        cerr << "Usage: " << argv[0] << " \"<XML string>\"" << endl;
        return 1;  
    }

    string input = argv[1];  

    cout << (DetermineXml(input) ? "Valid" : "Invalid") << endl;

    return 0;
}
