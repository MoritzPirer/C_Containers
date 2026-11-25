
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

typedef struct {
    int total;
    int passed;
    int failed;
} TestSummary;

static int run_test(const char* path)
{
    pid_t pid = fork();

    if (pid < 0) {
        printf("Error while spawning process! Tests in '%s' not ran!", path);
        return 1;
    }

    if (pid == 0) {
        execl(path, path, (char*)NULL);
        //should not return to here
        perror(path);
        _exit(127);
    }

    int status;
    pid_t result;

    do {
        result = waitpid(pid, &status, 0);
    } while (result < 0 && errno == EINTR);

    if (result < 0) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("[PASS] %s\n", path);
        return 0;
    }

    if (WIFEXITED(status)) {
        printf("[FAIL] %s (exit code: %d)\n",
            path, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("[FAIL] %s (signal: %d)\n",
            path, WTERMSIG(status));
    }

    return 1;
}

static void discover_tests(const char* directory, TestSummary* summary)
{
    DIR* dir = opendir(directory);

    if (dir == NULL) {
        perror(directory);
        summary->failed++;
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[PATH_MAX];

        int length = snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

        if (length < 0 || (size_t)length >= sizeof(path)) {
            fprintf(stderr, "Path too long: %s/%s\n", directory, entry->d_name);
            summary->failed++;
            continue;
        }

        struct stat info;

        if (lstat(path, &info) != 0) {
            perror(path);
            summary->failed++;
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            discover_tests(path, summary);
            continue;
        }

        if (!S_ISREG(info.st_mode)) {
            continue;
        }

        if (strncmp(entry->d_name, "test_", 5) != 0) {
            continue;
        }

        if (access(path, X_OK) != 0) {
            continue;
        }

        summary->total++;

        if (run_test(path) == 0) {
            summary->passed++;
        }
        else {
            summary->failed++;
        }
    }

    closedir(dir);
}

int main(void)
{
    TestSummary summary = {0};

    discover_tests(".", &summary);

    printf("\n========== TEST SUMMARY ==========\n");
    printf("Total:  %d\n", summary.total);
    printf("Passed: %d\n", summary.passed);
    printf("Failed: %d\n", summary.failed);
    printf("==================================\n");

    return summary.failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
