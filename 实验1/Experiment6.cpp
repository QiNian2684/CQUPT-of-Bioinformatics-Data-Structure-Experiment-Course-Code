#include "Experiment6.h"
#include <iostream>
#include <unordered_set>

using namespace std;

// 去重函数
LinkList RemoveDuplicates(LinkList head, int &new_count){
    unordered_set<string> seen;
    LinkList current = head;
    LinkList prev = nullptr;
    new_count = 0;

    while(current != nullptr){
        string isbn(current->data.no);
        if(seen.find(isbn) == seen.end()){
            // 第一次出现，保留
            seen.insert(isbn);
            new_count++;
            prev = current;
            current = current->next;
        }
        else{
            // 重复出现，删除节点
            LinkList temp = current;
            if(prev != nullptr){
                prev->next = current->next;
            }
            else{
                // 删除头节点
                head = current->next;
            }
            current = current->next;
            delete temp;
        }
    }

    return head;
}

// 实验6实现
void Experiment6(){
    cout << "=== 实验6：图书去重 ===" << endl;
    // 创建图书链表
    LinkList head = CreateList();

    // 去重并获取新图书个数
    int new_count = 0;
    head = RemoveDuplicates(head, new_count);

    // 输出去重后的图书个数
    cout << new_count << endl;

    // 输出去重后的图书信息
    PrintList(head);

    // 释放链表内存
    FreeList(head);
    cout << "=== 实验6结束 ===\n" << endl;
}
