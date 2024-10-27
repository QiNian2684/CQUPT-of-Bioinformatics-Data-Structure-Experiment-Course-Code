#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Book.h"
#include <string>

// ����ڵ�ṹ��
struct LNode {
    Book data;       // ������
    LNode* next;     // ָ����
};

// ��ʽ�洢�ṹ����Ϊ LinkList
typedef LNode* LinkList;

// ���������������
LinkList CreateList();
void PrintList(LinkList head);
int CountList(LinkList head);
void FreeList(LinkList head);

// ���� parseLine ����
bool parseLine(const std::string& line, std::string& isbn, std::string& title, float& price);

#endif // LINKEDLIST_H
