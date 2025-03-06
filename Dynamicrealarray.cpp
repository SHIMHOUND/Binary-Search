#include <iostream>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <list>

class MyVector {
public:
    MyVector(int initial_capacity = 16) : size(0), capacity(initial_capacity) {
        data = new int[capacity];
    }

    ~MyVector() { delete[] data; }

    void push_back(int value) {
        if (size == capacity) {
            resize_array();
            std::cout << "Resized to " << capacity << std::endl; // Print when resize occurs.
        }
        data[size++] = value;
    }

    void resize(int new_size) {
        if (new_size > capacity) {
            while (new_size > capacity) {
                resize_array();
                std::cout << "Resized to " << capacity << std::endl; // Print when resize occurs.
            }
        }
        if (new_size < size) {
            size = new_size;
        }
    }

    int get_element(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    void set_element(int index, int value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        data[index] = value;
    }

    void erase(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void erase(int start_index, int end_index) {
        if (start_index < 0 || start_index >= size || end_index < 0 || end_index >= size || end_index < start_index) {
            throw std::out_of_range("Index out of bounds");
        }
        int num_elements = end_index - start_index + 1;
        for (int i = end_index + 1; i < size; i++) {
            data[i - num_elements] = data[i];
        }
        size -= num_elements;
    }

    int get_size() const {
        return size;
    }

private:
    int *data;
    int size;
    int capacity;

    void resize_array() {
        int new_capacity = capacity * 2;
        int *new_data = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

int main() {
    int num_elements = 100000;

    // Test MyVector
    MyVector myVector;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        myVector.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "MyVector append time: " << diff.count() << " s" << std::endl;


    // Test std::vector
    std::vector<int> stdVector;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        stdVector.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::vector append time: " << diff.count() << " s" << std::endl;

    // Test std::list
    std::list<int> myList;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_elements; ++i) {
        myList.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::list append time: " << diff.count() << " s" << std::endl;

    std::cout << "First element Myvector: " << myVector.get_element(0) << std::endl;
    myVector.set_element(0, 100);
    std::cout << "First element Myvector after setting it to 100: " << myVector.get_element(0) << std::endl;
    try {
        myVector.get_element(num_elements);
    } catch (std::out_of_range &e) {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }

    try {
        myVector.set_element(num_elements, 100);
    } catch (std::out_of_range &e) {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }

    std::cout << "Size before resize: " << myVector.get_element(myVector.get_size() - 1) << std::endl;
    myVector.resize(num_elements / 2);
    std::cout << "Size after resize: " << myVector.get_element(myVector.get_size() - 1) << std::endl;

    std::cout << "Size before erase: " << myVector.get_element(myVector.get_size() - 1) << std::endl;
    myVector.erase(myVector.get_size() - 1);
    std::cout << "Size after erase last element: " << myVector.get_element(myVector.get_size() - 1) << std::endl;


    std::cout << "Size before segment erase: " << myVector.get_element(myVector.get_size() - 1) << std::endl;
    myVector.erase(myVector.get_size() - 5, myVector.get_size() - 1);
    std::cout << "Size after segment erase: " << myVector.get_element(myVector.get_size() - 1) << std::endl;

    return 0;
}
