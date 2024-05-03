#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

struct member {
    char id[10];
    char name[50];
    char password[50];
};

struct ticket {
    char code[10];
    char trainCode[10];
    char memberID[10];
    int qty;
    int date;
    int month;
    int time;
};

struct train {
    char code[10];
    char from[50];
    char to[50];
    double price;
    int timing;
};

struct member memberInfo[10];
struct train trainSchedule[10];

void introMenu();

void getMemberData();

void getTrainData();

void memberLogin();

void memberMenu();

void memberModify(int memberIndex);

void bookingTicket();

void purchaseHistory();

void getMemberData() {

    FILE *firstOutputMember = fopen("/Users/jhui/CLionProjects/untitled1/memberData.txt", "r");

    if (firstOutputMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 5; i++) {
        fscanf(firstOutputMember, "%s %s %s", memberInfo[i].id, memberInfo[i].name, memberInfo[i].password);
    }

    fclose(firstOutputMember);
}

void memberLogin() {

    getMemberData();

    char inputID[100];
    char inputPassword[100];
    int memberIndex = -1;

    while (memberIndex == -1) {
        printf("\nWelcome to Train Member System\n");
        printf("> User ID: ");
        scanf("%s", inputID);
        rewind(stdin);

        printf("> Password: ");
        scanf("%s", inputPassword);
        rewind(stdin);

        for (int i = 0; i < 4; i++) {
            if (strcmp(inputID, memberInfo[i].id) == 0) {
                if (strcmp(inputPassword, memberInfo[i].password) == 0) {
                    memberIndex = i;
                    break;
                }
            }
        }

        if (memberIndex < 0) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    // store member index in file
    FILE *tempMember = fopen("/Users/jhui/CLionProjects/untitled1/tempMember.bin", "wb");

    if (tempMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fwrite(&memberIndex, sizeof(memberIndex), 1, tempMember);

    fclose(tempMember);

}

void memberMenu() {

    int selected = -1;
    int memberIndex = -1;

    FILE *tempMember = fopen("/Users/jhui/CLionProjects/untitled1/tempMember.bin", "rb");

    if (tempMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fread(&memberIndex, sizeof(memberIndex), 1, tempMember);

    fclose(tempMember);

    printf("\nWelcome back, %s !\n", memberInfo[memberIndex].name);
    printf("\n1. Modify Member Details\n2. Booking Ticket\n3. View Purchased History\n4. Go Back\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 4) {

        if (selected > 0 && selected < 5) {
            if (selected == 1) {
                memberModify(memberIndex);
            } else if (selected == 2) {
                bookingTicket();
            } else if (selected == 3) {
                purchaseHistory();
            }
        } else {
            printf("\nInvalid input, please try again.\n");
        }

        printf("\nWelcome back, %s !\n", memberInfo[memberIndex].name);
        printf("\n1. Modify Member Details\n2. Booking Ticket\n3. View Purchased History\n4. Go Back\n");
        printf("> Select: ");
        scanf("%d", &selected);
        rewind(stdin);
    }

    introMenu();
}

void memberModify(int memberIndex) {

    struct member memberList[4];

    int selected = -1;
    char confName = 'n';
    char confPass = 'n';
    char tempName[20];
    char tempPass[20];

    // Get temp member details
    FILE *outputMember = fopen("/Users/jhui/CLionProjects/untitled1/memberData.txt", "r");

    if (outputMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fscanf(outputMember, "%s %s %s", memberList[i].id, memberList[i].name, memberList[i].password);
    }

    fclose(outputMember);

    printf("Select a info to edit: \n1. Member Name\n2. Password\n3. Go back\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 3) {

        if (selected > 0 && selected < 4) {

            if (selected == 1) {

                printf("Your current name is %s , are you sure you want to change?\n", memberList[memberIndex].name);

                while (1) {
                    printf("> Press 'Y' to continue modify, press 'N' go back to MENU (Data will LOST) : ");
                    scanf("%c", &confName);
                    rewind(stdin);

                    if (confName == 'Y' || confName == 'N') {
                        if (confName == 'Y') {

                            printf("> New Name (no space): ");
                            scanf("%s", tempName);
                            rewind(stdin);
                            strcpy(memberList[memberIndex].name, tempName);
                            printf("\nUpdate completed!\n");
                            break;
                        }
                        break;
                    } else {
                        printf("\nInvalid input, please try again.\n");
                    }
                }

            } else if (selected == 2) {
                printf("Your current password is %s , are you sure you want to change?\n",
                       memberList[memberIndex].password);

                while (1) {
                    printf("> Press 'Y' to continue modify, press 'N' go back to MENU (Data will LOST) : ");
                    scanf("%c", &confPass);
                    rewind(stdin);

                    if (confPass == 'Y' || confPass == 'N') {
                        if (confPass == 'Y') {
                            printf("> New Password (no space): ");
                            scanf("%s", tempPass);
                            rewind(stdin);
                            strcpy(memberList[memberIndex].password, tempPass);

                            printf("\nUpdate completed!\n");
                            break;
                        }
                        break;
                    } else {
                        printf("\nInvalid input, please try again.\n");
                    }
                }
            }
        } else {
            printf("\nInvalid input, please try again.\n");
        }

        printf("\nSelect a info to edit: \n1. Member Name\n2. Password\n3. Go back\n");
        printf("> Select: ");
        scanf("%d", &selected);
        rewind(stdin);
    }


    // Input new data
    FILE *updateMember = fopen("/Users/jhui/CLionProjects/untitled1/memberData.txt", "w");

    if (updateMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fprintf(updateMember, "%s %s %s\t", memberList[i].id, memberList[i].name, memberList[i].password);
    }

    fclose(updateMember);
}


void purchaseHistory() {

    int memberIndex = -1;

    struct ticket ticketList[100];

    printf("================================================================================\n");
    printf("                              Purchase History\n");
    printf("================================================================================\n");
    printf("No.  Booking ID        From             To                                  Date\n");

    // Get member Index
    FILE *tempMember = fopen("/Users/jhui/CLionProjects/untitled1/tempMember.bin", "rb");

    if (tempMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fread(&memberIndex, sizeof(memberIndex), 1, tempMember);

    fclose(tempMember);

    getTrainData();

    getMemberData();

    // Get ticket list
    FILE *outputTicket = fopen("/Users/jhui/CLionProjects/untitled1/ticketData.txt", "r");

    if (outputTicket == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 100; i++) {
        fscanf(outputTicket, "%s %s %s %d %d %d %d\t", ticketList[i].code, ticketList[i].trainCode,
               ticketList[i].memberID, &ticketList[i].qty, &ticketList[i].date, &ticketList[i].month,
               &ticketList[i].time);
    }

    fclose(outputTicket);

    int count = 0;

    for (int i = 0; i < 100; i++) {
        if (strcmp(memberInfo[memberIndex].id, ticketList[i].memberID) == 0) {
            for (int j = 0; j < 10; j++) {
                if (strcmp(ticketList[i].trainCode, trainSchedule[j].code) == 0) {
                    count++;
                    printf("%d.%-18s%-17s%-17s%d / %d / 2024\n ", count, ticketList[i].code, trainSchedule[j].from,
                           trainSchedule[j].to, ticketList[i].date, ticketList[i].month);
                }
            }
        }
    }

    if (count < 1) {
        printf("\nNo Purchased History!\n");
    }

}