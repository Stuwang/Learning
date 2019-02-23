#include <iostream>
#include <map>
#include <string>

void Call(int type) {
    if (auto l = sizeof(type); l == 4) {
        std::cout << "the len of int is " << 4 << std::endl;
    } else if (l == 8) {
        std::cout << "the len of int is " << 8 << std::endl;
    } else {
        std::cout << "the len of int is other" << std::endl;
    }
}

void for_map() {
    std::map<std::string, int> m;
    m["wangyuan"] = 1;
    m["wangyuan2"] = 2;
    for (auto[ key, value ] : m) {
        std::cout << "key " << key << " value " << value << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    for_map();
    return 0;
}