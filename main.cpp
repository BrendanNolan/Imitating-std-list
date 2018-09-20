#include <iostream>
#include "Lst.h"
int main()
{
    Lst<int> my_Lst;

    my_Lst.push_back(10);
    my_Lst.push_back(20);
    my_Lst.push_back(40);
    my_Lst.push_back(50);
    my_Lst.push_back(60);
    Lst<int>::iterator it = my_Lst.begin();

    Lst<int>::iterator it1 = it;
    ++(++it1);
    my_Lst.insert(it1, 30);
    my_Lst.pop_back();

    std::cout << "my_Lst.size(): " << my_Lst.size() << std::endl;
    for (Lst<int>::size_type i = 0; i < my_Lst.size(); ++i)
        std::cout << *(it++) << std::endl;
    Lst<int> cpy_my_Lst(my_Lst);
    it = cpy_my_Lst.begin();
    std::cout << "cpy_my_Lst.size(): " << cpy_my_Lst.size() << std::endl;
    for (Lst<int>::size_type i = 0; i < cpy_my_Lst.size(); ++i)
        std::cout << *(it++) << std::endl;
    cpy_my_Lst.pop_back();
    cpy_my_Lst.pop_back();
    cpy_my_Lst.erase(cpy_my_Lst.begin());
    my_Lst = cpy_my_Lst;
    it = my_Lst.begin();
    std::cout << "my_Lst.size(): " << my_Lst.size() << std::endl;
    for (Lst<int>::size_type i = 0; i < my_Lst.size(); ++i)
        std::cout << *(it++) << std::endl;

    std::cin.get(); // keeps output window open until you press Enter
                    // (useful if writing code in Visual Studio)
}