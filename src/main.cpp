#include "List.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    List<int> list(2);

    list.append(1);
    list.append(2);
    list.append(3);

    List<int> list2(3);

    list2.append(4);
    list2.append(5);

    list.extend(list2);

    std::cout << list.size() << std::endl;

    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << std::endl;
    }

    return 0;
}
