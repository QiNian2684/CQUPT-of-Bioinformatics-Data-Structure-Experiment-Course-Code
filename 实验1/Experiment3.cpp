#include "Experiment3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ������߼۸�ͼ��ĺ���
vector<Book> FindMaxPricedBooks(LinkList head, float &max_price){
    vector<Book> max_books;
    LinkList p = head;
    max_price = -1.0f;

    // �����ҵ���߼۸�
    while(p != nullptr){
        if(p->data.price > max_price){
            max_price = p->data.price;
        }
        p = p->next;
    }

    // �ٴα������ռ�������߼۸��ͼ��
    p = head;
    while(p != nullptr){
        if(abs(p->data.price - max_price) < 1e-6){
            max_books.push_back(p->data);
        }
        p = p->next;
    }

    return max_books;
}

// ʵ��3ʵ��
void Experiment3(){
    cout << "=== ʵ��3�����ͼ��Ĳ��� ===" << endl;
    // ����ͼ������
    LinkList head = CreateList();

    // ������߼۸��ͼ��
    float max_price = 0.0f;
    vector<Book> max_priced_books = FindMaxPricedBooks(head, max_price);

    // ������ͼ�������
    cout << max_priced_books.size() << endl;

    // ������ͼ�����Ϣ
    for(auto &book : max_priced_books){
        cout << book.no << " " << book.name << " "
             << fixed << setprecision(2) << book.price << endl;
    }

    // �ͷ������ڴ�
    FreeList(head);
    cout << "=== ʵ��3���� ===\n" << endl;
}
