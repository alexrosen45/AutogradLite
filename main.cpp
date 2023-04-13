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

    // return Node's data attribute
    double getData() const
    {
        return data;
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

// return a new Node with data being
// the sum of two input Node's data
Node node_sum(const Node &node1, const Node &node2)
{
    double data = node1.getData() + node2.getData();
    Node node(data);
    return node;
}

int main(int argc, char *argv[])
{
    int data;

    cout << "Enter node's 'data'(double): ";
    cin >> data;

    Node node1(data);
    Node node2(data);
    Node node = node_sum(node1, node2);

    std::cout << static_cast<std::string>(node) << std::endl;
}