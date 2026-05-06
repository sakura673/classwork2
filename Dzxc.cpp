#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

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
        
        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
    int getHeight() {
        return (int)log2(heap.size()) + 1;
    }
    
    void printSpaces(int count) {
        for (int i = 0; i < count; i++)
            cout << " ";
    }
    
public:
    BinaryHeap() {}
    
    BinaryHeap(vector<T> arr) {
        buildHeap(arr);
    }
    
    void insert(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
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
        for (int i = heap.size() / 2; i < heap.size(); i++) {
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
        for (int i = heap.size() / 2; i < heap.size(); i++) {
            if (heap[i] > heap[maxIndex])
                maxIndex = i;
        }
        
        T maxVal = heap[maxIndex];
        
        heap[maxIndex] = heap.back();
        heap.pop_back();
        
        if (maxIndex < heap.size()) {
            if (maxIndex > 0 && heap[parent(maxIndex)] > heap[maxIndex])
                heapifyUp(maxIndex);
            else
                heapifyDown(maxIndex);
        }
        
        return maxVal;
    }
    
    void decreaseKey(int index, T newValue) {
        if (index >= heap.size())
            throw runtime_error("Index out of range");
        if (newValue > heap[index])
            throw runtime_error("New value is greater than current value");
        
        heap[index] = newValue;
        heapifyUp(index);
    }
    
    void increaseKey(int index, T newValue) {
        if (index >= heap.size())
            throw runtime_error("Index out of range");
        if (newValue < heap[index])
            throw runtime_error("New value is smaller than current value");
        
        heap[index] = newValue;
        heapifyDown(index);
    }
    
    void buildHeap(vector<T> arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    void merge(BinaryHeap<T>& other) {
        for (T val : other.heap) {
            insert(val);
        }
    }
    
    int size() { return heap.size(); }
    bool empty() { return heap.empty(); }
    
    void display() {
        if (heap.empty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        
        int height = getHeight();
        int maxWidth = pow(2, height) * 4;
        
        vector<vector<string>> levels(height);
        
        for (int i = 0; i < heap.size(); i++) {
            int level = log2(i + 1);
            levels[level].push_back(to_string(heap[i]));
        }
        
        for (int i = 0; i < height; i++) {
            int spaces = maxWidth / pow(2, i + 1);
            
            printSpaces(spaces);
            for (int j = 0; j < levels[i].size(); j++) {
                cout << levels[i][j];
                if (j < levels[i].size() - 1) {
                    printSpaces(spaces * 2);
                }
            }
            cout << endl << endl;
        }
    }
    
    void displayAsList() {
        cout << "Heap as list: [";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i];
            if (i < heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    void displayDetailed() {
        cout << "\n========== HEAP STATUS ==========" << endl;
        cout << "Size: " << heap.size() << endl;
        cout << "Min element: " << (heap.empty() ? "N/A" : to_string(getMin())) << endl;
        cout << "Max element: " << (heap.empty() ? "N/A" : to_string(getMax())) << endl;
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

void demonstrateHeap() {
    cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ КУЧИ ===\n" << endl;
    
    BinaryHeap<int> heap;
    
    cout << "1. Добавление элементов: 10, 5, 15, 3, 8, 20" << endl;
    heap.insert(10);
    heap.insert(5);
    heap.insert(15);
    heap.insert(3);
    heap.insert(8);
    heap.insert(20);
    heap.displayDetailed();
    
    cout << "2. Поиск минимального и максимального элементов" << endl;
    cout << "Min: " << heap.getMin() << endl;
    cout << "Max: " << heap.getMax() << endl << endl;
    
    cout << "3. Удаление минимального элемента" << endl;
    int minVal = heap.extractMin();
    cout << "Удален: " << minVal << endl;
    heap.displayDetailed();
    
    cout << "4. Удаление максимального элемента" << endl;
    int maxVal = heap.extractMax();
    cout << "Удален: " << maxVal << endl;
    heap.displayDetailed();
    
    cout << "5. Изменение значений" << endl;
    cout << "Уменьшаем элемент на позиции 1 с 8 до 2" << endl;
    heap.decreaseKey(1, 2);
    heap.displayDetailed();
    
    cout << "Увеличиваем элемент на позиции 2 с 10 до 25" << endl;
    heap.increaseKey(2, 25);
    heap.displayDetailed();
    
    cout << "6. Слияние куч" << endl;
    BinaryHeap<int> heap2;
    heap2.insert(30);
    heap2.insert(25);
    heap2.insert(35);
    cout << "Вторая куча: ";
    heap2.displayAsList();
    
    heap.merge(heap2);
    cout << "После слияния:" << endl;
    heap.displayDetailed();
    
    cout << "7. Построение кучи из массива [7, 12, 4, 9, 6]" << endl;
    vector<int> arr = {7, 12, 4, 9, 6};
    BinaryHeap<int> heap3(arr);
    heap3.displayDetailed();
}

void taskManagerExample() {
    cout << "\n=== ПРАКТИЧЕСКИЙ ПРИМЕР: СИСТЕМА УПРАВЛЕНИЯ ЗАДАЧАМИ ===\n" << endl;
    
    BinaryHeap<Task> taskHeap;
    int nextId = 1;
    
    cout << "Добавление задач:" << endl;
    taskHeap.insert(Task("Срочный баг-фикс", 1, nextId++));
    cout << "  + Срочный баг-фикс (приоритет 1)" << endl;
    
    taskHeap.insert(Task("Написать документацию", 3, nextId++));
    cout << "  + Написать документацию (приоритет 3)" << endl;
    
    taskHeap.insert(Task("Провести код-ревью", 2, nextId++));
    cout << "  + Провести код-ревью (приоритет 2)" << endl;
    
    taskHeap.insert(Task("Деплой на продакшн", 1, nextId++));
    cout << "  + Деплой на продакшн (приоритет 1)" << endl;
    
    taskHeap.insert(Task("Оптимизация БД", 4, nextId++));
    cout << "  + Оптимизация БД (приоритет 4)" << endl;
    
    cout << "\nТекущее состояние:" << endl;
    taskHeap.displayDetailed();
    
    cout << "\nВыполнение задач в порядке приоритета:" << endl;
    int taskNum = 1;
    while (!taskHeap.empty()) {
        Task currentTask = taskHeap.getMin();
        cout << taskNum++ << ". Выполняется: " << currentTask << endl;
        taskHeap.extractMin();
    }
}

void extendedDemo() {
    cout << "\n=== РАСШИРЕННАЯ ДЕМОНСТРАЦИЯ ===\n" << endl;
    
    cout << "Куча с double значениями:" << endl;
    BinaryHeap<double> doubleHeap;
    doubleHeap.insert(3.14);
    doubleHeap.insert(2.71);
    doubleHeap.insert(1.41);
    doubleHeap.insert(1.73);
    doubleHeap.displayDetailed();
    
    cout << "Куча со строками:" << endl;
    BinaryHeap<string> stringHeap;
    stringHeap.insert("apple");
    stringHeap.insert("banana");
    stringHeap.insert("cherry");
    stringHeap.insert("date");
    stringHeap.insert("elderberry");
    stringHeap.displayDetailed();
    
    BinaryHeap<int> testHeap;
    
    cout << "Тестирование массового добавления:" << endl;
    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        testHeap.insert(val);
        cout << "Добавлено: " << val << " -> ";
        testHeap.displayAsList();
    }
    
    cout << "\nКонечное состояние:" << endl;
    testHeap.displayDetailed();
    
    cout << "Извлечение всех элементов в порядке возрастания:" << endl;
    while (!testHeap.empty()) {
        cout << testHeap.extractMin() << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    
    demonstrateHeap();
    taskManagerExample();
    extendedDemo();
    
    return 0;
}
