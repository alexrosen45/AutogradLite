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

    // cast Node to string
    operator std::string() const
    {
        std::string str = "Node(data=";
        str += std::to_string(data);
        str += ")";
        return str;
    }
};

int main(int argc, char *argv[])
{
    int data;

    cout << "Enter node's 'data'(double): ";
    cin >> data;

    Node node(data);
    std::cout << static_cast<std::string>(node) << std::endl;
}