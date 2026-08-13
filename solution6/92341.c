#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// "HH:MM" 형태의 문자열을 분 단위 정수로 변환
static int toMinutes(const char* hhmm) {
    int h = (hhmm[0] - '0') * 10 + (hhmm[1] - '0');
    int m = (hhmm[3] - '0') * 10 + (hhmm[4] - '0');
    return h * 60 + m;
}

// fees_len은 배열 fees의 길이
// records_len은 배열 records의 길이
int* solution(int fees[], size_t fees_len, const char* records[], size_t records_len) {
    int dt = fees[0]; // 기본시간
    int df = fees[1]; // 기본요금
    int ut = fees[2]; // 단위시간
    int uf = fees[3]; // 단위요금

    // 차량번호(0000~9999)를 인덱스로 사용 -> 자연스럽게 오름차순 정렬 효과
    static int inTime[10000];       // 현재 입차 중인 차량의 입차 시각, -1이면 미입차
    static long long totalTime[10000]; // 차량별 누적 주차 시간
    static bool isUsed[10000];      // 이 차량번호가 등장했는지 여부

    // static 배열이므로 매 호출마다 반드시 초기화 필요
    for (int i = 0; i < 10000; i++) {
        inTime[i] = -1;
        totalTime[i] = 0;
        isUsed[i] = false;
    }

    // 1. 기록을 순서대로 읽으며 입/출차 시간을 누적
    for (size_t i = 0; i < records_len; i++) {
        char timeStr[6] = {0};
        char carStr[5] = {0};
        char state[4] = {0};

        // "HH:MM 차량번호 IN/OUT" 파싱 (records[i]는 const라 sscanf로 복사해서 사용)
        sscanf(records[i], "%5s %4s %3s", timeStr, carStr, state);

        int carNum = atoi(carStr);
        int t = toMinutes(timeStr);

        isUsed[carNum] = true;

        if (strcmp(state, "IN") == 0) {
            inTime[carNum] = t; // 입차 시각 기록
        } else {
            // 출차: 이번 입차~출차 구간 시간을 누적
            totalTime[carNum] += (t - inTime[carNum]);
            inTime[carNum] = -1;
        }
    }

    // 2. 출차 기록 없이 끝까지 입차 상태인 차량 -> 23:59 출차로 간주
    for (int car = 0; car < 10000; car++) {
        if (inTime[car] != -1) {
            totalTime[car] += (23 * 60 + 59) - inTime[car];
        }
    }

    // 3. 등장한 차량 수 세기
    int count = 0;
    for (int car = 0; car < 10000; car++) {
        if (isUsed[car]) count++;
    }

    // 4. 결과 배열 동적 할당
    int* answer = (int*)malloc(sizeof(int) * count);
    int idx = 0;

    // 5. 차량번호 오름차순으로 요금 계산
    for (int car = 0; car < 10000; car++) {
        if (!isUsed[car]) continue;

        long long time = totalTime[car];
        int fee;

        if (time <= dt) {
            fee = df; // 기본시간 이하면 기본요금
        } else {
            long long over = time - dt;
            long long units = (over + ut - 1) / ut; // 올림 처리
            fee = df + (int)(units * uf);
        }

        answer[idx++] = fee;
    }

    return answer;
}