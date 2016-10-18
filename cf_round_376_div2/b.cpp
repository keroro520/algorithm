/*
 * ## 算法
 *   1. 能用折扣就用折扣
 *   2. 不能用折扣就用优惠券
 *
 * ## 注意点
 *   1. n = 2
 *      3 0
 *
 */
#include <algorithm>
#include <cstdio>

int main() {
    int n;
    int x;
    int acc = 0;
    bool flag = true;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &x);

        if (acc == 1) {
            if (x > 0) {
                x --;
            } else {
                flag = false;
                break;
            }
        }

        acc = x % 2;
    }

    if(acc == 0 && flag) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
