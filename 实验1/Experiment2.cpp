#include "Experiment2.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ʵ��2ʵ��
void Experiment2(){
    cout << "=== ʵ��2��ͼ����Ϣ����޸� ===" << endl;
    // ����ͼ������
    LinkList head = CreateList();

    // ͳ��ͼ������ͼ����ܼ۸�
    int count = 0;
    float sum = 0.0f;
    LinkList p = head;
    while(p != nullptr){
        count++;
        sum += p->data.price;
        p = p->next;
    }

    // ����ƽ���۸�
    float average = 0.0f;
    if(count > 0){
        average = sum / count;
    }

    // �޸ļ۸�
    p = head;
    while(p != nullptr){
        if(p->data.price < average){
            p->data.price *= 1.20f; // ���20%
        }
        else{
            p->data.price *= 1.10f; // ���10%
        }
        p = p->next;
    }

    // ���ƽ���۸�
    cout << fixed << setprecision(2) << average << endl;

    // ���ͼ�����
    cout << count << endl;

    // ����޸ĺ��ͼ����Ϣ
    PrintList(head);

    // �ͷ������ڴ�
    FreeList(head);
    cout << "=== ʵ��2���� ===\n" << endl;
}
