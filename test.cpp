#include <iostream>
#include <vector>
#include "skiplist.h"

int main() {
    std::vector<int> numbers;
    for (int i = 0; i < 10; i++) {
        int r = rand() % 0xffff;
        numbers.push_back(r);
    }

    SkipList<int, int> skip_list(5);
    for (int i : numbers) {
        std::cout << "Insert:" << i << std::endl;
        skip_list.Insert(i, i);
        std::cout << skip_list.ToString() << std::endl;
    }

    auto* node = skip_list.Search(numbers[5]);
    std::cout << node->value() << std::endl;

    for (int i : numbers) {
        std::cout << "Remove:" << i << std::endl;
        skip_list.Remove(i);
        std::cout << skip_list.ToString() << std::endl;
    }

    std::cout << "finish" << std::endl;
    return 0;
}
