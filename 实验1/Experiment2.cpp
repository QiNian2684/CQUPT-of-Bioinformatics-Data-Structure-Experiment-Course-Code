#include "Experiment2.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 实验2实现
void Experiment2(){
    cout << "=== 实验2：图书信息表的修改 ===" << endl;
    // 创建图书链表
    LinkList head = CreateList();

    // 统计图书个数和计算总价格
    int count = 0;
    float sum = 0.0f;
    LinkList p = head;
    while(p != nullptr){
        count++;
        sum += p->data.price;
        p = p->next;
    }

    // 计算平均价格
    float average = 0.0f;
    if(count > 0){
        average = sum / count;
    }

    // 修改价格
    p = head;
    while(p != nullptr){
        if(p->data.price < average){
            p->data.price *= 1.20f; // 提高20%
        }
        else{
            p->data.price *= 1.10f; // 提高10%
        }
        p = p->next;
    }

    // 输出平均价格
    cout << fixed << setprecision(2) << average << endl;

    // 输出图书个数
    cout << count << endl;

    // 输出修改后的图书信息
    PrintList(head);

    // 释放链表内存
    FreeList(head);
    cout << "=== 实验2结束 ===\n" << endl;
}
