#include "LinkedList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// 解析输入行的函数
bool parseLine(const string& line, string& isbn, string& title, float& price) {
    istringstream ss(line);
    if (!(ss >> isbn)) {
        // 无法读取 ISBN
        return false;
    }
    size_t isbn_len = isbn.length();
    string rest_of_line = line.substr(isbn_len);

    // 去除剩余行的前导空格
    size_t first_char = rest_of_line.find_first_not_of(' ');
    if (first_char != string::npos) {
        rest_of_line = rest_of_line.substr(first_char);
    } else {
        // ISBN 之后没有内容
        return false;
    }

    // 从后向前查找价格
    size_t i = rest_of_line.length();
    while (i > 0 && (isdigit(rest_of_line[i - 1]) || rest_of_line[i - 1] == '.')) {
        i--;
    }
    if (i == rest_of_line.length()) {
        // 没有找到价格
        return false;
    }

    string price_str = rest_of_line.substr(i);
    title = rest_of_line.substr(0, i);

    // 去除书名的尾部空格
    size_t end_pos = title.find_last_not_of(' ');
    if (end_pos != string::npos) {
        title = title.substr(0, end_pos + 1);
    } else {
        title.clear(); // 书名为空
    }

    // 将价格字符串转换为浮点数
    try {
        price = stof(price_str);
    } catch (const exception& e) {
        // 转换失败
        return false;
    }
    return true;
}

// 创建链表函数
LinkList CreateList(){
    LinkList head = nullptr;
    LinkList tail = nullptr;
    string line;

    while(getline(cin, line)){
        if(line.empty()) continue; // 跳过空行
        if(line == "0 0 0") break;  // 结束输入

        // 跳过以 '===' 开头的行
        if(line.substr(0, 3) == "==="){
            continue;
        }

        string isbn, title;
        float price;
        if (!parseLine(line, isbn, title, price)) {
            cerr << "警告：无法解析输入行，跳过此行：" << line << endl;
            continue;
        }

        // 创建新节点
        LinkList newNode = new LNode;
        strncpy(newNode->data.no, isbn.c_str(), sizeof(newNode->data.no)-1);
        newNode->data.no[sizeof(newNode->data.no)-1] = '\0';
        strncpy(newNode->data.name, title.c_str(), sizeof(newNode->data.name)-1);
        newNode->data.name[sizeof(newNode->data.name)-1] = '\0';
        newNode->data.price = price;
        newNode->next = nullptr;

        // 插入链表
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

// 打印链表函数
void PrintList(LinkList head){
    LinkList p = head;
    while(p != nullptr){
        cout << p->data.no << " " << p->data.name << " "
             << fixed << setprecision(2) << p->data.price << endl;
        p = p->next;
    }
}

// 统计链表长度函数
int CountList(LinkList head){
    int count = 0;
    LinkList p = head;
    while(p != nullptr){
        count++;
        p = p->next;
    }
    return count;
}

// 释放链表内存函数
void FreeList(LinkList head){
    LinkList p = head;
    while(p != nullptr){
        LinkList temp = p;
        p = p->next;
        delete temp;
    }
}
