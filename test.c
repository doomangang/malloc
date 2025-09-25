#include <stdio.h>
#include <string.h>

// 우리의 ft_malloc.h를 포함하는 대신,
// 표준 malloc 함수 프로토타입을 직접 선언하거나 <stdlib.h>를 포함합니다.
// 어차피 링커가 우리가 만든 함수로 바꿔치기할 것입니다.
#include <stdlib.h>

int main(void)
{
    char *ptr;

    printf("1. LARGE 할당 테스트 시작...\n");
    // 4096 바이트 할당 (LARGE 케이스)
    ptr = (char *)malloc(4096);
    if (!ptr)
    {
        printf("메모리 할당 실패!\n");
        return (1);
    }
    printf("할당된 주소: %p\n", ptr);

    // 할당된 메모리에 데이터 쓰기 테스트
    strcpy(ptr, "Hello Malloc!");
    printf("데이터 쓰기 테스트: \"%s\"\n", ptr);

    printf("2. FREE 테스트 시작...\n");
    free(ptr);
    printf("메모리 해제 완료.\n");

    // 이미 해제된 메모리에 접근 시도 (이론상으론 여기서 오류가 날 수 있음)
    // printf("해제 후 접근 테스트: %s\n", ptr);

    printf("테스트 성공!\n");
    return (0);
}