#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool solution(vector<string> phone_book) {
    // 사전순 정렬 (접두사 관계면 서로 인접하게 됨)
    sort(phone_book.begin(), phone_book.end());

    // 인접한 문자열끼리만 비교
    for (int i = 0; i < (int)phone_book.size() - 1; i++) {
        // 앞 번호가 뒤 번호의 접두사인지 확인
        if (phone_book[i+1].compare(0, phone_book[i].size(), phone_book[i]) == 0) {
            return false;
        }
    }

    return true;
}