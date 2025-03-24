#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

int main(){
    pid_t process_id = fork();
    if (process_id == -1){
        printf("fork id = %d \n", process_id);
    }
    else if(process_id == 0){
        printf("child process\n");
        execl("/root/Unix_OS/homeworks/homework1/triangle", "triangle", NULL);
    } 
    else {
        wait (NULL);
        printf("parent process\n");
        
        float width;
        float length;
        float rec_area;

        wait (NULL);

        do{
            printf("Enter the width of the rectangle: ");
            scanf("%f", &width);
    
        } while (width <= 0);

        do{
            printf("Enter the length of the rectangle: ");
            scanf("%f", &length);
        } while (length <= 0);

        rec_area = width * length;
        printf("The area of the rectangle is %.2f\n", rec_area);
    }
}