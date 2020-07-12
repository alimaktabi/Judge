#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define MAXSIZE 100

float Judge(char name[]);

/*
*This function is for getting input and output files from txt addresses if needed
* variable counter and count are counters for getting inputs and putting testcases
* variable command is for executing commands in cmd
* variable name is the name of the project and x counts the txt files as it goes
*/

void Text(char name[]) {
    int count, counter = 1;
    char location[MAXSIZE], command[MAXSIZE], x;
    printf("\nGive me testcases count: ");
    scanf("%i", &count); getchar();
    for (count; count >= counter; counter++) {
        x = counter + '0';
        printf("Testcase %i Input location: ", counter);
        gets(location);
        strcpy(command, "copy "); strcat(command, location); strcat(command, " "); strcat(command, name);
        strcat(command, "\\in\\"); strncat(command, &x, 1);strcat(command, ".txt");
        system(command);
        memset(command, 0, sizeof command);
        printf("Testcase %i Output location: ", counter);
        gets(location);
        strcpy(command, "copy "); strcat(command, location); strcat(command, " "); strcat(command, name);
        strcat(command, "\\out\\"); strncat(command, &x, 1);strcat(command, ".txt");
        system(command);
    }
    printf("Judge created successfully\n3.File Location(C:\\filename.c): ");
    gets(location);
    strcpy(command, "gcc -v "); strcat(command, location); strcat(command, " -o "); strcat(command, name); strcat(command, "\\t.exe");
    if (system(command) == 1) {
        printf("seems there is an error, press enter to continue: ");
        getchar();
        return;
    }
    system("cls");
    printf("Compiled successfully\nDoing the tests right now");
    printf("\n\nYour result is : %f\n\npress enter to continue: ", Judge(name));
    getchar();
    return;
}
/*int compareFile(FILE * fPtr1, FILE * fPtr2)
{
    char ch1, ch2;
    int num1, num2;
    do
    {
        fscanf(fPtr1, "%d", &num1);
        fscanf(fPtr2, "%d", &num2);


        if (num1 != num2)
            printf("%i\n", num1);
            printf("%i\n", num2);
            return -1;


    } while (ch1 != EOF && ch2 != EOF);


    return 0;
//    else
//        return -1;
} */
/*
*this function is for comparing 2 files so make sure he gets the score or not
*ch1 and ch2 gets every characters from files and compare each other, if they were not equal so the function returns error
* if nothing wrong happens the function complete successfully and returns the good result of a good student
*/
int compareFiles(FILE *file1, FILE *file2){
   char ch1 = getc(file1);
   char ch2 = getc(file2);
   int error = 0, pos = 0, line = 1;
   while (ch1 != EOF && ch2 != EOF){
      pos++;
      if (ch1 == '\n' && ch2 == '\n'){
         line++;
         pos = 0;
      }
      if (ch1 != ch2){
         error++;
         return -1;
      }
      ch1 = getc(file1);
      ch2 = getc(file2);
   }
   return 0;
}
/*
int ls(char x[]) {
struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }

    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);

    closedir(dr);
    return 0;
}
*/
/*
*function for making directories
* variable name is for name of the dir
* if no error happens function returns 0
*/
int cd(char name[]) {
    char command[50] = "mkdir ";
    strcat(command, name);
    if(system(command) != 0) {
        printf("This directory or judge already exist pls try another name\npress enter to continue: ");
        getchar();
        return -1;
    }
    return 0;
}

/*
* this function gets testfile outputs and put them into comparefiles
* variable @name is the name of the judge
* variable @command is for executing cmd commands
* function @returns the score at last
*/
float Judge(char name[]) {
    int score = 0;
    int counter = 1, count=0;
    char command[50] = "mkdir ";
    strcat(command, name); strcat(command, "\\testcase");
    if(system(command) == 1) {
        strcpy(command, "RMDIR /Q/S "); strcat(command, name); strcat(command, "\\testcase");
        system(command);
        return Judge(name);
    }
    char x, exe[MAXSIZE];
    while (1) {
        x = counter + '0';
        strcpy(exe, name);
        strcat(exe, "\\t.exe < ");
        strcat(exe, name); strcat(exe, "\\in\\");

        strncat(exe, &x, 1);
        strcat(exe, ".txt >");
        strcat(exe, name);
        strcat(exe, "\\testcase\\");

        strncat(exe, &x, 1);
        strcat(exe, ".txt");

        if (system(exe) != 0) {
            system("cls");
            break;
        }
        counter++;
    }
    int match;
    FILE *log;
    log = fopen("D:\\temp\\log.txt", "w");
    printf("Done, Calculating the result...\n");
    FILE *test, *ans;
    for(count=1; count < counter; count++) {
        x =count + '0';
        strcpy(command, name); strcat(command, "\\testcase\\"); strncat(command, &x, 1);
        strcat(command, ".txt");
        test = fopen(command, "r");
        strcpy(command, name);
        strcat(command, "\\out\\"); strncat(command, &x, 1); strcat(command, ".txt");
        ans = fopen(command, "r");
        if(compareFiles(ans, test) == 0) {
            fprintf(log, "pass\n");
            score++;
        }
        else {
            fprintf(log, "fail\n");
        }
            fclose(ans); fclose(test);
        }
       fclose (log);
    return score / (float) (counter-1) * 100;
}

