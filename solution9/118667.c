#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int queue1[], size_t queue1_len, int queue2[], size_t queue2_len) {
    int answer = -2;

    size_t n1 = queue1_len;
    size_t n2 = queue2_len;
    size_t total_len = n1 + n2;  // 두 큐를 합친 전체 원소 개수 (원형 큐 배열 크기로 사용)

    // 각 큐를 원형 큐(circular buffer)로 쓰기 위해 total_len 크기로 넉넉하게 할당
    int *q1 = (int *)malloc(sizeof(int) * total_len);
    int *q2 = (int *)malloc(sizeof(int) * total_len);

    long long sum1 = 0, sum2 = 0;  // 각 큐의 원소 합 (int 범위 초과 대비 long long)
    int max_val = 0;  // 두 큐를 합친 원소 중 최댓값

    // queue1 복사 + 합 계산 + 최댓값 갱신
    for (size_t i = 0; i < n1; i++) {
        q1[i] = queue1[i];
        sum1 += queue1[i];
        if (queue1[i] > max_val) max_val = queue1[i];
    }
    // queue2 복사 + 합 계산 + 최댓값 갱신
    for (size_t i = 0; i < n2; i++) {
        q2[i] = queue2[i];
        sum2 += queue2[i];
        if (queue2[i] > max_val) max_val = queue2[i];
    }

    long long total = sum1 + sum2;  // 두 큐의 전체 합

    // 조건 1: 총합이 홀수면 절반으로 정확히 나눌 수 없으므로 절대 불가능
    if (total % 2 != 0) {
        free(q1);
        free(q2);
        return -1;
    }

    long long target = total / 2;  // 각 큐가 도달해야 할 목표 합

    // 조건 2: 원소 중 최댓값이 target보다 크면 절대 불가능
    if ((long long)max_val > target) {
        free(q1);
        free(q2);
        return -1;
    }

    // front: 다음에 뺄 원소의 인덱스, rear: 다음에 넣을 위치의 인덱스
    // [front, rear) 구간이 현재 큐에 들어있는 유효한 원소들
    size_t front1 = 0, rear1 = n1;
    size_t front2 = 0, rear2 = n2;

    int count = 0;  // 지금까지 수행한 이동(옮기기) 횟수 = 최종 answer 후보

    // 위 두 조건(합이 짝수, 최댓값 ≤ target)을 통과했다면 이론적으로 반드시 유한 횟수 안에 sum1 == sum2가 됨
    long long limit = (long long)total_len * 4;

    // 두 큐의 합이 같아질 때까지 반복
    while (sum1 != sum2) {
        if (count > limit) {
            // 이론상 도달할 일 없지만, 방어 코드로 남겨둠
            free(q1);
            free(q2);
            return -1;
        }

        if (sum1 > sum2) {
            // sum1이 더 크면 q1의 맨 앞 원소를 빼서 q2의 맨 뒤에 넣음
            int val = q1[front1 % total_len];  // 모듈러 연산으로 원형 큐 인덱스 처리
            front1++;                          // q1의 front를 한 칸 전진 (빼낸 것으로 처리)

            q2[rear2 % total_len] = val;       // q2의 rear 위치에 값 삽입
            rear2++;                           // q2의 rear를 한 칸 전진

            sum1 -= val;  // 빠진 만큼 sum1 감소
            sum2 += val;  // 들어온 만큼 sum2 증가
        } else {
            // sum2가 더 크거나 같으면 q2의 맨 앞 원소를 빼서 q1의 맨 뒤에 넣음
            int val = q2[front2 % total_len];
            front2++;

            q1[rear1 % total_len] = val;
            rear1++;

            sum2 -= val;
            sum1 += val;
        }

        count++;  // 이동 1회 수행했으므로 카운트 증가
    }

    answer = count;  // 두 합이 같아지는 데 걸린 최소 이동 횟수

    free(q1);
    free(q2);
    return answer;
}