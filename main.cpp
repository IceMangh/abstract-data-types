#include <iostream>
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Tests.h"

void PrintSequence(const Sequence<int>& seq) {
    for (int i = 0; i < seq.GetLength(); ++i) {
        std::cout << seq.Get(i) << ' ';
    }
    std::cout << "\n";
}

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== LAB 2 MENU ===\n";
        std::cout << "1. Run tests\n";
        std::cout << "2. Demo ArraySequence\n";
        std::cout << "3. Demo ListSequence\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            RunAllTests();
        } else if (choice == 2) {
            int data[] = {1, 2, 3};
            ArraySequence<int> seq(data, 3);
            seq.Append(4)->Prepend(0)->InsertAt(99, 2);
            std::cout << "ArraySequence: ";
            PrintSequence(seq);
        } else if (choice == 3) {
            int data[] = {1, 2, 3};
            ListSequence<int> seq(data, 3);
            seq.Append(4)->Prepend(0)->InsertAt(99, 2);
            std::cout << "ListSequence: ";
            PrintSequence(seq);
        } else if (choice != 0) {
            std::cout << "Unknown menu item\n";
        }
    }

    return 0;
}
