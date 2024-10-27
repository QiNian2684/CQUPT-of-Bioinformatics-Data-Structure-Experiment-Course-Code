#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

// 定义二叉树结点结构
typedef struct Node {
    char data;               // 数据域
    struct Node *leftChild;  // 左子树指针
    struct Node *rightChild; // 右子树指针
} BiTreeNode, *BiTree;

// 创建新的树节点
BiTree CreateNode(char ch, BiTree left = nullptr, BiTree right = nullptr) {
    BiTreeNode* node = new BiTreeNode;
    node->data = ch;
    node->leftChild = left;
    node->rightChild = right;
    return node;
}

// 判断字符是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 返回运算符的优先级
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0; // '(' 的优先级最低
}

// 计算表达式树的值（后序遍历）
int evaluate(BiTree root) {
    if (!root)
        return 0;
    // 如果是叶子节点（数字）
    if (!root->leftChild && !root->rightChild)
        return root->data - '0';
    // 递归计算左子树和右子树
    int leftVal = evaluate(root->leftChild);
    int rightVal = evaluate(root->rightChild);
    // 根据运算符计算结果
    switch (root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/':
            if (rightVal == 0) {
                cerr << "Error: Division by zero." << endl;
                exit(EXIT_FAILURE);
            }
            return leftVal / rightVal;
        default:
            cerr << "Error: Unknown operator " << root->data << endl;
            exit(EXIT_FAILURE);
    }
}

// 构建表达式树
BiTree buildExpressionTree(const string& expr) {
    stack<char> OPTR;    // 运算符栈
    stack<BiTree> EXPT;  // 操作数栈（表达式树节点）

    OPTR.push('#'); // 栈底标志

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (ch == ' ') {
            continue; // 跳过空格
        }

        if (isdigit(ch)) {
            // 如果是数字，创建叶子节点并压入操作数栈
            BiTree operand = CreateNode(ch);
            EXPT.push(operand);
        }
        else if (ch == '(') {
            OPTR.push(ch);
        }
        else if (ch == ')') {
            // 弹出运算符并构建子树，直到遇到 '('
            while (!OPTR.empty() && OPTR.top() != '(') {
                char op = OPTR.top();
                OPTR.pop();
                // 弹出两个操作数
                if (EXPT.size() < 2) {
                    cerr << "Error: Invalid expression." << endl;
                    exit(EXIT_FAILURE);
                }
                BiTree right = EXPT.top(); EXPT.pop();
                BiTree left = EXPT.top(); EXPT.pop();
                // 创建新节点并压入操作数栈
                BiTree operatorNode = CreateNode(op, left, right);
                EXPT.push(operatorNode);
            }
            if (!OPTR.empty() && OPTR.top() == '(') {
                OPTR.pop(); // 弹出 '('
            }
            else {
                cerr << "Error: Mismatched parentheses." << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (isOperator(ch)) {
            // 处理运算符
            while (!OPTR.empty() && precedence(OPTR.top()) >= precedence(ch)) {
                if (OPTR.top() == '(')
                    break;
                char op = OPTR.top();
                OPTR.pop();
                // 弹出两个操作数
                if (EXPT.size() < 2) {
                    cerr << "Error: Invalid expression." << endl;
                    exit(EXIT_FAILURE);
                }
                BiTree right = EXPT.top(); EXPT.pop();
                BiTree left = EXPT.top(); EXPT.pop();
                // 创建新节点并压入操作数栈
                BiTree operatorNode = CreateNode(op, left, right);
                EXPT.push(operatorNode);
            }
            OPTR.push(ch);
        }
        else {
            cerr << "Error: Invalid character '" << ch << "' in expression." << endl;
            exit(EXIT_FAILURE);
        }
    }

    // 处理剩余的运算符
    while (!OPTR.empty() && OPTR.top() != '#') {
        char op = OPTR.top();
        OPTR.pop();
        if (op == '(' || op == ')') {
            cerr << "Error: Mismatched parentheses." << endl;
            exit(EXIT_FAILURE);
        }
        // 弹出两个操作数
        if (EXPT.size() < 2) {
            cerr << "Error: Invalid expression." << endl;
            exit(EXIT_FAILURE);
        }
        BiTree right = EXPT.top(); EXPT.pop();
        BiTree left = EXPT.top(); EXPT.pop();
        // 创建新节点并压入操作数栈
        BiTree operatorNode = CreateNode(op, left, right);
        EXPT.push(operatorNode);
    }

    if (OPTR.empty() || OPTR.top() != '#') {
        cerr << "Error: Invalid expression." << endl;
        exit(EXIT_FAILURE);
    }

    if (EXPT.size() != 1) {
        cerr << "Error: Invalid expression." << endl;
        exit(EXIT_FAILURE);
    }

    return EXPT.top(); // 表达式树的根节点
}

int main() {
    string line;
    while (getline(cin, line)) {
        // 移除行末的换行符和空格
        size_t start = 0;
        size_t end = line.length();
        while (start < end && isspace(line[start])) start++;
        while (end > start && isspace(line[end - 1])) end--;
        string expr = line.substr(start, end - start);

        if (expr == "=")
            break; // 输入结束

        // 确保表达式以 '=' 结尾
        if (expr.empty() || expr.back() != '=') {
            cerr << "Error: Expression must end with '='." << endl;
            continue;
        }

        // 去掉末尾的 '='
        expr.pop_back();

        // 构建表达式树
        BiTree root = buildExpressionTree(expr);

        // 计算表达式的值
        int result = evaluate(root);

        // 输出结果
        cout << result << endl;

        // 释放内存（可选）
        // 这里没有实现树的释放，为了简化代码，假设输入数据不大，程序结束时操作系统会回收内存
    }

    return 0;
}
