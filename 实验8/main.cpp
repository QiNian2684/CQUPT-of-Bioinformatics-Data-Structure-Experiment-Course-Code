#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// 定义学生结构体
struct Student {
    string name;   // 姓名
    float score;   // 成绩
    int rank;      // 名次
};

// 插入排序算法（稳定排序）
void insertionSort(vector<Student> &students) {
    cout << "使用插入排序进行排序..." << endl;
    int n = students.size();
    for(int i = 1; i < n; ++i){
        Student key = students[i];
        int j = i - 1;
        // 按成绩降序排序
        while(j >=0 && students[j].score < key.score){
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
    cout << "插入排序完成。\n" << endl;
}

// 快速排序的分区函数
int partitionQuickSort(vector<Student> &students, int low, int high) {
    float pivot = students[high].score;
    int i = low - 1;
    for(int j = low; j < high; j++) {
        if(students[j].score > pivot) { // 降序排列
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

// 快速排序算法（不稳定排序）
void quickSort(vector<Student> &students, int low, int high) {
    if(low < high) {
        int pi = partitionQuickSort(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

// 希尔排序算法
void shellSort(vector<Student> &students) {
    cout << "使用希尔排序进行排序..." << endl;
    int n = students.size();
    // 使用希尔增量序列（Knuth序列）
    int gap = 1;
    while(gap < n/3) gap = 3 * gap + 1;
    while(gap >=1){
        for(int i = gap; i < n; ++i){
            Student temp = students[i];
            int j = i;
            while(j >= gap && students[j - gap].score < temp.score){
                students[j] = students[j - gap];
                j -= gap;
            }
            students[j] = temp;
        }
        gap /= 3;
    }
    cout << "希尔排序完成。\n" << endl;
}

// 快速排序接口
void performQuickSort(vector<Student> &students) {
    cout << "开始使用快速排序对学生按成绩降序排序..." << endl;
    quickSort(students, 0, students.size() - 1);
    cout << "快速排序完成。\n" << endl;
}

// 分配名次
void assignRanks(vector<Student> &students) {
    if(students.empty()) return;
    int current_rank = 1;
    students[0].rank = current_rank;
    for(int i = 1; i < students.size(); i++){
        if(abs(students[i].score - students[i-1].score) < 1e-6){
            students[i].rank = current_rank; // 分数相同，名次相同
        }
        else{
            current_rank = i + 1;
            students[i].rank = current_rank;
        }
    }
}

// 打印排序结果
void printStudents(const vector<Student> &students) {
    cout << "名次 姓名 成绩" << endl;
    for(const auto &s : students){
        // 设置输出格式为两位小数
        cout << s.rank << " " << s.name << " " << fixed << setprecision(2) << s.score << "\n";
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Student> original_students;
    string name;
    float score;

    // 读取学生信息，直到输入"0 0"
    while(cin >> name >> score){
        if(name == "0" && fabs(score - 0.0) < 1e-6){
            break; // 输入结束标志
        }
        Student s;
        s.name = name;
        s.score = score;
        s.rank = 0; // 初始名次为0
        original_students.push_back(s);
    }

    if(original_students.empty()){
        return 0; // 无学生数据，无需输出
    }

    // 快速排序
    vector<Student> quick_sorted = original_students; // 复制原始数据
    performQuickSort(quick_sorted);
    assignRanks(quick_sorted);
    cout << "快速排序结果:" << endl;
    printStudents(quick_sorted);

    // 插入排序
    vector<Student> insertion_sorted = original_students; // 复制原始数据
    insertionSort(insertion_sorted);
    assignRanks(insertion_sorted);
    cout << "插入排序结果:" << endl;
    printStudents(insertion_sorted);

    // 希尔排序
    vector<Student> shell_sorted = original_students; // 复制原始数据
    shellSort(shell_sorted);
    assignRanks(shell_sorted);
    cout << "希尔排序结果:" << endl;
    printStudents(shell_sorted);

    return 0;
}
