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

    // sum two Node's data
    Node node_sum(const Node &node)
    {
        double new_data = data + node.getData();
        Node new_node(new_data);
        return new_node;
    }

    // multiply two Node's data
    Node node_product(const Node &node)
    {
        double new_data = data * node.getData();
        Node new_node(new_data);
        return new_node;
    }
};

int main(int argc, char *argv[])
{
    int data;

    cout << "Enter node's 'data'(double): ";
    cin >> data;

    Node node1(data);
    Node node2(data);
    Node node = node1.node_product(node2);

    std::cout << static_cast<std::string>(node) << std::endl;
}