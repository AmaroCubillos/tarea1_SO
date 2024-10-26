#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int primo(long long num) {
    if (num <= 1) return 0;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    char *primos_salida = "resultados_primos.txt";    
    long long M = atoll(argv[1]);
    long long num_procesos = atoi(argv[2]);
    long long rango = M / num_procesos;
    int pipes[num_procesos][2];

    for (int i = 0; i < num_procesos; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("error al inicializar el pipe");
            exit(1);
        }
    }    
    for (int i = 0; i < num_procesos; i++) {

        int pid = fork();

        if (pid < 0) {
            perror("error al inicializar el fork");
            exit(1);
        }

        if (pid == 0) {
            close(pipes[i][0]);

            long long inicio = i * rango + 1;
            long long fin = (i + 1) * rango ;

            for (long long num = inicio; num <= fin; num++) {
                if (primo(num) == 1) {
                    write(pipes[i][1], &num, sizeof(long long));
                }
            }

            close(pipes[i][1]);
            exit(0);
        } else {
            close(pipes[i][1]);
        }
    }

    FILE *salida = fopen(primos_salida, "w");

    for (int i = 0; i < num_procesos; i++) {
        long long primo;
        while (read(pipes[i][0], &primo, sizeof(long long)) > 0) {
            fprintf(salida, "%lld\n", primo);
        }
        close(pipes[i][0]);
        wait(NULL);
    }

    fclose(salida);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = ((end.tv_sec - start.tv_sec) * 1e3) + ((end.tv_nsec - start.tv_nsec) / 1e6);
    printf("el programa demoró %.3f ms\n", elapsed);
    
    return 0;
}