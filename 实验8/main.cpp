#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// ����ѧ���ṹ��
struct Student {
    string name;   // ����
    float score;   // �ɼ�
    int rank;      // ����
};

// ���������㷨���ȶ�����
void insertionSort(vector<Student> &students) {
    cout << "ʹ�ò��������������..." << endl;
    int n = students.size();
    for(int i = 1; i < n; ++i){
        Student key = students[i];
        int j = i - 1;
        // ���ɼ���������
        while(j >=0 && students[j].score < key.score){
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
    cout << "����������ɡ�\n" << endl;
}

// ��������ķ�������
int partitionQuickSort(vector<Student> &students, int low, int high) {
    float pivot = students[high].score;
    int i = low - 1;
    for(int j = low; j < high; j++) {
        if(students[j].score > pivot) { // ��������
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

// ���������㷨�����ȶ�����
void quickSort(vector<Student> &students, int low, int high) {
    if(low < high) {
        int pi = partitionQuickSort(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

// ϣ�������㷨
void shellSort(vector<Student> &students) {
    cout << "ʹ��ϣ�������������..." << endl;
    int n = students.size();
    // ʹ��ϣ���������У�Knuth���У�
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
    cout << "ϣ��������ɡ�\n" << endl;
}

// ��������ӿ�
void performQuickSort(vector<Student> &students) {
    cout << "��ʼʹ�ÿ��������ѧ�����ɼ���������..." << endl;
    quickSort(students, 0, students.size() - 1);
    cout << "����������ɡ�\n" << endl;
}

// ��������
void assignRanks(vector<Student> &students) {
    if(students.empty()) return;
    int current_rank = 1;
    students[0].rank = current_rank;
    for(int i = 1; i < students.size(); i++){
        if(abs(students[i].score - students[i-1].score) < 1e-6){
            students[i].rank = current_rank; // ������ͬ��������ͬ
        }
        else{
            current_rank = i + 1;
            students[i].rank = current_rank;
        }
    }
}

// ��ӡ������
void printStudents(const vector<Student> &students) {
    cout << "���� ���� �ɼ�" << endl;
    for(const auto &s : students){
        // ���������ʽΪ��λС��
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

    // ��ȡѧ����Ϣ��ֱ������"0 0"
    while(cin >> name >> score){
        if(name == "0" && fabs(score - 0.0) < 1e-6){
            break; // ���������־
        }
        Student s;
        s.name = name;
        s.score = score;
        s.rank = 0; // ��ʼ����Ϊ0
        original_students.push_back(s);
    }

    if(original_students.empty()){
        return 0; // ��ѧ�����ݣ��������
    }

    // ��������
    vector<Student> quick_sorted = original_students; // ����ԭʼ����
    performQuickSort(quick_sorted);
    assignRanks(quick_sorted);
    cout << "����������:" << endl;
    printStudents(quick_sorted);

    // ��������
    vector<Student> insertion_sorted = original_students; // ����ԭʼ����
    insertionSort(insertion_sorted);
    assignRanks(insertion_sorted);
    cout << "����������:" << endl;
    printStudents(insertion_sorted);

    // ϣ������
    vector<Student> shell_sorted = original_students; // ����ԭʼ����
    shellSort(shell_sorted);
    assignRanks(shell_sorted);
    cout << "ϣ��������:" << endl;
    printStudents(shell_sorted);

    return 0;
}
