#include <iostream>
#include <stdexcept>
#include <limits>

template <typename T>
class DynamicArray {
private:
    T* arrayData;
    size_t capacity;
    size_t currentSize;

    void resizeArray() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newArray = new T[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newArray[i] = arrayData[i];
        }
        delete[] arrayData;
        arrayData = newArray;
    }

public:
    DynamicArray() : arrayData(nullptr), capacity(0), currentSize(0) {}

    ~DynamicArray() {
        delete[] arrayData;
    }

    void addElement(const T& value) {
        if (currentSize == capacity) {
            resizeArray();
        }
        arrayData[currentSize++] = value;
    }

    T getElementAt(size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return arrayData[index];
    }

    size_t getSize() const {
        return currentSize;
    }

    T calculateSum() const {
        T total = 0;
        for (size_t i = 0; i < currentSize; ++i) {
            total += arrayData[i];
        }
        return total;
    }

    T findMax() const {
        if (currentSize == 0) {
            throw std::runtime_error("Array empty");
        }
        T maxValue = std::numeric_limits<T>::lowest();
        for (size_t i = 0; i < currentSize; ++i) {
            if (arrayData[i] > maxValue) {
                maxValue = arrayData[i];
            }
        }
        return maxValue;
    }

    T findMin() const {
        if (currentSize == 0) {
            throw std::runtime_error("Array empty");
        }
        T minValue = std::numeric_limits<T>::max();
        for (size_t i = 0; i < currentSize; ++i) {
            if (arrayData[i] < minValue) {
                minValue = arrayData[i];
            }
        }
        return minValue;
    }

    T* sliceArray(size_t startIndex, size_t endIndex) const {
        if (startIndex >= currentSize || endIndex >= currentSize || startIndex > endIndex) {
            throw std::out_of_range("Slice out of bounds");
        }
        size_t sliceSize = endIndex - startIndex + 1;
        T* slicedArray = new T[sliceSize];
        for (size_t i = 0; i < sliceSize; ++i) {
            slicedArray[i] = arrayData[startIndex + i];
        }
        return slicedArray;
    }
};

int main() {
    DynamicArray<int> numberArray;

    numberArray.addElement(15);
    numberArray.addElement(42);
    numberArray.addElement(27);
    numberArray.addElement(33);
    numberArray.addElement(12);
    numberArray.addElement(19);
    numberArray.addElement(81);
    numberArray.addElement(29);

    std::cout << "Array size: " << numberArray.getSize() << std::endl;
    std::cout << "Array sum: " << numberArray.calculateSum() << std::endl;
    std::cout << "Maximum value: " << numberArray.findMax() << std::endl;
    std::cout << "Minimum value: " << numberArray.findMin() << std::endl;

    int* slicedArray = numberArray.sliceArray(2, 5);
    std::cout << "Sliced array (indices 2 to 5): ";
    for (size_t i = 0; i < 4; ++i) {
        std::cout << slicedArray[i] << " ";
    }
    std::cout << std::endl;

    delete[] slicedArray;

    return 0;
}

