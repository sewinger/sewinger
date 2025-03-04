#include <stdio.h>

// 函数声明
double celsiusToFahrenheit(double celsius);
double fahrenheitToCelsius(double fahrenheit);
void displayMenu();

int main() {
    int choice;
    double temperature, result;
    
    do {
        // 显示菜单
        displayMenu();
        
        // 获取用户选择
        printf("请输入您的选择 (1-3): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                // 摄氏度转华氏度
                printf("请输入摄氏温度: ");
                scanf("%lf", &temperature);
                result = celsiusToFahrenheit(temperature);
                printf("%.2lf 摄氏度 = %.2lf 华氏度\n\n", temperature, result);
                break;
                
            case 2:
                // 华氏度转摄氏度
                printf("请输入华氏温度: ");
                scanf("%lf", &temperature);
                result = fahrenheitToCelsius(temperature);
                printf("%.2lf 华氏度 = %.2lf 摄氏度\n\n", temperature, result);
                break;
                
            case 3:
                // 退出程序
                printf("感谢使用温度转换器！再见！\n");
                break;
                
            default:
                printf("无效选择，请重新输入！\n\n");
        }
        
    } while (choice != 3);
    
    return 0;
}

// 显示菜单函数
void displayMenu() {
    printf("===== 温度转换器 =====\n");
    printf("1. 摄氏度转华氏度\n");
    printf("2. 华氏度转摄氏度\n");
    printf("3. 退出程序\n");
    printf("=====================\n");
}

// 摄氏度转华氏度函数
double celsiusToFahrenheit(double celsius) {
    return celsius * 1.8 + 32;
}

// 华氏度转摄氏度函数
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32) / 1.8;
}