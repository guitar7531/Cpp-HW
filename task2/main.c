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

void ensure_space() {
    if (size == n) {
        note *na = (note *) malloc(sizeof(note *) * (n - inval) * 2);
        int pos = 0;
        int i;
        for (i = 0; i < size; i++) {
            if (a[i].valid)na[pos++] = a[i];
        }
        n = size - n;
        size = (n - inval) * 2;
        inval = 0;
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
    FILE *f;

    f = fopen(path, "w+");
    int i;
    for (i = 0; i < n; i++)
        if (a[i].valid)
            fprintf(f, "id: %d | name: %s | phone: %s \n", a[i].id, a[i].name, a[i].phone);
    fclose(f);
}

int cur_id = 0;

void add(char *name, char *phone) {
    ensure_space();
    note t;
    t.name = name;
    t.id = cur_id++;
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

void read(char *s) {
    int pos = 0;
    char x;
    if (strlen(s) == pos) ensure_space_str(s);
    scanf("%c", &x);
    while (x != '\n' && x != 32) {
        s[pos++] = x;
        if (strlen(s) == pos) ensure_space_str(s);
        scanf("%c", &x);
    }
    s[pos++] = '\0';
}

int main(int argc, char **argv) {

    path = argc > 1 ? argv[0] : "base.txt";
    //  freopen("input.txt", "r", stdin);
    a = (note *) malloc(sizeof(note *) * 16);
    size = 16;
    int id;
    char cmd[15];

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
            char *s = (char *) malloc(sizeof(char *) * 2);
            read(s);
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
            char *phone = (char *) malloc(sizeof(char *) * 32);
            char *s = (char *) malloc(sizeof(char *) * 32);
            read(s);
            read(phone);
            add(s, phone);
            continue;
        }

        if (strcmp(cmd, "find") == 0) {
            char *s = (char *) malloc(sizeof(char *) * 32);
            read(s);
            int i;
            for (i = 0; i < n; i++) {
                if (a[i].valid && (find(a[i].name, s) || find(a[i].phone, s))) {
                    printf("%d %s %s\n", a[i].id, a[i].name, a[i].phone);
                }
            }
            continue;
        }
        printf("Unknown command");
    }
}
