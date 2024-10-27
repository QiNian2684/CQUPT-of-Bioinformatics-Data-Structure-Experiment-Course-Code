#include "Experiment5.h"
#include <iostream>
#include <limits>

using namespace std;

// 删除图书函数
bool DeleteBook(LinkList &head, int pos, int length){
    // 检查删除位置是否合法（1 <= pos <= length）
    if(pos < 1 || pos > length){
        return false;
    }

    LinkList toDelete = nullptr;

    if(pos == 1){
        // 删除头节点
        toDelete = head;
        head = head->next;
    }
    else{
        // 删除中间或尾部节点
        LinkList p = head;
        for(int i=1; i<pos-1 && p != nullptr; i++){
            p = p->next;
        }
        if(p == nullptr || p->next == nullptr){
            return false;
        }
        toDelete = p->next;
        p->next = toDelete->next;
    }

    delete toDelete;
    return true;
}

// 实验5实现
void Experiment5(){

    cout << "=== 实验5：图书信息表的删除 ===" << endl;

    // 创建图书链表
    LinkList head = CreateList();

    // 统计图书个数
    int count = CountList(head);

    // 读取删除位置
    int pos;
    cin >> pos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区

    // 删除图书
    bool success = DeleteBook(head, pos, count);

    if(success){
        // 删除成功，图书总数减少1
        count--;
        cout << count << endl;
        // 输出所有图书信息
        PrintList(head);
    }
    else{
        // 删除失败
        cout << "抱歉，出库位置非法!" << endl;
    }

    // 释放链表内存
    FreeList(head);

    cout << "=== 实验5结束 ===\n" << endl;
}
