int solution(int n) {
    int answer = 0;           // 최종 반환할 결과값
    long long a = 0;          // F(0) 값 저장
    long long b = 1;          // F(1) 값 저장

    if (n == 0) return 0;     // n이 0이면 바로 0 반환
    if (n == 1) return 1;     // n이 1이면 바로 1 반환

    for (int i = 2; i <= n; i++) {           // F(2)부터 F(n)까지 순차 계산
        long long c = (a + b) % 1234567;     // 다음 피보나치 수 계산 후 나머지 저장
        a = b;                               // a를 한 칸 앞으로 이동 (이전 b값)
        b = c;                               // b를 새로 계산한 값으로 갱신
    }

    answer = (int)b;          // 최종 계산된 피보나치 수를 answer에 저장
    return answer;             // 결과 반환
}