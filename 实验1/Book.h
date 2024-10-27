#ifndef BOOK_H
#define BOOK_H

#define MAXSIZE 10000 // 图书表可能达到的最大长度

#include <cstring>

// 图书信息定义
struct Book {
    char no[20];    // 图书 ISBN
    char name[50];  // 图书名字
    float price;    // 图书价格
};

#endif // BOOK_H
