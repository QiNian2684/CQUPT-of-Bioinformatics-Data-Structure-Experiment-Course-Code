#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <climits>

using namespace std;

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

int main() {
    char str[1000];
    while (true) {
        cin.getline(str, 1000);
        if (strcmp(str, "0") == 0) {
            break;
        }

        int count[26] = {0};
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            count[str[i] - 'a']++;
        }

        // Output character frequencies
        int n = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                n++;
            }
        }
        if (n == 0) {
            continue;
        }
        char chars[100]; // chars[1..n]
        int weights[100]; // weights[1..n]
        int idx = 1;
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                chars[idx] = 'a' + i;
                weights[idx] = count[i];
                idx++;
            }
        }

        int m = 2 * n - 1;
        HuffmanTree HT = new HTNode[m + 1]; // HT[1..m]
        for (int i = 1; i <= m; i++) {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }

        for (int i = 1; i <= n; i++) {
            HT[i].weight = weights[i];
        }

        for (int i = n + 1; i <= m; i++) {
            int min1 = INT_MAX, min2 = INT_MAX;
            int s1 = 0, s2 = 0;
            for (int j = 1; j <= i - 1; j++) {
                if (HT[j].parent == 0) {
                    if (HT[j].weight < min1) {
                        min2 = min1;
                        s2 = s1;
                        min1 = HT[j].weight;
                        s1 = j;
                    } else if (HT[j].weight < min2) {
                        min2 = HT[j].weight;
                        s2 = j;
                    }
                }
            }
            HT[s1].parent = i;
            HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
        }

        // Generate Huffman codes
        char** HC = new char*[n + 1]; // HC[1..n]
        char cd[n];
        cd[n - 1] = '\0';
        for (int i = 1; i <= n; i++) {
            int start = n - 1;
            int c = i;
            int f = HT[i].parent;
            while (f != 0) {
                if (HT[f].lchild == c) {
                    cd[--start] = '0';
                } else {
                    cd[--start] = '1';
                }
                c = f;
                f = HT[f].parent;
            }
            HC[i] = new char[n - start + 1];
            strcpy(HC[i], &cd[start]);
        }

        // Output character frequencies
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                cout << (char)(i + 'a') << ":" << count[i] << " ";
            }
        }
        cout << endl;

        // Output Huffman tree structure
        for (int i = 1; i <= m; i++) {
            cout << i << " " << HT[i].weight << " ";
            printf("%d%d%d", HT[i].parent, HT[i].lchild, HT[i].rchild);
            cout << endl;
        }

        // Map characters to indices
        int charToIndex[26] = {0};
        for (int i = 1; i <= n; i++) {
            charToIndex[chars[i] - 'a'] = i;
        }

        // Output Huffman codes
        for (int i = 0; i < 26; i++) {
            int idx = charToIndex[i];
            if (idx != 0) {
                cout << (char)(i + 'a') << ":" << HC[idx] << " ";
            }
        }
        cout << endl;

        // Encode the string
        string encodedStr = "";
        for (int i = 0; i < len; i++) {
            int idx = charToIndex[str[i] - 'a'];
            encodedStr += HC[idx];
        }
        cout << encodedStr << endl;

        // Decode the string
        int f = m;
        int i = 0;
        while (i < encodedStr.length()) {
            if (encodedStr[i] == '0') {
                f = HT[f].lchild;
            } else {
                f = HT[f].rchild;
            }
            if (HT[f].lchild == 0 && HT[f].rchild == 0) {
                cout << chars[f];
                f = m;
            }
            i++;
        }
        cout << endl;

        // Clean up
        delete[] HT;
        for (int i = 1; i <= n; i++) {
            delete[] HC[i];
        }
        delete[] HC;
    }

    return 0;
}
