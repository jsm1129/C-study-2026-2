#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int x, int y, int n) {
    int answer = 0;

    // dp[i] : x에서 i까지 도달하는 데 필요한 최소 연산 횟수
    // 아직 도달하지 못했으면 -1로 초기화
    int size = y + 1;
    int *dp = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        dp[i] = -1;  // 초기값: 도달 불가능
    }
    dp[x] = 0;  // 시작점 x는 0번의 연산으로 도달

    // x부터 y까지 순서대로 돌면서
    // 현재 값(i)에서 갈 수 있는 다음 값들을 갱신
    for (int i = x; i < y; i++) {
        if (dp[i] == -1) continue;  // i에 아직 도달 못했으면 스킵

        // 연산 1: ×2
        if ((long long)i * 2 <= y) {
            int next = i * 2;
            // 처음 도달했거나, 더 적은 횟수로 도달 가능하면 갱신
            if (dp[next] == -1 || dp[next] > dp[i] + 1) {
                dp[next] = dp[i] + 1;
            }
        }

        // 연산 2: ×3
        if ((long long)i * 3 <= y) {
            int next = i * 3;
            if (dp[next] == -1 || dp[next] > dp[i] + 1) {
                dp[next] = dp[i] + 1;
            }
        }

        // 연산 3: +n
        if (i + n <= y) {
            int next = i + n;
            if (dp[next] == -1 || dp[next] > dp[i] + 1) {
                dp[next] = dp[i] + 1;
            }
        }
    }

    answer = dp[y];  // y까지 도달 못했으면 -1, 도달했으면 최소 횟수

    free(dp);
    return answer;
}