#include "Experiment5.h"
#include <iostream>
#include <limits>

using namespace std;

// ɾ��ͼ�麯��
bool DeleteBook(LinkList &head, int pos, int length){
    // ���ɾ��λ���Ƿ�Ϸ���1 <= pos <= length��
    if(pos < 1 || pos > length){
        return false;
    }

    LinkList toDelete = nullptr;

    if(pos == 1){
        // ɾ��ͷ�ڵ�
        toDelete = head;
        head = head->next;
    }
    else{
        // ɾ���м��β���ڵ�
        LinkList p = head;
        for(int i=1; i<pos-1 && p != nullptr; i++){
            p = p->next;
        }
        if(p == nullptr || p->next == nullptr){
            return false;
        }
        toDelete = p->next;
        p->next = toDelete->next;
    }

    delete toDelete;
    return true;
}

// ʵ��5ʵ��
void Experiment5(){

    cout << "=== ʵ��5��ͼ����Ϣ���ɾ�� ===" << endl;

    // ����ͼ������
    LinkList head = CreateList();

    // ͳ��ͼ�����
    int count = CountList(head);

    // ��ȡɾ��λ��
    int pos;
    cin >> pos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������

    // ɾ��ͼ��
    bool success = DeleteBook(head, pos, count);

    if(success){
        // ɾ���ɹ���ͼ����������1
        count--;
        cout << count << endl;
        // �������ͼ����Ϣ
        PrintList(head);
    }
    else{
        // ɾ��ʧ��
        cout << "��Ǹ������λ�÷Ƿ�!" << endl;
    }

    // �ͷ������ڴ�
    FreeList(head);

    cout << "=== ʵ��5���� ===\n" << endl;
}
