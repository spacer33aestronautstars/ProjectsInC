
#include<stdio.h>
#include<string.h>
#define LastName "YADAV"
#define PI 3.14159625
int main(){
    char FirstName[20]="YOGESH";
    char FullName[50]; 
    strcpy(FullName, FirstName);
    strcat(FullName, " ");
    strcat(FullName, LastName);
    printf("%s\n",FullName);
    //Print the area of a circle
    float radius;
    printf("Enter radius: ");
    scanf("%f",&radius);
    printf("%.2f",PI*radius*radius);
    return 0;
}