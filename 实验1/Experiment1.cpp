#include "Experiment1.h"
#include <iostream>

using namespace std;

// ʵ��1ʵ��
void Experiment1(){
    cout << "=== ʵ��1��ͼ����Ϣ��Ĵ�������� ===" << endl;
    // ����ͼ������
    LinkList head = CreateList();

    // ͳ��ͼ�����
    int count = CountList(head);

    // ���ͼ�����
    cout << count << endl;

    // ���ÿ��ͼ�����Ϣ
    PrintList(head);

    // �ͷ������ڴ�
    FreeList(head);
    cout << "=== ʵ��1���� ===\n" << endl;
}
