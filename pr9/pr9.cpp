#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() > 1) {
            std::vector<int> left(array.begin(), array.begin() + array.size() / 2);
            std::vector<int> right(array.begin() + array.size() / 2, array.end());

            
            std::thread left_thread(&MergeSort::Sort, this, std::ref(left));
            std::thread right_thread(&MergeSort::Sort, this, std::ref(right));

            left_thread.join();
            right_thread.join();

            
            Merge(array, left, right);
        }
    }

private:
    void Merge(std::vector<int>& array, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            array[k++] = left[i++];
        }
        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    std::vector<int> array(10);
    std::cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> array[i];
    }

    
    MergeSort sorter;

    
    auto sort_func = [&sorter](std::vector<int>& arr) {
        sorter.Sort(arr);
        };

    
    std::thread sort_thread(sort_func, std::ref(array));
    sort_thread.join(); 

    
    std::cout << "Отсортированный массив: ";
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
