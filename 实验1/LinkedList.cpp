#include "LinkedList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// ���������еĺ���
bool parseLine(const string& line, string& isbn, string& title, float& price) {
    istringstream ss(line);
    if (!(ss >> isbn)) {
        // �޷���ȡ ISBN
        return false;
    }
    size_t isbn_len = isbn.length();
    string rest_of_line = line.substr(isbn_len);

    // ȥ��ʣ���е�ǰ���ո�
    size_t first_char = rest_of_line.find_first_not_of(' ');
    if (first_char != string::npos) {
        rest_of_line = rest_of_line.substr(first_char);
    } else {
        // ISBN ֮��û������
        return false;
    }

    // �Ӻ���ǰ���Ҽ۸�
    size_t i = rest_of_line.length();
    while (i > 0 && (isdigit(rest_of_line[i - 1]) || rest_of_line[i - 1] == '.')) {
        i--;
    }
    if (i == rest_of_line.length()) {
        // û���ҵ��۸�
        return false;
    }

    string price_str = rest_of_line.substr(i);
    title = rest_of_line.substr(0, i);

    // ȥ��������β���ո�
    size_t end_pos = title.find_last_not_of(' ');
    if (end_pos != string::npos) {
        title = title.substr(0, end_pos + 1);
    } else {
        title.clear(); // ����Ϊ��
    }

    // ���۸��ַ���ת��Ϊ������
    try {
        price = stof(price_str);
    } catch (const exception& e) {
        // ת��ʧ��
        return false;
    }
    return true;
}

// ����������
LinkList CreateList(){
    LinkList head = nullptr;
    LinkList tail = nullptr;
    string line;

    while(getline(cin, line)){
        if(line.empty()) continue; // ��������
        if(line == "0 0 0") break;  // ��������

        // ������ '===' ��ͷ����
        if(line.substr(0, 3) == "==="){
            continue;
        }

        string isbn, title;
        float price;
        if (!parseLine(line, isbn, title, price)) {
            cerr << "���棺�޷����������У��������У�" << line << endl;
            continue;
        }

        // �����½ڵ�
        LinkList newNode = new LNode;
        strncpy(newNode->data.no, isbn.c_str(), sizeof(newNode->data.no)-1);
        newNode->data.no[sizeof(newNode->data.no)-1] = '\0';
        strncpy(newNode->data.name, title.c_str(), sizeof(newNode->data.name)-1);
        newNode->data.name[sizeof(newNode->data.name)-1] = '\0';
        newNode->data.price = price;
        newNode->next = nullptr;

        // ��������
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// ��ӡ������
void PrintList(LinkList head){
    LinkList p = head;
    while(p != nullptr){
        cout << p->data.no << " " << p->data.name << " "
             << fixed << setprecision(2) << p->data.price << endl;
        p = p->next;
    }
}

// ͳ�������Ⱥ���
int CountList(LinkList head){
    int count = 0;
    LinkList p = head;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}

// �ͷ������ڴ溯��
void FreeList(LinkList head){
    LinkList p = head;
    while(p != nullptr){
        LinkList temp = p;
        p = p->next;
        delete temp;
    }
}
