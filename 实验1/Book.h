#ifndef BOOK_H
#define BOOK_H

#define MAXSIZE 10000 // ͼ�����ܴﵽ����󳤶�

#include <cstring>

// ͼ����Ϣ����
struct Book {
    char no[20];    // ͼ�� ISBN
    char name[50];  // ͼ������
    float price;    // ͼ��۸�
};

#endif // BOOK_H
