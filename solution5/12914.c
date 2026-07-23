#include <string.h>

long long solution(int n) {
    long long dp[2001]; // n칸까지의 경우의 수 저장
    memset(dp, 0, sizeof(dp));

    dp[1] = 1; // 1칸: 1가지
    dp[2] = 2; // 2칸: 2가지 (1+1 또는 2)

    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 1234567; // 직전 두 값의 합
    }

    return dp[n];
}