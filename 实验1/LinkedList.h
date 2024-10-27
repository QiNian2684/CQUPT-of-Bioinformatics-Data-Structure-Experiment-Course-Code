#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Book.h"
#include <string>

// 链表节点结构体
struct LNode {
    Book data;       // 数据域
    LNode* next;     // 指针域
};

// 链式存储结构类型为 LinkList
typedef LNode* LinkList;

// 链表操作函数声明
LinkList CreateList();
void PrintList(LinkList head);
int CountList(LinkList head);
void FreeList(LinkList head);

// 声明 parseLine 函数
bool parseLine(const std::string& line, std::string& isbn, std::string& title, float& price);

#endif // LINKEDLIST_H
