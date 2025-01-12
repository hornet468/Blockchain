#include "generateKey.hpp"
#include <iostream>

int main() {
    Key keyGen;
    std::string result = keyGen.createPairKey();
    std::cout << "Keys have been generated and saved in .hex files!" << std::endl;
    return 0;
}