// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <sys/syscall.h>
// #include <assert.h>

// // 定义测试开始和结束的宏
// #define TEST_START(func) printf("========== START %s ==========\n", func);
// #define TEST_END(func) printf("========== END %s ==========\n", func);

// // 定义获取线程 ID 的宏
// #define gettid() syscall(SYS_gettid)

// // 线程函数
// void* thread_function(void* arg) {
//     pid_t tid = gettid();
//     assert(tid >= 0);
//     printf("This is child thread. tid = %d\n", (int)tid);
//     return NULL;
// }

// // 测试 gettid 的函数
// void test_gettid(void) {
//     TEST_START(__func__);
//     pthread_t thread_id;
//     int ret;

//     // 创建线程
//     ret = pthread_create(&thread_id, NULL, thread_function, NULL);
//     assert(ret == 0);

//     // 等待线程结束
//     ret = pthread_join(thread_id, NULL);
//     assert(ret == 0);

//     // 获取主线程的线程 ID
//     pid_t main_tid = gettid();
//     assert(main_tid >= 0);
//     printf("This is main thread. tid = %d\n", (int)main_tid);

//     TEST_END(__func__);
// }

// int main(void) {
//     test_gettid();
//     return 0;
// }    
// // // // // #include <stdio.h>
// // // // // #include <stdlib.h>
// // // // // #include <unistd.h>
// // // // // #include <sys/syscall.h>
// // // // // #include <assert.h>
// // // // // #include <sys/types.h>
// // // // // #include <sys/wait.h>

// // // // // // 定义获取线程 ID 的宏
// // // // // #define gettid() syscall(SYS_gettid)

// // // // // // 定义测试开始和结束的宏
// // // // // #define TEST_START(func) printf("========== START %s ==========\n", func);
// // // // // #define TEST_END(func) printf("========== END %s ==========\n", func);

// // // // // // 测试 gettid 的函数
// // // // // void test_gettid(void) {
// // // // //     TEST_START(__func__);

// // // // //     pid_t pid = fork();
// // // // //     assert(pid >= 0);

// // // // //     if (pid == 0) {
// // // // //         // 子进程
// // // // //         pid_t tid = gettid();
// // // // //         assert(tid >= 0);
// // // // //         printf("This is child process (also a thread context). tid = %d\n", (int)tid);
// // // // //         exit(0);
// // // // //     } else {
// // // // //         // 父进程
// // // // //         int status;
// // // // //         waitpid(pid, &status, 0);

// // // // //         pid_t main_tid = gettid();
// // // // //         assert(main_tid >= 0);
// // // // //         printf("This is main process (also a thread context). tid = %d\n", (int)main_tid);
// // // // //     }

// // // // //     TEST_END(__func__);
// // // // // }

// // // // // int main(void) {
// // // // //     test_gettid();
// // // // //     return 0;
// // // // // } 

// #define _GNU_SOURCE
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/syscall.h>
// #include <sys/types.h>
// #include <sched.h>
// size_t stack[1024] = {0};
// #define STACK_SIZE (1024) // 1KB stack size

// // 线程函数
// int thread_function(void* arg) {
//     // 获取线程ID
//     pid_t tid = syscall(SYS_gettid);
//     printf("Thread ID in child thread: %d\n", tid);

//     // 线程退出
//     return 0;
// }

// int main() {
//     // 获取主线程ID
//     pid_t main_tid = syscall(SYS_gettid);
//     printf("Thread ID in main thread: %d\n", main_tid);

//     // 分配栈空间
//     void* stack = malloc(STACK_SIZE);
//     if (stack == NULL) {
//         perror("Failed to allocate stack");
//         return 1;
//     }

//     // 创建线程
//     int clone_flags = CLONE_THREAD;
//     int* child_stack = stack + STACK_SIZE;
//     int child_tid = clone(thread_function,
//         child_stack,
//         CLONE_VM | CLONE_FS  | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD,
//         (void *)NULL);

//     if (child_tid == -1) {
//         perror("Failed to create thread using clone");
//         // free(stack);
//         return 1;
//     }

//     // 等待子线程结束
//     int status;
//     waitpid(child_tid, &status, 0);

//     // 释放栈空间
//     free(stack);

//     return 0;
// }
// // // #define _GNU_SOURCE
// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <unistd.h>
// // // #include <sys/syscall.h>
// // // #include <sys/types.h>
// // // #include <sched.h>
// // // #include <sys/mman.h>

// // // #define STACK_SIZE (1024 * 1024) // 1MB stack size

// // // void* thread_function(void* arg) {
// // //     pid_t tid = syscall(SYS_gettid);
// // //     printf("Thread ID in child thread: %d\n", tid);
// // //     return NULL;
// // // }

