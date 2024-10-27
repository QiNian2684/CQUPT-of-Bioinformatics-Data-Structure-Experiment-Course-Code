#include "Experiment3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 查找最高价格图书的函数
vector<Book> FindMaxPricedBooks(LinkList head, float &max_price){
    vector<Book> max_books;
    LinkList p = head;
    max_price = -1.0f;

    // 首先找到最高价格
    while(p != nullptr){
        if(p->data.price > max_price){
            max_price = p->data.price;
        }
        p = p->next;
    }

    // 再次遍历，收集所有最高价格的图书
    p = head;
    while(p != nullptr){
        if(abs(p->data.price - max_price) < 1e-6){
            max_books.push_back(p->data);
        }
        p = p->next;
    }

    return max_books;
}

// 实验3实现
void Experiment3(){
    cout << "=== 实验3：最贵图书的查找 ===" << endl;
    // 创建图书链表
    LinkList head = CreateList();

    // 查找最高价格的图书
    float max_price = 0.0f;
    vector<Book> max_priced_books = FindMaxPricedBooks(head, max_price);

    // 输出最贵图书的数量
    cout << max_priced_books.size() << endl;

    // 输出最贵图书的信息
    for(auto &book : max_priced_books){
        cout << book.no << " " << book.name << " "
             << fixed << setprecision(2) << book.price << endl;
    }

    // 释放链表内存
    FreeList(head);
    cout << "=== 实验3结束 ===\n" << endl;
}
