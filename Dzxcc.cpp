#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

template<typename T>
class BinaryHeap {
private:
    vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        if (left < (int)heap.size() && heap[left] < heap[smallest])
            smallest = left;
        
        if (right < (int)heap.size() && heap[right] < heap[smallest])
            smallest = right;
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
    int getHeight() {
        if (heap.empty()) return 0;
        return (int)log2((double)heap.size()) + 1;
    }
    
    void printSpaces(int count) {
        for (int i = 0; i < count; i++)
            cout << " ";
    }
    
    string toString(const T& val) {
        stringstream ss;
        ss << val;
        return ss.str();
    }
    
public:
    BinaryHeap() {}
    
    BinaryHeap(vector<T> arr) {
        buildHeap(arr);
    }
    
    void insert(T value) {
        heap.push_back(value);
        heapifyUp((int)heap.size() - 1);
    }
    
    T getMin() {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        return heap[0];
    }
    
    T getMax() {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        
        T maxVal = heap[0];
        for (int i = (int)heap.size() / 2; i < (int)heap.size(); i++) {
            if (heap[i] > maxVal)
                maxVal = heap[i];
        }
        return maxVal;
    }
    
    T extractMin() {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        
        T minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty())
            heapifyDown(0);
        
        return minVal;
    }
    
    T extractMax() {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        
        int maxIndex = 0;
        for (int i = (int)heap.size() / 2; i < (int)heap.size(); i++) {
            if (heap[i] > heap[maxIndex])
                maxIndex = i;
        }
        
        T maxVal = heap[maxIndex];
        
        heap[maxIndex] = heap.back();
        heap.pop_back();
        
        if (maxIndex < (int)heap.size()) {
            if (maxIndex > 0 && heap[parent(maxIndex)] > heap[maxIndex])
                heapifyUp(maxIndex);
            else
                heapifyDown(maxIndex);
        }
        
        return maxVal;
    }
    
    void decreaseKey(int index, T newValue) {
        if (index >= (int)heap.size())
            throw runtime_error("Index out of range");
        if (newValue > heap[index])
            throw runtime_error("New value is greater than current value");
        
        heap[index] = newValue;
        heapifyUp(index);
    }
    
    void increaseKey(int index, T newValue) {
        if (index >= (int)heap.size())
            throw runtime_error("Index out of range");
        if (newValue < heap[index])
            throw runtime_error("New value is smaller than current value");
        
        heap[index] = newValue;
        heapifyDown(index);
    }
    
    void buildHeap(vector<T> arr) {
        heap = arr;
        for (int i = (int)heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    void merge(BinaryHeap<T>& other) {
        for (T val : other.heap) {
            insert(val);
        }
    }
    
    int size() { return (int)heap.size(); }
    bool empty() { return heap.empty(); }
    
    void display() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        
        int height = getHeight();
        int maxWidth = (int)pow(2.0, height) * 4;
        
        vector<vector<string>> levels(height);
        
        for (int i = 0; i < (int)heap.size(); i++) {
            int level = (int)log2((double)(i + 1));
            levels[level].push_back(toString(heap[i]));
        }
        
        for (int i = 0; i < height; i++) {
            int spaces = maxWidth / (int)pow(2.0, i + 1);
            
            printSpaces(spaces);
            for (int j = 0; j < (int)levels[i].size(); j++) {
                cout << levels[i][j];
                if (j < (int)levels[i].size() - 1) {
                    printSpaces(spaces * 2);
                }
            }
            cout << endl << endl;
        }
    }
    
    void displayAsList() {
        cout << "Heap as list: [";
        for (int i = 0; i < (int)heap.size(); i++) {
            cout << heap[i];
            if (i < (int)heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    void displayDetailed() {
        cout << "\n========== HEAP STATUS ==========" << endl;
        cout << "Size: " << heap.size() << endl;
        if (!heap.empty()) {
            cout << "Min element: " << getMin() << endl;
            cout << "Max element: " << getMax() << endl;
        } else {
            cout << "Min element: N/A" << endl;
            cout << "Max element: N/A" << endl;
        }
        cout << "\nTree structure:" << endl;
        display();
        cout << "List representation:" << endl;
        displayAsList();
        cout << "================================\n" << endl;
    }
};

class Task {
public:
    string name;
    int priority;
    int id;
    
    Task(string n, int p, int i) : name(n), priority(p), id(i) {}
    
    bool operator<(const Task& other) const {
        return priority > other.priority;
    }
    
    bool operator>(const Task& other) const {
        return priority < other.priority;
    }
    
    friend ostream& operator<<(ostream& os, const Task& task) {
        os << task.name << "(" << task.priority << ")";
        return os;
    }
};

int main() {
    srand((unsigned int)time(nullptr));
    
    BinaryHeap<int> heap;
    
    cout << "1. Добавление элементов: 10, 5, 15, 3, 8, 20" << endl;
    heap.insert(10);
    heap.insert(5);
    heap.insert(15);
    heap.insert(3);
    heap.insert(8);
    heap.insert(20);
    heap.displayDetailed();
    
    cout << "2. Поиск min и max" << endl;
    cout << "Min: " << heap.getMin() << endl;
    cout << "Max: " << heap.getMax() << endl << endl;
    
    cout << "3. Удаление min" << endl;
    heap.extractMin();
    heap.displayDetailed();
    
    cout << "4. Удаление max" << endl;
    heap.extractMax();
    heap.displayDetailed();
    
    cout << "5. Уменьшение значения" << endl;
    heap.decreaseKey(1, 2);
    heap.displayDetailed();
    
    cout << "6. Увеличение значения" << endl;
    heap.increaseKey(2, 25);
    heap.displayDetailed();
    
    cout << "7. Слияние куч" << endl;
    BinaryHeap<int> heap2;
    heap2.insert(30);
    heap2.insert(25);
    heap2.insert(35);
    heap.merge(heap2);
    heap.displayDetailed();
    
    cout << "8. Построение кучи из массива" << endl;
    vector<int> arr = {7, 12, 4, 9, 6};
    BinaryHeap<int> heap3(arr);
    heap3.displayDetailed();
    
    cout << "\n=== ПРАКТИЧЕСКИЙ ПРИМЕР: СИСТЕМА ЗАДАЧ ===\n" << endl;
    
    BinaryHeap<Task> taskHeap;
    
    taskHeap.insert(Task("Срочный баг-фикс", 1, 1));
    taskHeap.insert(Task("Написать документацию", 3, 2));
    taskHeap.insert(Task("Провести код-ревью", 2, 3));
    taskHeap.insert(Task("Деплой", 1, 4));
    
    taskHeap.displayDetailed();
    
    cout << "Выполнение задач по приоритету:" << endl;
    int num = 1;
    while (!taskHeap.empty()) {
        Task t = taskHeap.getMin();
        cout << num++ << ". " << t << endl;
        taskHeap.extractMin();
    }
    
    return 0;
}
