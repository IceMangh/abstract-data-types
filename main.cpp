#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "ArraySequence.h"
#include "ImmutableArraySequence.h"
#include "ListSequence.h"
#include "Tests.h"

int ReadInt(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cout << "Ошибка ввода. Нужно целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::vector<int> ReadElements() {
    const int length = ReadInt("Введите длину последовательности: ");
    if (length < 0) {
        throw std::invalid_argument("Длина не может быть отрицательной");
    }

    std::vector<int> values(length);
    for (int i = 0; i < length; ++i) {
        values[i] = ReadInt("Элемент [" + std::to_string(i) + "]: ");
    }

    return values;
}

template <class SequenceType>
SequenceType BuildSequence(const std::vector<int>& values) {
    if (values.empty()) {
        return SequenceType();
    }

    return SequenceType(values.data(), static_cast<int>(values.size()));
}

template <class SequenceType>
void PrintSequence(const SequenceType& seq, const std::string& title) {
    std::cout << title << ": [";
    for (int i = 0; i < seq.GetLength(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << seq.Get(i);
    }
    std::cout << "]\n";
}

template <class SequenceType>
void PrintCommonInfo(const SequenceType& seq) {
    std::cout << "Длина: " << seq.GetLength() << '\n';
    if (seq.GetLength() == 0) {
        std::cout << "Последовательность пустая\n";
        return;
    }

    std::cout << "Первый элемент: " << seq.GetFirst() << '\n';
    std::cout << "Последний элемент: " << seq.GetLast() << '\n';
}

void ShowAlgorithms(const Sequence<int>& seq) {
    Sequence<int>* mapped = seq.Map(Double);
    PrintSequence(*mapped, "Map(x2)");
    delete mapped;

    std::cout << "Reduce(sum): " << seq.Reduce(Sum, 0) << '\n';

    if (seq.GetLength() >= 2) {
        Sequence<int>* sub = seq.GetSubsequence(0, seq.GetLength() - 2);
        PrintSequence(*sub, "Subsequence(0, n-2)");
        delete sub;
    }
}

void DemoMutableArraySequence() {
    std::cout << "\n=== Mutable ArraySequence ===\n";
    ArraySequence<int> sequence = BuildSequence<ArraySequence<int>>(ReadElements());
    PrintSequence(sequence, "Исходная последовательность");

    const int appendValue = ReadInt("Значение для Append: ");
    sequence.Append(appendValue);
    PrintSequence(sequence, "После Append");

    const int prependValue = ReadInt("Значение для Prepend: ");
    sequence.Prepend(prependValue);
    PrintSequence(sequence, "После Prepend");

    const int insertValue = ReadInt("Значение для InsertAt: ");
    const int insertIndex = ReadInt("Индекс для InsertAt (0.." + std::to_string(sequence.GetLength()) + "): ");
    sequence.InsertAt(insertValue, insertIndex);
    PrintSequence(sequence, "После InsertAt");

    PrintCommonInfo(sequence);
    ShowAlgorithms(sequence);
    std::cout << "Вывод: mutable-версия меняет исходный объект.\n";
}

void DemoImmutableArraySequence() {
    std::cout << "\n=== Immutable ArraySequence ===\n";
    ImmutableArraySequence<int> original = BuildSequence<ImmutableArraySequence<int>>(ReadElements());
    PrintSequence(original, "Исходная последовательность");

    const int appendValue = ReadInt("Значение для Append: ");
    Sequence<int>* appended = original.Append(appendValue);
    PrintSequence(original, "Исходный объект после Append");
    PrintSequence(*appended, "Новый объект после Append");

    const int prependValue = ReadInt("Значение для Prepend: ");
    Sequence<int>* prepended = appended->Prepend(prependValue);
    PrintSequence(*appended, "Предыдущий объект после Prepend");
    PrintSequence(*prepended, "Новый объект после Prepend");

    const int insertValue = ReadInt("Значение для InsertAt: ");
    const int insertIndex = ReadInt("Индекс для InsertAt (0.." + std::to_string(prepended->GetLength()) + "): ");
    Sequence<int>* inserted = prepended->InsertAt(insertValue, insertIndex);
    PrintSequence(*prepended, "Предыдущий объект после InsertAt");
    PrintSequence(*inserted, "Новый объект после InsertAt");

    PrintCommonInfo(*inserted);
    ShowAlgorithms(*inserted);
    std::cout << "Вывод: immutable-версия не меняет исходный объект, а возвращает новую последовательность.\n";

    delete appended;
    delete prepended;
    delete inserted;
}



void DemoMutableListSequence() {
    std::cout << "\n=== Mutable ListSequence ===\n";
    ListSequence<int> sequence = BuildSequence<ListSequence<int>>(ReadElements());
    PrintSequence(sequence, "Исходная последовательность");

    const int appendValue = ReadInt("Значение для Append: ");
    sequence.Append(appendValue);
    PrintSequence(sequence, "После Append");

    const int prependValue = ReadInt("Значение для Prepend: ");
    sequence.Prepend(prependValue);
    PrintSequence(sequence, "После Prepend");

    const int insertValue = ReadInt("Значение для InsertAt: ");
    const int insertIndex = ReadInt("Индекс для InsertAt (0.." + std::to_string(sequence.GetLength()) + "): ");
    sequence.InsertAt(insertValue, insertIndex);
    PrintSequence(sequence, "После InsertAt");

    PrintCommonInfo(sequence);
    ShowAlgorithms(sequence);
    std::cout << "Вывод: ListSequence в этом проекте реализована как mutable-структура.\n";
}

void PrintMenu() {
    std::cout << "\n========== МЕНЮ ==========\n";
    std::cout << "1. Запустить тесты\n";
    std::cout << "2. Демонстрация mutable ArraySequence\n";
    std::cout << "3. Демонстрация immutable ArraySequence\n";
    std::cout << "4. Демонстрация mutable ListSequence\n";
    std::cout << "0. Выход\n";
}

int main() {
    bool isRunning = true;

    while (isRunning) {
        try {
            PrintMenu();
            const int choice = ReadInt("Выберите пункт: ");

            switch (choice) {
                case 1:
                    RunAllTests();
                    break;
                case 2:
                    DemoMutableArraySequence();
                    break;
                case 3:
                    DemoImmutableArraySequence();
                    break;
                case 4:
                    DemoMutableListSequence();
                    break;
                case 0:
                    isRunning = false;
                    break;
                default:
                    std::cout << "Неизвестный пункт меню\n";
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }

    return 0;
}
