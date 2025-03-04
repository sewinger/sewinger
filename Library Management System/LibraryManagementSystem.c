#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 50
#define MAX_ID_LEN 20
#define MAX_BOOKS 1000
#define FILENAME "library.dat"

// 图书结构体定义
typedef struct {
    char id[MAX_ID_LEN];        // 图书ID
    char title[MAX_TITLE_LEN];   // 书名
    char author[MAX_AUTHOR_LEN];  // 作者
    int available;               // 是否可借阅(1:可借, 0:已借出)
    char borrower[MAX_AUTHOR_LEN]; // 借阅者姓名(如果已借出)
} Book;

// 全局变量
Book library[MAX_BOOKS];
int bookCount = 0;

// 函数声明
void displayMenu();
void addBook();
void displayAllBooks();
void searchBook();
void borrowBook();
void returnBook();
void saveToFile();
void loadFromFile();

int main() {
    int choice;
    
    // 从文件加载图书数据
    loadFromFile();
    
    do {
        displayMenu();
        printf("请输入您的选择 (1-7): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                saveToFile();
                printf("数据已保存到文件！\n");
                break;
            case 7:
                saveToFile(); // 退出前保存数据
                printf("感谢使用图书管理系统！再见！\n");
                break;
            default:
                printf("无效选择，请重新输入！\n\n");
        }
    } while (choice != 7);
    
    return 0;
}

// 显示菜单函数
void displayMenu() {
    printf("\n===== 图书管理系统 =====\n");
    printf("1. 添加新书\n");
    printf("2. 显示所有图书\n");
    printf("3. 查询图书\n");
    printf("4. 借阅图书\n");
    printf("5. 归还图书\n");
    printf("6. 保存数据\n");
    printf("7. 退出系统\n");
    printf("========================\n");
}

// 添加新书
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("错误：图书数量已达上限！\n");
        return;
    }
    
    Book newBook;
    
    printf("\n----- 添加新书 -----\n");
    
    printf("请输入图书ID: ");
    scanf("%s", newBook.id);
    
    // 检查ID是否已存在
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].id, newBook.id) == 0) {
            printf("错误：该图书ID已存在！\n");
            return;
        }
    }
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    printf("请输入书名: ");
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // 移除换行符
    
    printf("请输入作者: ");
    fgets(newBook.author, MAX_AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // 移除换行符
    
    newBook.available = 1; // 新书默认可借阅
    strcpy(newBook.borrower, ""); // 无借阅者
    
    library[bookCount] = newBook;
    bookCount++;
    
    printf("图书添加成功！\n");
}

// 显示所有图书
void displayAllBooks() {
    if (bookCount == 0) {
        printf("\n图书馆中没有图书！\n");
        return;
    }
    
    printf("\n----- 所有图书信息 -----\n");
    printf("ID\t书名\t\t作者\t\t状态\t\t借阅者\n");
    
    for (int i = 0; i < bookCount; i++) {
        printf("%s\t%.20s\t%.15s\t%s\t%s\n", 
               library[i].id, 
               library[i].title, 
               library[i].author, 
               library[i].available ? "可借阅" : "已借出",
               library[i].available ? "-" : library[i].borrower);
    }
}

// 查询图书
void searchBook() {
    if (bookCount == 0) {
        printf("\n图书馆中没有图书！\n");
        return;
    }
    
    char searchTerm[MAX_TITLE_LEN];
    int found = 0;
    int searchType;
    
    printf("\n----- 查询图书 -----\n");
    printf("1. 按ID查询\n");
    printf("2. 按书名查询\n");
    printf("3. 按作者查询\n");
    printf("请选择查询方式: ");
    scanf("%d", &searchType);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    printf("请输入查询关键词: ");
    fgets(searchTerm, MAX_TITLE_LEN, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0; // 移除换行符
    
    printf("\n----- 查询结果 -----\n");
    printf("ID\t书名\t\t作者\t\t状态\t\t借阅者\n");
    
    for (int i = 0; i < bookCount; i++) {
        int match = 0;
        
        switch(searchType) {
            case 1: // 按ID查询
                if (strcmp(library[i].id, searchTerm) == 0) match = 1;
                break;
            case 2: // 按书名查询
                if (strstr(library[i].title, searchTerm) != NULL) match = 1;
                break;
            case 3: // 按作者查询
                if (strstr(library[i].author, searchTerm) != NULL) match = 1;
                break;
            default:
                printf("无效的查询方式！\n");
                return;
        }
        
        if (match) {
            printf("%s\t%.20s\t%.15s\t%s\t%s\n", 
                   library[i].id, 
                   library[i].title, 
                   library[i].author, 
                   library[i].available ? "可借阅" : "已借出",
                   library[i].available ? "-" : library[i].borrower);
            found = 1;
        }
    }
    
    if (!found) {
        printf("未找到匹配的图书！\n");
    }
}

// 借阅图书
void borrowBook() {
    if (bookCount == 0) {
        printf("\n图书馆中没有图书！\n");
        return;
    }
    
    char bookId[MAX_ID_LEN];
    char borrowerName[MAX_AUTHOR_LEN];
    int found = 0;
    
    printf("\n----- 借阅图书 -----\n");
    printf("请输入要借阅的图书ID: ");
    scanf("%s", bookId);
    
    // 清除输入缓冲区
    while (getchar() != '\n');
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].id, bookId) == 0) {
            found = 1;
            
            if (library[i].available) {
                printf("请输入借阅者姓名: ");
                fgets(borrowerName, MAX_AUTHOR_LEN, stdin);
                borrowerName[strcspn(borrowerName, "\n")] = 0; // 移除换行符
                
                library[i].available = 0;
                strcpy(library[i].borrower, borrowerName);
                
                printf("借阅成功！\n");
            } else {
                printf("该图书已被借出，当前借阅者: %s\n", library[i].borrower);
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("未找到该ID的图书！\n");
    }
}

// 归还图书
void returnBook() {
    if (bookCount == 0) {
        printf("\n图书馆中没有图书！\n");
        return;
    }
    
    char bookId[MAX_ID_LEN];
    int found = 0;
    
    printf("\n----- 归还图书 -----\n");
    printf("请输入要归还的图书ID: ");
    scanf("%s", bookId);
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].id, bookId) == 0) {
            found = 1;
            
            if (!library[i].available) {
                library[i].available = 1;
                strcpy(library[i].borrower, "");
                
                printf("图书归还成功！\n");
            } else {
                printf("该图书未被借出，无需归还！\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("未找到该ID的图书！\n");
    }
}

// 保存数据到文件
void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    
    if (file == NULL) {
        printf("错误：无法打开文件进行写入！\n");
        return;
    }
    
    // 写入图书数量
    fwrite(&bookCount, sizeof(int), 1, file);
    
    // 写入所有图书数据
    for (int i = 0; i < bookCount; i++) {
        fwrite(&library[i], sizeof(Book), 1, file);
    }
    
    fclose(file);
}

// 从文件加载数据
void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    
    if (file == NULL) {
        printf("提示：未找到数据文件，将创建新的图书库。\n");
        return;
    }
    
    // 读取图书数量
    fread(&bookCount, sizeof(int), 1, file);
    
    // 读取所有图书数据
    for (int i = 0; i < bookCount; i++) {
        fread(&library[i], sizeof(Book), 1, file);
    }
    
    fclose(file);
    printf("已从文件加载 %d 本图书数据。\n", bookCount);
}