#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
private:
    double data;

public:
    Node(double data)
    {
        this->data = data;
    }

    std::string repr() const
    {
        std::string str = "Node(data=";
        str += std::to_string(data);
        str += ")";
        return str;
    }
};