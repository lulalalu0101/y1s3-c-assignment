#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#pragma warning(disable:4996)

void introMenu();

void showTrainSchedule();

void firstInputData();

void memberLogin();

void memberMenu();

void staffLogin();

void staffMenu();

void ticketTracking();

void bookingTicket();

struct train {
    char code[10];
    char from[50];
    char to[50];
    double price;
    int timing;
};

struct member {
    char id[10];
    char name[50];
    char password[50];
};

struct staff {
    char id[10];
    char name[50];
    char password[50];
};

int main() {

    firstInputData();
    introMenu();

    return 0;



//    // output struct
//
//    struct train trainSchedule[10];
//    struct member memberInfo[10];
//    struct staff staffInfo[10];
//
//    // train output
//
//    FILE*firstOutputTrain = fopen("/Users/jhui/CLionProjects/untitled1/trainSchedule.bin", "rb");
//
//    if (firstOutputTrain == NULL) {
//        printf("Error opening file!\n");
//        return 1;
//    }
//
//    for (int i = 0; i < 10; i++) {
//        fread(&trainSchedule[i], sizeof(struct train), 1, firstOutputTrain);
//    }
//
//    fclose(firstOutputTrain);
//
//    // member output
//
//    FILE*firstOutputMember = fopen("/Users/jhui/CLionProjects/untitled1/memberData.txt", "r");
//
//    if (firstOutputMember == NULL) {
//        printf("Error opening file!\n");
//        return 1;
//    }
//
//    for (int i = 0; i < 5; i++) {
//        fscanf(firstOutputMember, "%s %s %s", memberInfo[i].id, memberInfo[i].name, memberInfo[i].password);
//    }
//
//    fclose(firstOutputMember);
//
//    // staff output
//
//    FILE*firstOutputStaff = fopen("/Users/jhui/CLionProjects/untitled1/staffData.bin", "rb");
//
//    if (firstOutputStaff == NULL) {
//        printf("Error opening file!\n");
//        return 1;
//    }
//
//    for (int i = 0; i < 4; i++) {
//        fread(&staffInfo[i], sizeof(struct staff), 1, firstOutputStaff);
//    }
//
//    fclose(firstOutputStaff);
//
//    // output result
//
//    for (int i = 0; i < 4; i++) {
//        printf("%s   %s   %s\n", staffInfo[i].id, staffInfo[i].name, staffInfo[i].password);
//    }
//
//    for (int i = 0; i < 4; i++) {
//        printf("%s   %s   %s\n", memberInfo[i].id, memberInfo[i].name, memberInfo[i].password);
//    }
//
//    for (int i = 0; i < 10; i++) {
//        printf("%s   %s   %s   %.2lf %d mins\n", trainSchedule[i].code, trainSchedule[i].from, trainSchedule[i].to, trainSchedule[i].price/100.00, trainSchedule[i].timing);
//    }


}

void firstInputData() {

    struct train trainList[10] = {
            {"KL001", "KL Sentral",          "Perak",           4000,  240},
            {"KL002", "KL Sentral",          "Negeri Sembilan", 2000,  120},
            {"KL003", "KL Sentral",          "Selangor",        1500,  120},
            {"KL004", "KL Sentral",          "Kedah",           5000,  360},
            {"KL005", "KL Sentral",          "Kelantan",        2000,  180},
            {"KL006", "KL Sentral",          "Johor",           3000,  300},
            {"KL007", "KL Sentral",          "Terengganu",      3000,  210},
            {"KL008", "KL Sentral",          "Penang",          5000,  360},
            {"KL009", "KL Sentral",          "Perlis",          6000,  450},
            {"KL010", "KL Sentral",          "Malacca",         3000,  240}
    };

    struct member memberList[5] = {
            {"M1001", "Jhui", "qwe"},
            {"M1002", "Eric", "zxc"},
            {"M1003", "LiJuin", "asd"},
            {"M1004", "YHang", "bnm"}
    };

    struct staff staffList[5] = {
            {"S1001", "Pua Jie Hui", "123"},
            {"S1002", "Eric Liau Yee Kai", "456"},
            {"S1003", "Shak Li Juin", "789"},
            {"S1004", "Lim Yu Hang", "012"}
    };

    // train input

    FILE*firstInputTrain = fopen("/Users/jhui/CLionProjects/untitled1/trainSchedule.bin", "wb");

    if (firstInputTrain == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 10; i++) {
        fwrite(&trainList[i], sizeof(struct train), 1, firstInputTrain);
    }

    fclose(firstInputTrain);

    // member input

    FILE*firstInputMember = fopen("/Users/jhui/CLionProjects/untitled1/memberData.txt", "w");

    if (firstInputMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fprintf(firstInputMember, "%s %s %s\t", memberList[i].id, memberList[i].name, memberList[i].password);
    }

    fclose(firstInputMember);

    // staff input

    FILE*firstInputStaff = fopen("/Users/jhui/CLionProjects/untitled1/staffData.bin", "wb");

    if (firstInputStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fwrite(&staffList[i], sizeof(struct staff), 1, firstInputStaff);
    }

    fclose(firstInputStaff);

    // duty input


}

void introMenu() {
    
    int selected = -1;

    printf("\nWelcome to Train System!\n");
    printf("1. Member Information System\n2. Staff Information System\n3.Ticket Tracking\n4.Exit\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 4) {

        if (selected > 0 && selected < 5) {
            if (selected == 1) {
                memberLogin();
                memberMenu();
            } else if (selected == 2) {
                staffLogin();
                staffMenu();
            } else if (selected == 3) {
                ticketTracking();
            }
        } else {
            printf("\nInvalid input, please try again.\n");
        }

        printf("\nWelcome to Train System!\n");
        printf("1. Member Information System\n2. Staff Information System\n3.Ticket Tracking\n4.Exit\n");
        printf("> Select: ");
        scanf("%d", &selected);
        rewind(stdin);
    }

    printf("\nThanks for using our system, see you next time!\n");
    system("pause");
    exit(-1);
}
