#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utils.h"


void build_tree(pid_t root, u_int32_t count_indent)
{
    FILE *fp_cld = NULL;
    int8_t path[MAX_LEN] = {0};
    int8_t pid[MIN_LEN] = {0};

    snprintf(path, MAX_LEN, "/proc/%d/task/%d/children", root, root);
    if ((fp_cld = fopen(path, "r")) == NULL) {
        perror("Error opening children file!");
        return;
    }

    presence_pid[root] = 1;

    for (int i = 0; i < count_indent; i++)
        printf(INDENT);

    print_line(root);

    count_indent++;

    while (fscanf(fp_cld, "%s", pid) != EOF) {
        build_tree(atoi(pid), count_indent);
    }

    fclose(fp_cld);
}

void print_line(pid_t pid)
{
    FILE *fp_stat = NULL;
    FILE *fp_cmdline = NULL;
    int8_t *temp = NULL;
    int8_t path[MAX_LEN] = {0};
    int8_t cmdline_buf[MAX_LEN] = {0};
    int8_t stat_buf[MAX_LEN] = {0};
    int8_t name[MIN_LEN] = {0};
    int8_t state[MIN_LEN] = {0};

    snprintf(path, MAX_LEN, "/proc/%d/stat", pid);
    if ((fp_stat = fopen(path, "r")) == NULL) {
        perror("Error opening stat file!");
        return;
    }

    snprintf(path, MAX_LEN, "/proc/%d/cmdline", pid);
    if ((fp_cmdline = fopen(path, "r")) == NULL) {
        perror("Error opening cmdline file!");
        return;
    }

    while(!feof(fp_stat)) {
        if (fgets(stat_buf, MAX_LEN, fp_stat)) {
            temp = strrchr(stat_buf, '(');
            temp++;

            for (int i = 0; *temp != ')'; i++)
                name[i] = *temp++;

            temp = strrchr(stat_buf, ')');
            temp++;
            sscanf(temp, "%s", state);
        }
    }

    while(!feof(fp_cmdline)) {
        if (fgets(cmdline_buf, MAX_LEN, fp_cmdline)) {
            printf("%5d %s * %s\n", pid, state, cmdline_buf);
        }
        else {
            printf("%5d %s * %s\n", pid, state, name);
        }
    }

    fclose(fp_stat);
    fclose(fp_cmdline);
}
