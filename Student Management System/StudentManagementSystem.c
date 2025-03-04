#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define FILENAME "students.dat"

// 学生结构体定义
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    float score;
} Student;

// 全局变量
Student students[MAX_STUDENTS];
int studentCount = 0;

// 函数声明
void displayMenu();
void addStudent();
void displayAllStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();
void saveDataToFile();
void loadDataFromFile();
void searchStudentByName();
void sortStudentsByScore();

int main() {
    int choice;
    
    // 程序启动时加载数据
    loadDataFromFile();
    
    do {
        displayMenu();
        printf("请输入您的选择 (1-9): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                saveDataToFile(); // 添加后保存数据
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                saveDataToFile(); // 修改后保存数据
                break;
            case 5:
                deleteStudent();
                saveDataToFile(); // 删除后保存数据
                break;
            case 6:
                searchStudentByName();
                break;
            case 7:
                sortStudentsByScore();
                break;
            case 8:
                saveDataToFile();
                printf("数据已保存到文件！\n");
                break;
            case 9:
                printf("感谢使用学生管理系统！再见！\n");
                break;
            default:
                printf("无效选择，请重新输入！\n\n");
        }
    } while (choice != 9);
    
    return 0;
}

// 显示菜单函数
void displayMenu() {
    printf("\n===== 学生管理系统 =====\n");
    printf("1. 添加学生信息\n");
    printf("2. 显示所有学生\n");
    printf("3. 按学号查询学生\n");
    printf("4. 修改学生信息\n");
    printf("5. 删除学生信息\n");
    printf("6. 按姓名查询学生\n");
    printf("7. 按成绩排序显示\n");
    printf("8. 保存数据到文件\n");
    printf("9. 退出系统\n");
    printf("========================\n");
}

// 添加学生信息
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("错误：学生数量已达上限！\n");
        return;
    }
    
    Student newStudent;
    
    printf("\n----- 添加学生信息 -----\n");
    
    printf("请输入学号: ");
    scanf("%d", &newStudent.id);
    
    // 检查学号是否已存在
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent.id) {
            printf("错误：该学号已存在！\n");
            return;
        }
    }
    
    printf("请输入姓名: ");
    scanf("%s", newStudent.name);
    
    printf("请输入年龄: ");
    scanf("%d", &newStudent.age);
    
    printf("请输入成绩: ");
    scanf("%f", &newStudent.score);
    
    students[studentCount] = newStudent;
    studentCount++;
    
    printf("学生信息添加成功！\n");
}

// 显示所有学生信息
void displayAllStudents() {
    if (studentCount == 0) {
        printf("\n没有学生信息可显示！\n");
        return;
    }
    
    printf("\n----- 所有学生信息 -----\n");
    printf("学号\t姓名\t\t年龄\t成绩\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%s\t\t%d\t%.2f\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].score);
    }
}

// 查询学生信息
void searchStudent() {
    if (studentCount == 0) {
        printf("\n没有学生信息可查询！\n");
        return;
    }
    
    int searchId;
    int found = 0;
    
    printf("\n----- 查询学生信息 -----\n");
    printf("请输入要查询的学号: ");
    scanf("%d", &searchId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            printf("\n找到学生信息：\n");
            printf("学号: %d\n", students[i].id);
            printf("姓名: %s\n", students[i].name);
            printf("年龄: %d\n", students[i].age);
            printf("成绩: %.2f\n", students[i].score);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("未找到该学号的学生！\n");
    }
}



// 修改学生信息
void modifyStudent() {
    if (studentCount == 0) {
        printf("\n没有学生信息可修改！\n");
        return;
    }
    
    int modifyId;
    int found = 0;
    
    printf("\n----- 修改学生信息 -----\n");
    printf("请输入要修改的学号: ");
    scanf("%d", &modifyId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == modifyId) {
            printf("\n当前学生信息：\n");
            printf("学号: %d\n", students[i].id);
            printf("姓名: %s\n", students[i].name);
            printf("年龄: %d\n", students[i].age);
            printf("成绩: %.2f\n\n", students[i].score);
            
            printf("请输入新的姓名: ");
            scanf("%s", students[i].name);
            
            printf("请输入新的年龄: ");
            scanf("%d", &students[i].age);
            
            printf("请输入新的成绩: ");
            scanf("%f", &students[i].score);
            
            printf("学生信息修改成功！\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("未找到该学号的学生！\n");
    }
}



// 删除学生信息
void deleteStudent() {
    if (studentCount == 0) {
        printf("\n没有学生信息可删除！\n");
        return;
    }
    
    int deleteId;
    int found = 0;
    
    printf("\n----- 删除学生信息 -----\n");
    printf("请输入要删除的学号: ");
    scanf("%d", &deleteId);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == deleteId) {
            // 将后面的学生信息前移
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            
            studentCount--;
            printf("学生信息删除成功！\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("未找到该学号的学生！\n");
    }
}

// 保存数据到文件
void saveDataToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("错误：无法打开文件进行写入！\n");
        return;
    }
    
    // 写入学生数量
    fwrite(&studentCount, sizeof(int), 1, file);
    
    // 写入学生数据
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

// 从文件加载数据
void loadDataFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("提示：没有找到数据文件，将创建新文件。\n");
        return;
    }
    
    // 读取学生数量
    fread(&studentCount, sizeof(int), 1, file);
    
    // 读取学生数据
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    printf("已从文件加载 %d 条学生记录。\n", studentCount);
}

// 按姓名查询学生
void searchStudentByName() {
    if (studentCount == 0) {
        printf("\n没有学生信息可查询！\n");
        return;
    }
    
    char searchName[NAME_LENGTH];
    int found = 0;
    
    printf("\n----- 按姓名查询学生信息 -----\n");
    printf("请输入要查询的姓名: ");
    scanf("%s", searchName);
    
    printf("\n查询结果：\n");
    printf("学号\t姓名\t\t年龄\t成绩\n");
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, searchName) == 0) {
            printf("%d\t%s\t\t%d\t%.2f\n", 
                   students[i].id, 
                   students[i].name, 
                   students[i].age, 
                   students[i].score);
            found = 1;
        }
    }
    
    if (!found) {
        printf("未找到姓名为 %s 的学生！\n", searchName);
    }
}

// 按成绩排序显示学生
void sortStudentsByScore() {
    if (studentCount == 0) {
        printf("\n没有学生信息可排序！\n");
        return;
    }
    
    // 创建临时数组进行排序，不影响原始数据顺序
    Student tempStudents[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) {
        tempStudents[i] = students[i];
    }
    
    // 冒泡排序 - 按成绩降序排列
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (tempStudents[j].score < tempStudents[j + 1].score) {
                Student temp = tempStudents[j];
                tempStudents[j] = tempStudents[j + 1];
                tempStudents[j + 1] = temp;
            }
        }
    }
    
    // 显示排序后的结果
    printf("\n----- 按成绩降序排列的学生信息 -----\n");
    printf("排名\t学号\t姓名\t\t年龄\t成绩\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%d\t%s\t\t%d\t%.2f\n", 
               i + 1,
               tempStudents[i].id, 
               tempStudents[i].name, 
               tempStudents[i].age, 
               tempStudents[i].score);
    }
}