/*
* this function is the tui of the program
* it runs when every single job is done in the main functions so it does not stuck in return pointers
* variable @name is the project name and command is the execution of cmd
*/
void ui() {
    int cmd;
    char name[50], send[20], command[40];
    char enter;
    printf("Judge System\n\n********************\n\nAli Reza Rostami-Sina Amini-Mohammad Zare-Ali Maktabi\n\n********************\n1: Help\n2: New Judge\n3: Existing Judge\n\n\n\nType Your command: ");
    //scanf("%i", &cmd);
    cmd = getchar();
    system("cls");
    switch(cmd) {
    case '1':
        printf("\n\nThis Program is for testing student's scripts and making sure they shot the perfect score!\nyou just need to create new judge system and give him the correct input and output so the program knows what is the correct answer\n\n\n\n\n");
        printf("press Enter to continue: \n");
        getchar(); getchar();
        return;
    case '2':
        printf("1.Judge name: ");
        scanf("%s", name);
        getchar();
        if (cd(name) == -1) {
            return;
        }
        strcpy(command, name); strcat(command, "\\in"); cd(command);
        strcpy(command, name); strcat(command, "\\out"); cd(command);
        printf("To build a Judge you must give me test cases and answers\n\nchoose how you give me testcases: \n1.Giving Inputs on here      2.Giving Inputs location(txt)\n");
        scanf("%c", &enter);
        if (enter == '2') {
            Text(name);
            return;
        }
        printf("Enter number of testcases here: ");
        int count, c1=1;
        char text;
        scanf("%i", &count);
        getchar();
        for (c1; c1 <= count; c1++) {
            text = c1 + '0';
            printf("Entry of testcase %i: ", c1);
            scanf("%s", send); getchar();
            strcpy(command, "echo ");
            strcat(command, send);
            strcat(command, " > "); strcat(command, name); strcat(command, "\\in\\"); strncat(command, &text, 1); strcat(command, ".txt");
            system(command);
            printf("Outpot of testcase %i: ", c1);
            scanf("%s", &send);
            getchar();
            strcpy(command, "echo "); strcat(command, send); strcat(command, " > "); strcat(command, name); strcat(command, "\\out\\");
            strncat(command, &text, 1); strcat(command, ".txt");
            system(command);

        }
        printf("Created Judge Successfully! \n");

        //printf("Doing tests Right now \n");
        //Judge();
        printf("3.File Location (C:\\file.c): ");
        scanf("%s", send);
        getchar();
        strcpy(command, "gcc -v ");
        strcat(command, send); strcat(command, " -o "); strcat(command, name); strcat(command, "\\t.exe");
        if (system(command) != 0) {
            printf("there is a compile error on your code, press enter continue: ");
            getchar();
            return;
        }
        system("cls");
        printf("Compiled Successfully !\n\nDoing test right now!\n");
        float score = Judge(name);
        printf("The result of test is: %f\nDo you want to see details?\n", score);
        scanf("%c", &enter);
        if (enter == 'y') {
            strcpy(command, "python sad.py "); strcat(command, name);
            system(command);
        }
        printf("press enter to continue");
        getchar();
        return;
    case '3':

        printf("name of your judge: ");
        scanf("%s", name);
        getchar();
        DIR *dir = opendir(name);
        printf("%s", command);
        printf("\nDiscovering the Judge!...\n");
        if (!dir) {
            printf("The judge that you said does not exist! pls make sure you wrote currectly!\npress enter to continue: ");
            getchar();
            return;
        }
        strcpy(command, name); strcat(command, "\\in");
        dir = opendir(command);
        if (!dir) {
            printf("The judge seems missing some files you might delete it and create new judge\npress enter to continue");
            getchar();
            return;
        }
        strcpy(command, name); strcat(command, "\\out");
        dir = opendir(command);
        if (!dir) {
            printf("The judge seems missing some files you might delete it and create new judge\npress enter to continue");
            getchar();
            return;
        }
        printf("The judge discovered Successfully\n2.File location (C:\\filename.c): ");
        scanf("%s", send);
        getchar();
        strcpy(command, "gcc -v "); strcat(command, send); strcat(command, " -o "); strcat(command, name); strcat(command, "t.exe");
        if (system(command) != 0) {
            printf("there is a compile error on your code, press enter continue: ");
            getchar();
            return;
        }
        system("cls");
        printf("Doing Tests Right NOW!!!!!\n\n");
                printf("The result of test is: %f\nDo you want to see details?\n", score);
        scanf("%c", &enter);
        if (enter == 'y') {
            strcpy(command, "python sad.py "); strcat(command, name);
            system(command);
        }
        printf("press enter to continue: ");
        getchar();
        return;
    }

}



int main() {
    while(1) {
        system("cls");
        ui();
    }

}
