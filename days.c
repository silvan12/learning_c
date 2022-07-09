#include <stdio.h>

const char days[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


int main(){

    int current_day;
    
    printf("Enter number of days:\n>");
    scanf("%d", &current_day);

    int rest = current_day % 7;
    
    printf("Current day is: %s", days[rest]);

    return 0;
}