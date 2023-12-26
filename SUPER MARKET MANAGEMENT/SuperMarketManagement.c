#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define READ "(%d,%39[^,],%d,%d)\n"
#define WRITE "(%d,%s,%d,%d)\n"

struct content {
    int id;
    char name[40];
    int price;
    int stock;
};

struct content info[MAX];
FILE *file; // object for file
int no;     // no of products from 1

void init();
void add();
void rem();
void rearrange(int);
void bill();
void update();
void display();
void read_write();

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
    printf("|  3. UPDATE DETAILS             |\n");
    printf("|  4. BILL                       |\n");
    printf("|  5. VIEW                       |\n");
    printf("|  6. QUIT                       |\n");
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
            update();
            goto st;
            break;
        case 4:
            bill();
            goto st;
            break;
        case 5:
            display();
            goto st;
            break;
        case 6:
            goto end;
        default:
            printf("ENTER THE CORRECT VALUE\n-----------------------------------\n");
            goto st;
            break;
    }

    end:
    printf("THANKS FOR USING SUPER MARKET MANAGEMENT SYSTEMn\n\n\n");
    fclose(file);
    return 0;
}

void init() {
    int n = 1;
    for (int i = 0; i < MAX; i++) {
        info[i].id = 0;
        info[i].price = 0;
        strcpy(info[i].name, "");
        info[i].stock = 0;
    }

    fseek(file, 0, SEEK_SET);
    while (fscanf(file, READ, &info[n].id, &info[n].name, &info[n].price,&info[n].stock) == 4) {
        n++;
    }
    no = n - 1;
}

void add() {
    
    no += 1;
    printf("\n-----------------------------------\n");
    printf("| ENTER THE DETAILS              |\n");
    printf("| REPLACE SPACES WITH UNDERSCORE |\n");
    printf("-----------------------------------\n\n");
    printf("| PRODUCT NAME :");
    scanf("%s", info[no].name);
    printf("| PRODUCT PRICE : ");
    scanf("%d", &info[no].price);
    printf("| PRODUCT STOCK : ");
    scanf("%d", &info[no].stock);
    info[no].id = no;

    fseek(file, 0, SEEK_END);
    fprintf(file, WRITE, info[no].id, info[no].name, info[no].price,info[no].stock);
    
    printf("| PRODUCT ADDED SUCESSFULLY      |");
    printf("\n-----------------------------------\n");
    printf("\nPress Any Key to Continue.....\n");
    getchar();
    getchar();
}

void rem() {
    display();
    printf("-----------------------------------\n");
    printf("\nENTER THE ID OF THE PRODUCT TO BE REMOVED : ");
    int r;
    scanf("%d",&r);
    rearrange(r);

    printf("| PRODUT REMOVED SUCESSFULLY     |\n\n");
    printf("-----------------------------------\n");
    printf("Press Any Key to Continue.....\n");
    getchar();
    getchar();
}


void update(){
    display();
    int n,num;
    printf("\n-----------------------------------\n");
    printf("| ENTER THE ID TO BE UPDATED : ");
    scanf("%d",&n);
    name:
    printf("-----------------------------------\n");
    printf("| ENTER 1 TO UPDATE NAME\n");
    printf("| ENTER 0 TO SKIP UDATING NAME\n");
    printf("| OPTION : ");
    scanf("%d",&num);
    if(num==1){
        printf("| NAME : ");
        scanf("%s",&info[num].name);
    }else if(num==0){}
    else{
        printf("| WRONG INPUT                    |");
        goto name;
    }
    price:
    printf("-----------------------------------\n");
    printf("| ENTER 1 TO UPDATE PRICE\n");
    printf("| ENTER 0 TO SKIP UDATING PRICE\n");
    printf("| OPTION : ");
    scanf("%d",&num);
    if(num==1){
        printf("| PRICE : ");
        scanf("%d]",&info[num].price);
    }else if(num==0){}
    else{
        printf("| WRONG INPUT                    |");
        goto price;
    }
    stock:
    printf("-----------------------------------\n");
    printf("| ENTER 1 TO UPDATE STOCK (to add with existing)\n");
    printf("| ENTER 0 TO SKIP UDATING STOCK\n");
    printf("| OPTION : ");
    scanf("%d",&num);
    if(num==1){
        printf("| STOCK : ");
        int temp;
        scanf("%d",&temp);
        info[num].stock+=temp;
    }else if(num==0){}
    else{
        printf("| WRONG INPUT                    |");
        goto stock;
    }
    read_write();

    printf("-----------------------------------\n");
    printf("| ID HAS BEEN UPDATED            |");
    printf("\n-----------------------------------\n");
    printf("Press any key to continue......");
    getchar();
    getchar();

}

void bill(){
    printf("| BILLING SYSTEM                 |\n");
    printf("-----------------------------------\n");

    
    display();
    
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
        if(info[id[num]].stock < qty[num]){
            printf("| PRODUCT OUT OF STOCK\n");
            goto enter;
        }
        num+=1;
    }
    num-=1;
    printf("\n\n-------------------------------------------------\n");
    printf("| BILL :(ID,NAME,PRICE,AMOUNT)   |\n");
    printf("-------------------------------------------------\n");
    int temp=1,total=0;
    while(temp <= num){
        total+=info[id[temp]].price*qty[temp];
        if(strlen(info[id[temp]].name)>=10){
            printf("%d. %s \t%d \t %d \t%d\n",temp,info[id[temp]].name,info[id[temp]].price,qty[temp],info[id[temp]].price*qty[temp]);
        }else if(strlen(info[id[temp]].name)<=3){
            printf("%d. %s \t\t\t%d \t %d\t%d\n",temp,info[id[temp]].name,info[id[temp]].price,qty[temp],info[id[temp]].price*qty[temp]);
        }else{
            printf("%d. %s \t\t%d \t %d\t%d\n",temp,info[id[temp]].name,info[id[temp]].price,qty[temp],info[id[temp]].price*qty[temp]);
        }
        info[id[temp]].stock-=qty[temp];
        temp++;
    }


    printf("-------------------------------------------------\n");
    printf("| TOTAL : \t\t\t\t%d\n",total);
    printf("-------------------------------------------------\n");
    printf("Press any key to continue......");

    read_write();

    getchar();
    getchar();
}

void rearrange(int r) { 
    
    for (int i = r; i < no; i++) {
        info[i].id = info[i + 1].id-1;
        strcpy(info[i].name, info[i + 1].name);
        info[i].price = info[i + 1].price;
        info[i].stock = info[i + 1].stock;
    }
    no -= 1;
    
    read_write();
}

void display(){
    printf("\n\n| PRODUCTS:(ID,NAME,PRICE)       |\n-----------------------------------\n");
    int n = 1;
    while (n <= no) {
        if(strlen(info[n].name)>=10){
            printf("| %d. %s \t %d \t %d\n", info[n].id, info[n].name, info[n].price,info[n].stock);
        }else{
            printf("| %d. %s \t\t %d \t %d\n", info[n].id, info[n].name, info[n].price,info[n].stock);
        }
        n++;
    }
}

void read_write(){
    fclose(file);
    file = fopen("details.txt","w");
    fclose(file);
    file = fopen("details.txt","r+");
    
    fseek(file, 0, SEEK_SET);
    
    for (int i = 1; i <= no; i++) {
        fprintf(file, WRITE, info[i].id, info[i].name, info[i].price, info[i].stock);
    }
}
