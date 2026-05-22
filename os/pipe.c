#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int fd[2];
    float a, b, c;
    float four_ac, b2, disicriminant, result;

    printf("a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    // pipe and fork
    pipe(fd);
    pid = fork();

    if (pid == 0) {
        close(fd[0]);
        four_ac = 4 * a * c;
        write(fd[1], &four_ac, sizeof(four_ac));
        close(fd[1]);
    } else {
        close(fd[1]);
        b2 = b * b;
        read(fd[0], &four_ac, sizeof(four_ac));
        close(fd[0]);
        disicriminant = b2 - four_ac;

        if (disicriminant < 0) {
            printf("Negative Discriminant");
        } else {
            result = b + sqrt(disicriminant);
            result /= (2*a);
            printf("%f", result);
        }

    }

    return 0;
}