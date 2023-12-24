#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define READ "(%d,%39[^,],%d)\n"
#define WRITE "(%d,%s,%d)\n"

struct content {
    int id;
    char name[40];
    int price;
};

struct content info[MAX];
FILE *file; // object for file
int no;     // no of products from 1

void init();
void add();
void rem();
void rearrange(int);
void bill();

int main() {
    file = fopen("details.txt", "r+");

    init();

    st:
    printf("\n\n\n-----------------------------------\n");
    printf("| SUPER MARKET MANAGEMENT SYSTEM |\n");
    printf("-----------------------------------\n");
    printf("| ENTER A OPTION BELOW           |\n");
    printf("|  1. ADD A PRODUCT              |\n");
    printf("|  2. REMOVE A PRODUCT           |\n");
    printf("|  3. BILL                       |\n");
    printf("|  4. QUIT                       |\n");
    printf("-----------------------------------\n");
    printf("| OPTION : ");
    int op;
    scanf("%d",&op);
    printf("-----------------------------------\n");

    switch (op) {
        case 1:
            add();
            goto st;
            break;
        case 2:
            rem();
            goto st;
            break;
        case 3:
            bill();
            goto st;
            break;
        case 4:
            goto end;
        default:
            printf("ENTER THE CORRECT VALUE\n-----------------------------------\n");
            goto st;
            break;
    }

    end:
    printf("THANKS FOR USING SUPER MARKET MANAGEMENT SYSTEM");
    fclose(file);
    return 0;
}

void init() {
    int n = 1;
    for (int i = 0; i < MAX; i++) {
        info[i].id = 0;
        info[i].price = 0;
        strcpy(info[i].name, "");
    }

    fseek(file, 0, SEEK_SET);
    while (fscanf(file, READ, &info[n].id, &info[n].name, &info[n].price) == 3) {
        n++;
    }
    no = n - 1;
}

void add() {
    
    no += 1;
    printf("\n\n| ENTER THE DETAILS              |\n");
    printf("| REPLACE SPACES WITH UNDERSCORE |");
    printf("-----------------------------------\n\n");
    printf("| PRODUCT NAME :");
    scanf("%s", info[no].name);
    printf("| PRODUCT PRICE : ");
    scanf("%d", &info[no].price);
    info[no].id = no;

    fseek(file, 0, SEEK_END);
    fprintf(file, WRITE, info[no].id, info[no].name, info[no].price);
    
    printf("| PRODUCT ADDED SUCESSFULLY      |");
    printf("\n-----------------------------------\n");
    printf("\nPress Any Key to Continue.....\n");
    getchar();
}

void rem() {
    printf("\n\n| PRODUCTS:(ID,NAME,PRICE)       |\n-----------------------------------\n");
    int n = 1;
    while (n <= no) {
        printf("| %d. %s = %d\n", info[n].id, info[n].name, info[n].price);
        n++;
    }
    printf("-----------------------------------\n");
    printf("\nENTER THE ID OF THE PRODUCT TO BE REMOVED : ");
    int r;
    scanf("%d",&r);
    rearrange(r);
}
void rearrange(int r) {
    
    for (int i = r; i < no; i++) {
        info[i].id = info[i + 1].id-1;
        strcpy(info[i].name, info[i + 1].name);
        info[i].price = info[i + 1].price;
    }
    no -= 1;
    
    fclose(file);
    file = fopen("details.txt","w");
    fclose(file);
    file = fopen("details.txt","r+");
    
    fseek(file, 0, SEEK_SET);
    
    for (int i = 1; i <= no; i++) {
        fprintf(file, WRITE, info[i].id, info[i].name, info[i].price);
    }

    printf("| PRODUT REMOVED SUCESSFULLY     |\n\n");
    printf("-----------------------------------\n");
    printf("Press Any Key to Continue.....\n");
    getchar();
}

void bill(){
    printf("| BILLING SYSTEM                 |\n");
    printf("-----------------------------------\n");

    printf("\n\n| PRODUCTS:(ID,NAME,PRICE)       |\n-----------------------------------\n");
    int n = 1;
    while (n <= no) {
        printf("| %d. %s = %d\n", info[n].id, info[n].name, info[n].price);
        n++;
    }
    
    int num=1,c,id[100],qty[100];
    while(1){
        enter:
        printf("-----------------------------------\n");
        printf("| ENTER 1 TO ADD ITEMS           |\n");
        printf("| ENTER 0 TO BILL ENTERED ITEMS  |\n");
        printf("| OPTION : ");
        scanf("%d",&c);
        if(c<0 || c>1){
            printf("| ENTER VALID INPUT\n");
            goto enter;
        }
        if(c==0){
            break;
        }
        
        printf("| ENTER ID : ");
        scanf("%d",&id[num]);
        printf("| ENTER QUANTITY : ");
        scanf("%d",&qty[num]);
        if(id[num]>no){
            printf("| ENTER CORRECT ID\n");
            goto enter;
        }
        num+=1;
    }
    num-=1;
    printf("-----------------------------------\n");
    printf("| BILL :(ID,NAME,PRICE,AMOUNT)   |\n");
    printf("-----------------------------------\n");
    int temp=1,total=0;
    while(temp <= num){
        total+=info[id[temp]].price*qty[temp];
        printf("%d. %s = %d = %d\n",temp,info[id[temp]].name,info[id[temp]].price,info[id[temp]].price*qty[temp]);
        temp++;
    }


    printf("-----------------------------------\n");
    printf("| TOTAL : %d\n",total);
    printf("-----------------------------------\n");
    printf("Press any key to continue......");
    getchar();
}

