#include "Experiment6.h"
#include <iostream>
#include <unordered_set>

using namespace std;

// ȥ�غ���
LinkList RemoveDuplicates(LinkList head, int &new_count){
    unordered_set<string> seen;
    LinkList current = head;
    LinkList prev = nullptr;
    new_count = 0;

    while(current != nullptr){
        string isbn(current->data.no);
        if(seen.find(isbn) == seen.end()){
            // ��һ�γ��֣�����
            seen.insert(isbn);
            new_count++;
            prev = current;
            current = current->next;
        }
        else{
            // �ظ����֣�ɾ���ڵ�
            LinkList temp = current;
            if(prev != nullptr){
                prev->next = current->next;
            }
            else{
                // ɾ��ͷ�ڵ�
                head = current->next;
            }
            current = current->next;
            delete temp;
        }
    }

    return head;
}

// ʵ��6ʵ��
void Experiment6(){
    cout << "=== ʵ��6��ͼ��ȥ�� ===" << endl;
    // ����ͼ������
    LinkList head = CreateList();

    // ȥ�ز���ȡ��ͼ�����
    int new_count = 0;
    head = RemoveDuplicates(head, new_count);

    // ���ȥ�غ��ͼ�����
    cout << new_count << endl;

    // ���ȥ�غ��ͼ����Ϣ
    PrintList(head);

    // �ͷ������ڴ�
    FreeList(head);
    cout << "=== ʵ��6���� ===\n" << endl;
}
