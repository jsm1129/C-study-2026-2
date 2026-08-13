#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// want_len은 배열 want의 길이
// number_len은 배열 number의 길이
// discount_len은 배열 discount의 길이
int solution(const char* want[], size_t want_len, int number[], size_t number_len, const char* discount[], size_t discount_len) {
    int answer = 0;

    // discount_len이 10보다 작으면 10일 연속 구간 자체가 불가능
    if (discount_len < 10) {
        return 0;
    }

    // 시작일(start)을 하나씩 옮겨가며 10일짜리 윈도우를 검사
    // 마지막 시작일은 discount_len - 10 (10일치를 확보할 수 있는 마지막 시작점)
    for (size_t start = 0; start <= discount_len - 10; start++) {

        // 이번 윈도우에서 각 want 제품이 몇 번 등장했는지 세는 카운트 배열
        int count[10] = {0}; // want_len은 최대 10이므로 크기 10으로 고정

        // 10일치 할인 품목을 세어봄
        for (int day = 0; day < 10; day++) {
            const char* product = discount[start + day];

            // 이 제품이 want 목록에 있는지 확인
            for (size_t w = 0; w < want_len; w++) {
                if (strcmp(product, want[w]) == 0) {
                    count[w]++;
                    break; // want 안에 중복 제품은 없으므로 찾으면 바로 종료
                }
            }
        }

        // 모든 want 제품의 개수가 number와 정확히 일치하는지 확인
        bool ok = true;
        for (size_t w = 0; w < want_len; w++) {
            if (count[w] != number[w]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            answer++; // 조건을 만족하는 회원등록 날짜 발견
        }
    }

    return answer;
}