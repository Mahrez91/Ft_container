#include <map>
#include "map.hpp"
#include <iostream>

int	main()
{
    std::map<std::string, int> trezor;
    trezor["z"] = 15;
    trezor["e"] = 15;
    trezor["c"] = 18;
    trezor["u"] = 15;
    trezor["x"] = 15;
    trezor["c"] = 10;
    trezor["o"] = 15;
    trezor["a"] = 15;
    trezor["b"] = 10;
    std::map<std::string, int>::iterator it = trezor.begin();
    std::map<std::string, int>::iterator ite = trezor.end();
    while (it != ite)
    {    
        std::cout <<  it->first << std::endl;
        it++;
    }
    trezor.max_size();
    std::cout << trezor.max_size() << std::endl;
    std::cout << "---------------------our--------------------\n";
    ft::map<std::string, int> trezor1;
    trezor1["z"] = 15;
    trezor1["e"] = 15;
    trezor1["c"] = 10;
    trezor1["u"] = 15;
    trezor1["x"] = 15;
    trezor1["c"] = 10;
    trezor1["o"] = 15;
    trezor1["a"] = 15;
    trezor1["b"] = 10;
    ft::map<std::string, int>::iterator it1 = trezor1.begin();
    ft::map<std::string, int>::iterator ite1 = trezor1.end();
    while (it1 != ite1)
    {   
        std::cout <<  it1->first << std::endl;
        it1++;
    } 
    std::cout << trezor1.max_size() << std::endl;
    trezor1.display_map();
    return 0;
}