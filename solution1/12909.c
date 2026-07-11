#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool solution(const char *s) {
    int count = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
        }
        
        // 닫는 괄호가 여는 괄호보다 먼저 나오면 즉시 실패
        if (count < 0) {
            return false;
        }
    }
    
    // 끝까지 다 짝지어졌는지 확인
    return count == 0;
}

int main() {
    printf("%d\n", solution("()()"));   // 1 (true)
    printf("%d\n", solution("(())()")); // 1 (true)
    printf("%d\n", solution(")()("));   // 0 (false)
    printf("%d\n", solution("(()("));   // 0 (false)
    return 0;
}