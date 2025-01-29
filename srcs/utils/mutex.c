#include "utils.h"

int ft_mutex_init(t_mutex *mutex)
{
    int status;

    status = pthread_mutex_init(mutex, NULL);
    error_thread(status);
    return (status);
}

int ft_mutex_unlock(t_mutex *mutex)
{
    int status;

    status = pthread_mutex_unlock(mutex);
    error_thread(status);
    return (status);
}

int ft_mutex_lock(t_mutex *mutex)
{
    int status;

    status = pthread_mutex_lock(mutex);
    error_thread(status);
    return (status);
}
// int Value;
// t_mutex Mutex;
// void *print_code(void *data)
// {
//     char *stock = (char *)data;

//     ft_mutex_lock(&Mutex);
//     Value++;
//     printf("%s is %d.\n", stock, Value);
//     sleep(1);
//     ft_mutex_unlock(&Mutex);
//     return (NULL);
// }
// int main(int argc, char **argv)
// {
//     pthread_t thread[1000];
//     int i;
//     Value = 0;
//     if (argc < 2)
//     {
//         printf("Error: invalid argument\n");
//         return EXIT_FAILURE;
//     }
//     if (ft_mutex_init(&Mutex) != 0)
//     {
//         perror("pthread_mutex_init");
//         return EXIT_FAILURE;
//     }
//     while (1)
//     {
//         for (i = 0; i < argc - 1; i++)
//         {
//             if (ft_thread_create(&thread[i], print_code, argv[i + 1]) != 0)
//             {
//                 perror("pthread_create");
//                 pthread_mutex_destroy(&Mutex);
//                 return EXIT_FAILURE;
//             }
//         }
//         for (i = 0; i < argc - 1; i++)
//         {
//             if (pthread_join(thread[i], NULL) != 0)
//             {
//                 perror("pthread_join");
//                 pthread_mutex_destroy(&Mutex);
//                 return EXIT_FAILURE;
//             }
//         }
//         sleep(1);
//     }
//     pthread_mutex_destroy(&Mutex);
//     return 0;
// }