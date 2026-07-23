long long gcd(long long a, long long b) {
    // 유클리드 호제법: b가 0이 될 때까지 a를 b로, b를 a%b로 교체
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    // 두 수의 최소공배수 = (a * b) / gcd(a, b)
    // a를 먼저 gcd로 나눈 뒤 b를 곱해서 오버플로우 위험 줄임
    return a / gcd(a, b) * b;
}

int solution(int arr[], int n) {
    long long result = arr[0]; // 첫 번째 값부터 시작

    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]); // 지금까지의 lcm과 다음 원소의 lcm을 누적
    }

    return (int)result; // 최종 결과를 int로 캐스팅해서 반환
}