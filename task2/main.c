#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *path;

typedef struct {
    int id;
    char *name;
    char *phone;
    bool valid;
} note;
int size, n = 0, inval = 0;
note *a;
bool rd = false;
void ensure_space() {
    if (size == n) {
        note *na = (note *) malloc(sizeof(note *) * (n - inval) * 2);
        int pos = 0;
        int i;
        for (i = 0; i < size; i++) {
            if (a[i].valid)na[pos++] = a[i];
        }
        n = pos - 1;
        size = (n - inval) * 2;
        inval = 0;
        free(a);
        a = na;

    }
}

void ensure_space_str(char *s) {
    int n = strlen(s);
    if (n == 0)n++;
    s = (char *) realloc(s, sizeof(char *) * n * 2);
}

bool find_phone(char *s1, char *t1) {
    char *s = (char *) malloc(sizeof(char *) * strlen(s1));
    int pos = 0;
    int i;
    for (i = 0; i < strlen(s1); i++)
        if (s1[i] >= '0' && s1[i] <= '9')s[pos++] = s[i];
    char *t = (char *) malloc(sizeof(char *) * strlen(t1));
    pos = 0;
    for (i = 0; i < strlen(t1); i++)
        if (t1[i] >= '0' && t1[i] <= '9')t[pos++] = t[i];

    return strcmp(s, t) == 0;
}

bool find(char *s1, char *t) {
    char *s = (char *) malloc(sizeof(char *) * strlen(s1));
    strcpy(s, s1);
    int i;
    for (i = 0; i < strlen(s); i++)
        if (s[i] >= 'a') s[i] -= ('a' - 'A');
    int j;
    for (j = 0; j < strlen(t); j++)
        if (t[j] >= 'a')t[j] -= ('a' - 'A');
    return !(strstr(s, t) == NULL);
}

void rewrite() {
    if(rd)return;
    FILE *f;
    f = fopen(path, "w+");
    int i;
    for (i = 0; i < n; i++)
        if (a[i].valid)
            fprintf(f, "%d %s %s \n", a[i].id, a[i].name, a[i].phone);
    fclose(f);
}

int cur_id = 0;

void add(char *name, char *phone, int id) {
    ensure_space();
    note t;
    t.name = name;
    t.id = id++;
    t.phone = phone;
    t.valid = true;
    a[n++] = t;
    rewrite();
}

void del(int id) {
    int i;
    for (i = 0; i < n; i++)
        if (a[i].id == id) {
            a[i].valid = false;
            rewrite();
            return;
        }
}

char *read(FILE *f) {
    bool file = f == NULL ? false : true;
    int pos = 0;
    char x;
    char *s = (char *) malloc(sizeof(char *) * 32);
    if (file)fscanf(f, "%c", &x);
    else scanf("%c", &x);
    while (x != '\n' && x != 32) {
        s[pos++] = x;
        if (strlen(s) == pos) ensure_space_str(s);
        if (file)fscanf(f, "%c", &x);
        else scanf("%c", &x);
    }
    s[pos++] = '\0';
    return s;
}

void init() {
    rd = true;
    FILE *f;
    f = fopen(path, "r");
    int id;
    char *name = NULL, *phone = NULL;
    //while (fscanf(f, "%d%*c", &id) != EOF) {
     //   name = read(f);
      //  phone = read(f);
      //  add(name, phone, id);
    //    cur_id = id >= cur_id ? id + 1 : cur_id;
    //}
    rd = false;
}

int main(int argc, char **argv) {

    path = argc > 1 ? argv[1] : "base.txt";

    a = (note *) malloc(sizeof(note *) * 16);
    size = 16;
    init();
    int id;
    char cmd[15];
    FILE *nll = NULL;
    while (true) {
        scanf("%s%*c", cmd);
        if (strcmp(cmd, "exit") == 0) {
            rewrite();
            return 0;
        }
        if (strcmp(cmd, "delete") == 0) {
            scanf("%d%*c", &id);
            del(id);
            continue;
        }

        if (strcmp(cmd, "change") == 0) {
            scanf("%d", &id);
            scanf("%s%*c", cmd);
            char *s = NULL;
            s = read(nll);
            int p = 0;
            int i;
            for (i = 0; i < n; i++)
                if (a[i].valid && a[i].id == id) {
                    p = i;
                    break;
                }
            if (cmd[0] == 'n') a[p].phone = s; else a[p].name = s;
            rewrite();
            continue;
        }

        if (strcmp(cmd, "create") == 0) {
            char *phone = NULL;
            char *s = NULL;
            s = read(nll);
            phone = read(nll);
            add(s, phone, cur_id++);
            continue;
        }

        if (strcmp(cmd, "find") == 0) {
            char *s = NULL;
            s = read(nll);
            int i;
            for (i = 0; i < n; i++) {
                if (a[i].valid && (find(a[i].name, s) || find(a[i].phone, s))) {
                    printf("%d %s %s\n", a[i].id, a[i].name, a[i].phone);
                }
            }
            continue;
        }
        printf("Unknown command\n");
    }
}
