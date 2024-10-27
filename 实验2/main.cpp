#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;

// 获取运算符对应的索引
int getIndex(char theta) {
    switch (theta) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case '#': return 6;
        default: return -1; // 无效运算符
    }
}

// 获取运算符之间的优先级
char getPriority(char theta1, char theta2) {
    // 优先级关系表
    // 表中行对应theta1，列对应theta2
    // '>' 表示theta1 > theta2
    // '<' 表示theta1 < theta2
    // '=' 表示theta1 = theta2
    const char priority[7][7] = {
        // +    -    *    /    (    )    #
        { '>', '>', '<', '<', '<', '>', '>' }, // +
        { '>', '>', '<', '<', '<', '>', '>' }, // -
        { '>', '>', '>', '>', '<', '>', '>' }, // *
        { '>', '>', '>', '>', '<', '>', '>' }, // /
        { '<', '<', '<', '<', '<', '=', '0' }, // (
        { '>', '>', '>', '>', '0', '>', '>' }, // )
        { '<', '<', '<', '<', '<', '0', '=' }  // #
    };

    int index1 = getIndex(theta1);
    int index2 = getIndex(theta2);

    if(index1 == -1 || index2 == -1){
        return '0'; // 默认返回低优先级
    }

    return priority[index1][index2];
}

// 计算两个操作数的结果
int compute(int a, int b, char oper) {
    switch (oper) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if(b == 0){
                cerr << "Error: Division by zero!" << endl;
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            cerr << "Error: Invalid operator '" << oper << "'!" << endl;
            exit(EXIT_FAILURE);
    }
}

// 计算表达式的值
int evaluateExpression(const string& expr) {
    stack<char> OPTR; // 运算符栈
    stack<int> OPND;  // 操作数栈

    OPTR.push('#'); // 初始化运算符栈底

    size_t i = 0;
    size_t n = expr.length();

    // 确保表达式以'#'结尾
    string expression = expr;
    if(expression.back() != '='){
        // 根据输入要求，表达式应以'='结尾
        // 如果没有，自动添加
        expression += '=';
    }

    // 将'='替换为'#'以符合算法
    if(expression.back() == '='){
        expression.back() = '#';
    }

    while(i < expression.length()){
        char c = expression[i];

        if(isspace(c)){
            // 跳过空格
            i++;
            continue;
        }

        if(isdigit(c)){
            // 读取一个完整的整数
            int num = 0;
            while(i < expression.length() && isdigit(expression[i])){
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            OPND.push(num);
            continue; // 继续下一字符
        }

        // 处理运算符
        while(true){
            char top = OPTR.top();
            char precedence = getPriority(top, c);

            if(precedence == '<'){
                OPTR.push(c);
                break;
            }
            else if(precedence == '='){
                OPTR.pop(); // 匹配的括号，弹出
                break;
            }
            else if(precedence == '>'){
                // 执行计算
                if(OPND.size() < 2){
                    cerr << "Error: Not enough operands!" << endl;
                    exit(EXIT_FAILURE);
                }
                int b = OPND.top(); OPND.pop();
                int a = OPND.top(); OPND.pop();
                char oper = OPTR.top(); OPTR.pop();
                int result = compute(a, b, oper);
                OPND.push(result);
            }
            else{
                // 处理其他情况，如优先级表中的'0'
                cerr << "Error: Invalid precedence!" << endl;
                exit(EXIT_FAILURE);
            }
        }

        i++;
    }

    if(OPND.empty()){
        cerr << "Error: No result computed!" << endl;
        exit(EXIT_FAILURE);
    }

    return OPND.top();
}

int main(){
    string line;
    while(getline(cin, line)){
        // 检查是否为结束标志
        if(line == "="){
            break;
        }

        // 计算表达式的值
        int result = evaluateExpression(line);
        cout << result << endl;
    }

    return 0;
}
