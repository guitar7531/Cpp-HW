#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char* path;

typedef struct {
    int id;
    char* name;
    char* phone;
    bool valid;
}node;
int size, cur_pos = 0, cnt_inval = 0;
node* a;

void ensure_space(){
    if (size == cur_pos){
        node* na = (node*)malloc(sizeof(node*)* cnt_inval * 2);
        int pos = 0;
        for (int i = 0; i < size; i++){
            if (a[i].valid)na[pos++] = a[i];
        }
        cur_pos = size - cnt_inval;
        size = cnt_inval * 2;
        cnt_inval = 0;
    }
}

void ensure_space_str(char* s){
    int n = strlen(s);
    s = (char*)realloc(s, sizeof(char*)* n * 2);
}

bool find(char* s1, char* t){
    char* s = (char*)malloc(sizeof(char*)* strlen(s1));
    strcpy(s, s1);
    for (int i = 0; i < strlen(s); i++)
    if (s[i] >= 'a') s[i] -= ('a' - 'A');
    for (int j = 0; j < strlen(t); j++)
    if (t[j] >= 'a')t[j] -= ('a' - 'A');
    return !(strstr(s, t) == NULL);
}

void rewrite(){
    FILE* f;

    f = fopen(path, "w+");
    for (int i = 0; i < cur_pos; i++)
    if (a[i].valid)
        fprintf(f, "id %d  name %s  phone %s \n", a[i].id, a[i].name, a[i].phone);
    fclose(f);
}

int cur_id = 0;
void add(char* name, char* phone){
    ensure_space();
    node t;
    t.name = name;
    t.id = cur_id++;
    t.phone = phone;
    t.valid = true;
    a[cur_pos++] = t;
    rewrite();
}

void del(int id){
    for (int i = 0; i < cur_pos; i++)
    if (a[i].id == id){
        a[i].valid = false;
        rewrite();
        return;
    }
}

void read(char* s){
    int pos = 0;
    char x;
    scanf("%c", &x);
    while (x != '\n' && x != 32){
        if (x != '(' && x != ')' && x != '-' && x != '+')s[pos++] = x;
        if (strlen(s) == pos) ensure_space_str(s);
        scanf("%c", &x);
    }
    s[pos++] = '\0';
}

int main(int argc, char* argv[]){

    path = "base.txt";
    freopen("input.txt", "r", stdin);
    a = (node*)malloc(sizeof(node*)* 16);
    size = 16;
    int id;
    char cmd[15];

    while (true){
        scanf("%s%*c", &cmd);
        if (cmd[0] == 'e'){
            rewrite();
            return 0;                            //exit
        }
        if (cmd[0] == 'd'){                                    // delete		
            scanf("%d%*c", &id);
            del(id);
            continue;
        }

        if (cmd[1] == 'h'){                 // change
            scanf("%d", &id);
            scanf("%s%*c", cmd);
            char* s = (char*)malloc(sizeof(char*)* 2);
            read(s);
            int p;
            for (int i = 0; i < cur_pos; i++)
            if (a[i].valid && a[i].id == id){
                p = i;
                break;
            }
            if (cmd[0] == 'n') a[p].phone = s; else a[p].name = s;
            rewrite();
            continue;
        }

        if (cmd[1] == 'r'){                                  // create 
            char* phone = (char*)malloc(sizeof(char*)* 32);
            char* s = (char*)malloc(sizeof(char*)* 2);
            read(s);
            read(phone);
            add(s, phone);
            continue;
        }

        if (cmd[0] == 'f') {                             // find
            char* s = (char*)malloc(sizeof(char*)* 2);
            read(s);
            for (int i = 0; i < cur_pos; i++){
                if (a[i].valid && (find(a[i].name, s) || find(a[i].phone, s))){
                    printf("%d %s %s\n", a[i].id, a[i].name, a[i].phone);
                }
            }
        }
    }
}
