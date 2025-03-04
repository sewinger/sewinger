#include <stdio.h>

int main() {
    double num1, num2, result;
    char operator;

    // 提示用户输入第一个数字
    printf("请输入第一个数字: ");
    scanf("%lf", &num1);

    // 提示用户输入运算符
    printf("请输入运算符 (+, -, *, /): ");
    scanf(" %c", &operator);

    // 提示用户输入第二个数字
    printf("请输入第二个数字: ");
    scanf("%lf", &num2);

    // 根据运算符进行相应的计算
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '/':
            if (num2 == 0) {
                printf("错误：除数不能为零。\n");
            } else {
                result = num1 / num2;
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
            }
            break;
        default:
            printf("错误：无效的运算符。\n");
    }

    return 0;
}