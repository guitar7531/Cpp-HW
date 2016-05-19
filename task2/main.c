#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *path;

typedef struct {
    int id;
    char *name;
    char *phone;
    bool valid;
} note;
int size, n = 0, inval = 0;
note *a;
FILE *nll = NULL;
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
    int n = strlen(s), i;
    if (n == 0)n++;
    char* t = (char *) malloc(sizeof(char*) * n * 2);
    for(i=0;i < n;i++)
        t[i] = s[i];
    s = t;
    free(t);
}

void rewrite() {
    if (rd)return;
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
    f = fopen(path, "at+");
    int id;
    char *name = NULL, *phone = NULL;
    while (fscanf(f, "%d", &id) != EOF) {
        fscanf(f, "%*c");
        name = read(f);
        phone = read(f);
        add(name, phone, id);
        cur_id = id >= cur_id ? id + 1 : cur_id;
    }
    fclose(f);
    rd = false;
}

char *name_conv(char *s) {
    char *t = (char *) malloc(sizeof(char *) * strlen(s));
    int i, pos = 0;
    for (i = 0; i < strlen(s); i++) {
        t[pos++] = s[i];
        if (t[i] >= 'a') t[i] -= ('a' - 'A');
    }
    t[pos++] = '\0';
    return t;
}

char *phone_conv(char *s) {
    char *t = (char *) malloc(sizeof(char *) * strlen(s));
    int i, pos = 0;
    for (i = 0; i < strlen(s); i++)
        if (isdigit(s[i])) t[pos++] = s[i];
    t[pos++] = '\0';
    return t;
}

void find() {
    char *s = NULL;
    s = read(nll);
    bool name = isalpha(s[0]);
    if (name)s = name_conv(s);
    else s = phone_conv(s);
    int i;
    for (i = 0; i < n; i++)
        if ((name && strstr(name_conv(a[i].name), s) != NULL) ||
            (!name && strcmp(phone_conv(a[i].phone), s) == 0))
            printf("%d %s %s\n", a[i].id, a[i].name, a[i].phone);
    fflush(stdout);
}

int main(int argc, char **argv) {

    path = argc > 1 ? argv[1] : "base.txt";

    a = (note *) malloc(sizeof(note *) * 16);
    size = 16;
    init();
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
            find();
            continue;
        }
        printf("Unknown command\n");
    }
}
