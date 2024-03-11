#include <iostream>
#include <list>
#include <chrono>

// helper function to print list
template<typename Iter>
void print(const Iter& begin, const Iter& end, bool new_line = true)
{
    std::for_each(begin, end, [](auto& i) { std::cout << i << " "; });
    if (new_line) {
        std::cout << std::endl;
    }
}

// partition function
template<typename Iter, typename Comparator>
Iter partitions(Iter begin, Iter end, Comparator compare) {
    // std::cout << "PARTITION "; print(begin, end);
    Iter pivot = std::prev(end);
    Iter i = begin;
    for (Iter j = begin; j != pivot; j++) {
        if (compare(*j, *pivot)) {
            std::swap(*i++, *j);
        }
    }
    std::swap(*i, *pivot);
    return i;
}

template<typename Iter, typename Comparator>
void quickSort(Iter begin, Iter end, Comparator compare) {
    // std::cout << "SORT "; print(begin, end);
    int size = std::distance(begin, end);
    if (size <= 1) return;
    Iter bound = partitions(begin, end, compare);
    quickSort(begin, bound, compare);
    quickSort(std::next(bound), end, compare);
}

template<typename Comparator>
void testSortedResult(Comparator compare) {
    std::list<int> l = {2, 5, 1, 7, 9, 2, 4, 3, 8, 11};
    std::cout << "Before sort: ";
    print(l.begin(), l.end());
    quickSort(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    print(l.begin(), l.end());
}

// timing test
void testSorted() {
    std::list<int> l;
    std::cout << "Experiment 1: Sorted Order\n";
    for (int i = 1; i <= 10000; ++i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testReverseSorted() {
    std::list<int> l;
    std::cout << "Experiment 2: Reverse Sorted Order\n";
    for (int i = 10000; i >= 1; --i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testRandom() {
    std::list<int> l;
    std::cout << "Experiment 3: Random Order\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(rand() % 10000);
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testAllDuplicates() {
    std::list<int> l;
    std::cout << "Experiment 4: All Duplicate Elements\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(42);
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    // test result
    std::cout << "Test Result: " << std::endl;

    std::cout << "Ascending Order:\n";
    testSortedResult(std::less<int>());

    std::cout << "Descending Order:\n";
    testSortedResult(std::greater<int>());

    std::cout << std::endl;

    // timing
    std::cout << "TIMING TESTS: " << std::endl;
    testSorted();
    testReverseSorted();
    testRandom();
    testAllDuplicates();
    return 0;
}