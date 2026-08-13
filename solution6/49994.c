#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어짐
int solution(const char* dirs) {
    int answer = 0;

    // 좌표는 -5~5 이므로 +5 오프셋을 줘서 0~10 범위로 사용
    // visited[x][y][dir] : (x,y) 좌표에서 dir 방향으로 이미 지나간 길인지 여부
    // dir: 0=U, 1=D, 2=L, 3=R
    static bool visited[11][11][4];
    memset(visited, false, sizeof(visited));

    int x = 5, y = 5; // (0,0)을 (5,5)로 매핑

    // 이동 방향에 따른 델타값과, 반대 방향(역방향) 인덱스를 매핑
    // U(0)의 반대는 D(1), D(1)의 반대는 U(0), L(2)의 반대는 R(3), R(3)의 반대는 L(2)
    int dx[4] = {0, 0, -1, 1};   // U, D, L, R 순서에 대응하는 x 변화량
    int dy[4] = {1, -1, 0, 0};   // U, D, L, R 순서에 대응하는 y 변화량
    int opp[4] = {1, 0, 3, 2};   // 각 방향의 반대 방향 인덱스

    int len = strlen(dirs);
    for (int i = 0; i < len; i++) {
        int dir;
        switch (dirs[i]) {
            case 'U': dir = 0; break;
            case 'D': dir = 1; break;
            case 'L': dir = 2; break;
            case 'R': dir = 3; break;
            default: continue; // 문제 조건상 발생하지 않지만 안전하게 처리
        }

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 좌표평면 경계(-5~5, 오프셋 적용 후 0~10)를 벗어나면 이 명령은 무시
        if (nx < 0 || nx > 10 || ny < 0 || ny > 10) {
            continue;
        }

        // 아직 지나가지 않은 길이라면 처음 걸어본 길이므로 카운트
        if (!visited[x][y][dir]) {
            visited[x][y][dir] = true;          // 현재 좌표에서 해당 방향으로 지나감을 기록
            visited[nx][ny][opp[dir]] = true;    // 도착 좌표에서 반대 방향으로도 같은 길이므로 함께 기록
            answer++;
        }

        // 이동 (경계를 넘지 않는 유효한 이동이므로 실제로 위치 갱신)
        x = nx;
        y = ny;
    }

    return answer;
}