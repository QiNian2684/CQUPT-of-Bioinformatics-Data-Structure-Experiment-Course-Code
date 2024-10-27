#include "Experiment4.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

// 插入图书函数
bool InsertBook(LinkList &head, int pos, Book new_book, int length){
    // 检查插入位置是否合法（1 <= pos <= length +1）
    if(pos < 1 || pos > length +1){
        return false;
    }

    // 创建新节点
    LinkList newNode = new LNode;
    newNode->data = new_book;
    newNode->next = nullptr;

    if(pos == 1){
        // 插入到头部
        newNode->next = head;
        head = newNode;
    }
    else{
        // 插入到指定位置
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

// 实验4实现
void Experiment4(){

    cout << "=== 实验4：图书信息表的插入 ===" << endl;

    // 创建图书链表
    LinkList head = CreateList();

    // 统计图书个数
    int count = CountList(head);

    // 读取插入位置
    int pos;
    cin >> pos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区

    // 读取新图书信息
    string line;
    getline(cin, line);

    // 使用 parseLine 函数解析新图书信息
    string isbn, title;
    float price;
    if (!parseLine(line, isbn, title, price)) {
        cout << "抱歉，入库位置非法!" << endl;
        FreeList(head);
        return;
    }

    // 创建新图书
    Book new_book;
    strncpy(new_book.no, isbn.c_str(), sizeof(new_book.no)-1);
    new_book.no[sizeof(new_book.no)-1] = '\0';
    strncpy(new_book.name, title.c_str(), sizeof(new_book.name)-1);
    new_book.name[sizeof(new_book.name)-1] = '\0';
    new_book.price = price;

    // 插入新图书
    bool success = InsertBook(head, pos, new_book, count);

    if(success){
        // 图书插入成功，图书总数增加1
        count++;
        cout << count << endl;
        // 输出所有图书信息
        PrintList(head);
    }
    else{
        // 插入失败
        cout << "抱歉，入库位置非法!" << endl;
    }

    // 释放链表内存
    FreeList(head);

    cout << "=== 实验4结束 ===\n" << endl;
}
