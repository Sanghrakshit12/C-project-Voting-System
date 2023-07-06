#include"adminpanel.h"
#include"studentpanel.h"
#include"patt.h"

int main(){
    while(1){
        open();
      
        printf("\t\t\t\t 1- Admin Panel  \n\n\t\t\t\t 2- Student panel \n\n\t\t\t\t 3- Exit \n\n\t\t\t\t Please Press The Required Key :");
		char choice;
        scanf(" %c",&choice);

        switch(choice){
            case '1':
              adminPanel();
                break;
            case '2':
              studentPanel();
                break;
            case '3':
                return 0;
            default:
                printf("\nInvalid option");
                getch();
        }
    }
    return 0;
}