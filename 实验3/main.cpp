#include <iostream>
#include <string>
#include <vector>

// 构建KMP算法中的最长前缀后缀（LPS）表
std::vector<int> buildKMPTable(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m, 0); // 初始化LPS表
    int len = 0; // 前一个最长前缀后缀的长度

    for (int i = 1; i < m; ++i) {
        // 如果当前字符不匹配，回退到之前的最长前缀后缀位置
        while (len > 0 && pattern[i] != pattern[len]) {
            len = lps[len - 1];
        }
        // 如果当前字符匹配，增加前缀后缀长度
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
        }
    }
    return lps;
}

// KMP搜索函数：如果在text中找到pattern，则返回true
bool KMP(const std::string& text, const std::string& pattern, const std::vector<int>& lps) {
    int n = text.length();
    int m = pattern.length();
    int i = 0; // text的索引
    int j = 0; // pattern的索引

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == m) {
                return true; // 找到匹配
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false; // 未找到匹配
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string A, B;
    int caseNumber = 1; // 测试用例编号

    // 循环读取多组数据，直到输入为"0 0"时结束
    while (std::cin >> A >> B) {
        if (A == "0" && B == "0") {
            break; // 结束输入
        }

        int m = A.length();
        int n = B.length();
        bool infected = false;

        // 如果病毒DNA长度大于人的DNA，直接判断为未感染
        if (m > n) {
            infected = false;
        } else {
            // 将病毒DNA序列连接两次以覆盖所有环状旋转
            std::string AA = A + A;

            // 遍历所有可能的旋转
            for (int i = 0; i < m; ++i) {
                std::string rotation = AA.substr(i, m);
                // 构建当前旋转的LPS表
                std::vector<int> lps = buildKMPTable(rotation);
                // 使用KMP算法进行匹配
                if (KMP(B, rotation, lps)) {
                    infected = true;
                    break; // 找到匹配后无需继续
                }
            }
        }

        // 输出检测结果
        std::cout << (infected ? "YES" : "NO") << "\n";

        // 如果需要显示测试用例编号和详细信息，可以取消注释以下代码
        /*
        std::cout << "测试用例 " << caseNumber++ << ":\n";
        std::cout << "病毒DNA: " << A << "\n";
        std::cout << "人类DNA: " << B << "\n";
        std::cout << "感染结果: " << (infected ? "YES" : "NO") << "\n\n";
        */
    }

    return 0;
}
