#include "Experiment1.h"
#include <iostream>

using namespace std;

// 实验1实现
void Experiment1(){
    cout << "=== 实验1：图书信息表的创建和输出 ===" << endl;
    // 创建图书链表
    LinkList head = CreateList();

    // 统计图书个数
    int count = CountList(head);

    // 输出图书个数
    cout << count << endl;

    // 输出每本图书的信息
    PrintList(head);

    // 释放链表内存
    FreeList(head);
    cout << "=== 实验1结束 ===\n" << endl;
}
