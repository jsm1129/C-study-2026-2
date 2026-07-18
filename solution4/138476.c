#include <stdlib.h>

// 오름차순 비교 함수 (그룹핑을 위해 tangerine 정렬용)
int cmp_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// 내림차순 비교 함수 (개수 많은 순 정렬용)
int cmp_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int solution(int k, int tangerine[], size_t tangerine_len) {
    int answer = 0;
    int n = (int)tangerine_len;

    // tangerine 배열을 복사해서 정렬 (원본 보존하고 싶으면)
    int *arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = tangerine[i];
    }
    qsort(arr, n, sizeof(int), cmp_asc); // 같은 크기끼리 인접하도록 오름차순 정렬

    // 크기별 개수를 저장할 배열 (최대 종류 수는 n개를 넘을 수 없음)
    int *counts = (int*)malloc(sizeof(int) * n);
    int type_num = 0; // 서로 다른 크기의 종류 수

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && arr[j] == arr[i]) { // 같은 크기인 구간 찾기
            j++;
        }
        counts[type_num] = j - i; // 이 크기의 개수 저장
        type_num++;
        i = j; // 다음 크기 구간으로 이동
    }

    // 개수가 많은 순서로 정렬
    qsort(counts, type_num, sizeof(int), cmp_desc);

    // 개수 많은 크기부터 순서대로 k개가 될 때까지 채움
    int picked = 0;
    for (int t = 0; t < type_num; t++) {
        if (picked >= k) break;
        picked += counts[t];
        answer++;
    }

    free(arr);
    free(counts);

    return answer;
}