// // // int main() {
// // //     pid_t main_tid = syscall(SYS_gettid);
// // //     printf("Thread ID in main thread: %d\n", main_tid);

// // //     // 使用 mmap 分配栈空间
// // //     void *stack;

// // //     stack = malloc(STACK_SIZE);

// // //     int child_tid = clone(thread_function, stack+STACK_SIZE,
// // //     CLONE_THREAD|CLONE_SIGHAND|CLONE_VM, 0);

// // //     if (child_tid == -1) {
// // //     printf("Error: thread creation fled\n");
// // //     return 1;
// // //     }
// // //     // void* stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
// // //     //                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// // //     // if (stack == MAP_FAILED) {
// // //     //     perror("Failed to allocate stack using mmap");
// // //     //     return 1;
// // //     // }

// // //     // // 确保栈空间的顶部地址是 16 字节对齐的
// // //     // void* child_stack = (void*)(((unsigned long)stack + STACK_SIZE) & (~0xF));

// // //     // int clone_flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD;
// // //     // int child_tid = clone(thread_function, child_stack, clone_flags, NULL);

// // //     // if (child_tid == -1) {
// // //     //     perror("Failed to create thread using clone");
// // //     //     munmap(stack, STACK_SIZE);
// // //     //     return 1;
// // //     // }

// // //     int status;
// // //     waitpid(child_tid, &status, 0);

// // //     munmap(stack, STACK_SIZE);
// // //     return 0;
// // // }
// // #define _GNU_SOURCE
// // #include <sched.h>
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>

// // #define STACK_SIZE 1024 * 1024  // 1MB stack size

// // int child_func(void *arg) {
// //     printf("Child process: PID = %d\n", getpid());
// //     return 0;
// // }

// // int main() {
// //     char *stack = malloc(STACK_SIZE);
// //     if (!stack) {
// //         perror("malloc");
// //         exit(EXIT_FAILURE);
// //     }

// //     pid_t pid = clone(child_func, stack + STACK_SIZE, CLONE_SIGHAND, NULL);
// //     if (pid == -1) {
// //         perror("clone");
// //         exit(EXIT_FAILURE);
// //     }

// //     printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
// //     wait(NULL);  // Wait for child process to finish
// //     free(stack);
// //     return 0;
// // }
// // #define _GNU_SOURCE
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <sys/syscall.h>
// // #include <sys/types.h>
// // #include <sched.h>
// // #include <sys/mman.h>

// // #define STACK_SIZE (1024 * 1024) // 1MB stack size

// // void* thread_function(void* arg) {
// //     pid_t tid = syscall(SYS_gettid);
// //     printf("Thread ID in child thread: %d\n", tid);
// //     return NULL;
// // }

// // int main() {
// //     pid_t main_tid = syscall(SYS_gettid);
// //     printf("Thread ID in main thread: %d\n", main_tid);

// //     // 使用 mmap 分配栈空间
// //     void* stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
// //                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// //     if (stack == MAP_FAILED) {
// //         perror("Failed to allocate stack using mmap");
// //         return 1;
// //     }

// //     // 确保栈空间的顶部地址是 16 字节对齐的
// //     void* child_stack = (void*)(((unsigned long)stack + STACK_SIZE) & (~0xF));

// //     int clone_flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD;
// //     int child_tid = clone(thread_function, child_stack, clone_flags, NULL);

// //     if (child_tid == -1) {
// //         perror("Failed to create thread using clone");
// //         munmap(stack, STACK_SIZE);
// //         return 1;
// //     }

// //     int status;
// //     waitpid(child_tid, &status, 0);

// //     munmap(stack, STACK_SIZE);
// //     return 0;
// // }
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/mman.h>

#define STACK_SIZE (1024 * 1024) // 1MB stack size

void* thread_function(void* arg) {
    pid_t tid = syscall(SYS_gettid);
    printf("Thread ID in child thread: %d\n", tid);
    return NULL;
}

int main() {
    pid_t main_tid = syscall(SYS_gettid);
    printf("Thread ID in main thread: %d\n", main_tid);

    // 使用 mmap 分配栈空间
    void* stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (stack == MAP_FAILED) {
        perror("Failed to allocate stack using mmap");
        return 1;
    }

    // 确保栈空间的顶部地址是 16 字节对齐的
    void* child_stack = (void*)(((unsigned long)stack + STACK_SIZE) & (~0xF));

    int clone_flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD;
    int child_tid = clone(thread_function, child_stack, clone_flags, NULL);

    if (child_tid == -1) {
        perror("Failed to create thread using clone");
        munmap(stack, STACK_SIZE);
        return 1;
    }

    int status;
    waitpid(child_tid, &status, 0);

    munmap(stack, STACK_SIZE);
    return 0;
}