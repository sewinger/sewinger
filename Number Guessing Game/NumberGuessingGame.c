#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int randomNumber, userGuess, attempts = 0;
    int playAgain = 1;
    
    // 初始化随机数生成器
    srand(time(NULL));
    
    printf("===== 猜数字小游戏 =====\n\n");
    
    while (playAgain) {
        // 生成1到100之间的随机数
        randomNumber = rand() % 100 + 1;
        attempts = 0;
        
        printf("我已经想好了一个1到100之间的数字。\n");
        printf("请开始猜测！\n\n");
        
        do {
            printf("请输入您的猜测: ");
            scanf("%d", &userGuess);
            attempts++;
            
            if (userGuess > randomNumber) {
                printf("太大了！再试一次。\n");
            } else if (userGuess < randomNumber) {
                printf("太小了！再试一次。\n");
            } else {
                printf("\n恭喜您！您猜对了！\n");
                printf("您用了 %d 次尝试。\n\n", attempts);
            }
            
        } while (userGuess != randomNumber);
        
        printf("是否要再玩一次？(1: 是, 0: 否): ");
        scanf("%d", &playAgain);
        printf("\n");
    }
    
    printf("感谢您玩猜数字游戏！再见！\n");
    
    return 0;
}