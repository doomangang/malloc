#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// ft_malloc.h 에 선언된 함수들
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void print_test_header(const char *title) {
    printf("\n%s====================================================%s\n", YELLOW, RESET);
    printf("%s[%s]%s\n", YELLOW, title, RESET);
    printf("%s====================================================%s\n", YELLOW, RESET);
}

void assert_str_equal(const char *s1, const char *s2, const char *test_name) {
    if (s1 && s2 && strcmp(s1, s2) == 0) {
        printf("%s✓ SUCCESS:%s %s\n", GREEN, RESET, test_name);
    } else {
        printf("%s✗ FAILED:%s %s (expected: \"%s\", got: \"%s\")\n", RED, RESET, test_name, s2, s1);
    }
}

int main() {
    char *tiny_ptr, *small_ptr, *large_ptr;
    char *realloc_ptr1, *realloc_ptr2, *realloc_ptr3;

    // ====================================================
    // 1. 기본 Malloc & Free 테스트
    // ====================================================
    print_test_header("1. BASIC MALLOC & FREE TESTS");

    printf("--- Allocating TINY, SMALL, LARGE blocks ---\n");
    tiny_ptr = (char *)malloc(32);
    strcpy(tiny_ptr, "tiny test");
    assert_str_equal(tiny_ptr, "tiny test", "TINY allocation and write");

    small_ptr = (char *)malloc(512);
    strcpy(small_ptr, "small test");
    assert_str_equal(small_ptr, "small test", "SMALL allocation and write");

    large_ptr = (char *)malloc(8192);
    strcpy(large_ptr, "large test");
    assert_str_equal(large_ptr, "large test", "LARGE allocation and write");

    printf("\n--- Current memory state ---\n");
    show_alloc_mem();

    printf("\n--- Freeing all blocks ---\n");
    free(tiny_ptr);
    free(small_ptr);
    free(large_ptr);
    printf("All blocks freed.\n");

    printf("\n--- Memory state after free ---\n");
    show_alloc_mem();

    // ====================================================
    // 2. Realloc 테스트
    // ====================================================
    print_test_header("2. REALLOC TESTS");

    // 2-1. Realloc - 축소
    printf("\n--- 2-1. Realloc - Shrinking ---\n");
    realloc_ptr1 = (char *)malloc(100);
    strcpy(realloc_ptr1, "12345678901234567890");
    printf("Original ptr: %p, content: \"%s\"\n", realloc_ptr1, realloc_ptr1);
    realloc_ptr1 = (char *)realloc(realloc_ptr1, 10);
    realloc_ptr1[9] = '\0'; // 문자열 잘라주기
    printf("Shrunk ptr:   %p, content: \"%s\"\n", realloc_ptr1, realloc_ptr1);
    assert_str_equal(realloc_ptr1, "123456789", "Shrinking realloc content check");

    printf("\n--- Memory state after shrinking ---\n");
    show_alloc_mem();
    free(realloc_ptr1);


    // 2-2. Realloc - 확장 (새 할당)
    printf("\n--- 2-2. Realloc - Growing (new allocation) ---\n");
    realloc_ptr2 = (char *)malloc(32);
    strcpy(realloc_ptr2, "original data");
    // 바로 옆에 다른 블록을 할당해서 in-place 확장이 불가능하게 만듦
    char* dummy = malloc(16);
    printf("Original ptr: %p, content: \"%s\"\n", realloc_ptr2, realloc_ptr2);
    realloc_ptr2 = (char *)realloc(realloc_ptr2, 128);
    printf("Grown ptr:    %p, content: \"%s\"\n", realloc_ptr2, realloc_ptr2);
    assert_str_equal(realloc_ptr2, "original data", "Growing realloc (new alloc) content check");
    printf("\n--- Memory state after growing (new alloc) ---\n");
    show_alloc_mem();
    free(realloc_ptr2);
    free(dummy);


    // 2-3. Realloc - 확장 (In-place, 병합) - **핵심 테스트**
    printf("\n--- 2-3. Realloc - Growing (in-place merge) ---\n");
    realloc_ptr3 = (char *)malloc(32);
    void* original_ptr_addr = realloc_ptr3;
    strcpy(realloc_ptr3, "in-place test");

    // 바로 옆에 블록을 할당했다가 바로 free 해서 병합 가능한 공간을 만듦
    char* next_block = malloc(64);
    free(next_block);
    printf("Allocated ptr1 at %p and ptr2, then freed ptr2.\n", original_ptr_addr);
    printf("--- Memory state before in-place realloc ---\n");
    show_alloc_mem();

    printf("Reallocating ptr1 from 32 to 80 bytes...\n");
    realloc_ptr3 = (char *)realloc(realloc_ptr3, 80);

    if (realloc_ptr3 == original_ptr_addr) {
         printf("%s✓ SUCCESS:%s In-place realloc successful (pointer did not change)\n", GREEN, RESET);
    } else {
         printf("%s✗ FAILED:%s In-place realloc failed (pointer changed from %p to %p)\n", RED, RESET, original_ptr_addr, realloc_ptr3);
    }
    assert_str_equal(realloc_ptr3, "in-place test", "In-place realloc content check");
    printf("\n--- Memory state after in-place realloc ---\n");
    show_alloc_mem();
    free(realloc_ptr3);

    // ====================================================
    // 3. 엣지 케이스 테스트
    // ====================================================
    print_test_header("3. EDGE CASE TESTS");
    // realloc(NULL, size) == malloc(size)
    char *realloc_null = realloc(NULL, 50);
    strcpy(realloc_null, "realloc_null test");
    assert_str_equal(realloc_null, "realloc_null test", "realloc(NULL, size)");
    free(realloc_null);

    // realloc(ptr, 0) == free(ptr)
    char *ptr_to_free = malloc(50);
    // realloc(ptr, 0) 의 반환값은 유효하지 않으므로 사용하면 안됨
    (void)realloc(ptr_to_free, 0);
    printf("✓ SUCCESS: realloc(ptr, 0) executed (should act like free)\n");

    // 0바이트 할당
    char *zero_byte = malloc(0);
    if (zero_byte == NULL) {
        printf("%s✓ SUCCESS:%s malloc(0) returned NULL as expected.\n", GREEN, RESET);
    } else {
        printf("%s✗ FAILED:%s malloc(0) should return NULL but returned %p.\n", RED, RESET, zero_byte);
    }

    printf("\n--- FINAL MEMORY STATE ---\n");
    show_alloc_mem();
    printf("\n%sAll tests finished!%s\n", GREEN, RESET);

    return (0);
}