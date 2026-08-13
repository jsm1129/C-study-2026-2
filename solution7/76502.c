#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 여는 괄호를 받아 그에 대응하는 닫는 괄호를 반환
char getCloser(char open) {
    if (open == '(') return ')';
    if (open == '[') return ']';
    return '}'; // '{' 인 경우
}

// 여는 괄호인지 판별
bool isOpen(char c) {
    return c == '(' || c == '[' || c == '{';
}

// 파라미터로 주어지는 문자열은 const로 주어짐
int solution(const char* s) {
    int answer = 0;
    int len = strlen(s);

    // 스택으로 쓸 임시 배열 (매 회전마다 재사용)
    char* stack = (char*)malloc(sizeof(char) * len);

    // x: 왼쪽으로 회전시키는 칸 수 (0 ~ len-1)
    for (int x = 0; x < len; x++) {
        int top = -1;        // 스택의 맨 위 인덱스 (-1이면 비어있음)
        bool valid = true;   // 이번 회전이 올바른 괄호 문자열인지 여부

        // 회전된 문자열을 순회: 실제 문자열을 만들지 않고
        // s[(x + i) % len] 형태로 인덱스만 x칸씩 밀어서 읽음
        for (int i = 0; i < len; i++) {
            char c = s[(x + i) % len];

            if (isOpen(c)) {
                // 여는 괄호면 스택에 push
                stack[++top] = c;
            } else {
                // 닫는 괄호인데 스택이 비어있거나 짝이 안 맞으면 실패
                if (top == -1 || getCloser(stack[top]) != c) {
                    valid = false;
                    break; // 더 검사할 필요 없이 이번 회전은 실패
                }
                top--; // 짝이 맞으면 pop
            }
        }

        // 순회를 끝까지 했는데 스택에 뭔가 남아있으면(짝이 안 맞은 여는 괄호) 실패
        if (valid && top != -1) {
            valid = false;
        }

        if (valid) {
            answer++;
        }
    }

    free(stack);
    return answer;
}