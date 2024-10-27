#include "Experiment4.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

// ����ͼ�麯��
bool InsertBook(LinkList &head, int pos, Book new_book, int length){
    // ������λ���Ƿ�Ϸ���1 <= pos <= length +1��
    if(pos < 1 || pos > length +1){
        return false;
    }

    // �����½ڵ�
    LinkList newNode = new LNode;
    newNode->data = new_book;
    newNode->next = nullptr;

    if(pos == 1){
        // ���뵽ͷ��
        newNode->next = head;
        head = newNode;
    }
    else{
        // ���뵽ָ��λ��
        LinkList p = head;
        for(int i=1; i<pos-1 && p != nullptr; i++){
            p = p->next;
        }
        if(p == nullptr){
            delete newNode;
            return false;
        }
        newNode->next = p->next;
        p->next = newNode;
    }

    return true;
}

// ʵ��4ʵ��
void Experiment4(){

    cout << "=== ʵ��4��ͼ����Ϣ��Ĳ��� ===" << endl;

    // ����ͼ������
    LinkList head = CreateList();

    // ͳ��ͼ�����
    int count = CountList(head);

    // ��ȡ����λ��
    int pos;
    cin >> pos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������

    // ��ȡ��ͼ����Ϣ
    string line;
    getline(cin, line);

    // ʹ�� parseLine ����������ͼ����Ϣ
    string isbn, title;
    float price;
    if (!parseLine(line, isbn, title, price)) {
        cout << "��Ǹ�����λ�÷Ƿ�!" << endl;
        FreeList(head);
        return;
    }

    // ������ͼ��
    Book new_book;
    strncpy(new_book.no, isbn.c_str(), sizeof(new_book.no)-1);
    new_book.no[sizeof(new_book.no)-1] = '\0';
    strncpy(new_book.name, title.c_str(), sizeof(new_book.name)-1);
    new_book.name[sizeof(new_book.name)-1] = '\0';
    new_book.price = price;

    // ������ͼ��
    bool success = InsertBook(head, pos, new_book, count);

    if(success){
        // ͼ�����ɹ���ͼ����������1
        count++;
        cout << count << endl;
        // �������ͼ����Ϣ
        PrintList(head);
    }
    else{
        // ����ʧ��
        cout << "��Ǹ�����λ�÷Ƿ�!" << endl;
    }

    // �ͷ������ڴ�
    FreeList(head);

    cout << "=== ʵ��4���� ===\n" << endl;
}
