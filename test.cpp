#include <iostream>
#include "linked_hash.hpp"

int main() {
    linked_hash myhash;
    std::string key = "hash";
    std::string value = "hello hash";
    std::cout << myhash.install(key, value) << std::endl;
    
    return 0;
}