#include "utils.h"

int main(int argc, char *argv[])
{
    FILE *fp_pid_max = NULL;
    DIR *dir = NULL;
    pid_t pid = 0;
    dirent_t *cur_dir = NULL;
    u_int32_t pid_max = 0;
    int8_t pid_max_str[MIN_LEN] = {0};

    if (argc != 1) {
        perror("Error count of arguments!");
        return -1;
    }

    if ((fp_pid_max = fopen("/proc/sys/kernel/pid_max", "r")) == NULL) {
        perror("Error opening pid_max file!");
        return -1;
    }

    if (fscanf(fp_pid_max, "%s", pid_max_str) != -1) {
        pid_max = atoi(pid_max_str);
    }
    else {
        perror("Error reading pid_max!");
        return -1;
    }

    presence_pid = (int8_t *)calloc(pid_max, sizeof(int8_t));
    if (presence_pid == NULL) {
        perror("Error calloc!");
        return -1;
    }

    dir = opendir("/proc");

    while (cur_dir = readdir(dir)) {
        if (*cur_dir->d_name < '0' || *cur_dir->d_name > '9')
            continue;

        pid = atoi(cur_dir->d_name);
        if (!presence_pid[pid])
            build_tree(pid, 0);
    }

    free(presence_pid);
    fclose(fp_pid_max);
    closedir(dir);

    return 0;
}
