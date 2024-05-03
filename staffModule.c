#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#pragma warning(disable:4996)

struct staff {
    char id[10];
    char name[50];
    char password[50];
};

struct train {
    char code[10];
    char from[50];
    char to[50];
    double price;
    int timing;
};

struct punchCard {
    char id[10];
    char timePunchIn[100];
};

struct staff staffInfo[10];
struct train trainSchedule[10];

void introMenu();

void getStaffData();

void getTrainData();

void staffLogin();

void staffMenu();

void modifyStaff(int staffIndex);

void modifyTrainSchedule();

void punchCard();

void updatePunchCard(int staffIndex);

void displayPunchCard(int staffIndex);

void getStaffData() {

    FILE *firstOutputStaff = fopen("/Users/jhui/CLionProjects/untitled1/staffData.bin", "rb");

    if (firstOutputStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fread(&staffInfo[i], sizeof(struct staff), 1, firstOutputStaff);
    }

    fclose(firstOutputStaff);

}

void staffLogin() {

    getStaffData();

    char inputID[100];
    char inputPassword[100];
    int staffIndex = -1;

    while (staffIndex == -1) {
        printf("\nWelcome to Train Staff Information System\n");
        printf("> Staff ID: ");
        scanf("%s", inputID);
        rewind(stdin);

        printf("> Password: ");
        scanf("%s", inputPassword);
        rewind(stdin);

        for (int i = 0; i < 4; i++) {
            if (strcmp(inputID, staffInfo[i].id) == 0) {
                if (strcmp(inputPassword, staffInfo[i].password) == 0) {
                    staffIndex = i;
                    break;
                }
            }
        }

        if (staffIndex < 0) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    // store staff index in file
    FILE *tempStaff = fopen("/Users/jhui/CLionProjects/untitled1/tempStaff.bin", "wb");

    if (tempStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fwrite(&staffIndex, sizeof(staffIndex), 1, tempStaff);

    fclose(tempStaff);

}

void staffMenu() {

    int selected = -1;
    int staffIndex = -1;

    FILE *tempStaff = fopen("/Users/jhui/CLionProjects/untitled1/tempStaff.bin", "rb");

    if (tempStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fread(&staffIndex, sizeof(staffIndex), 1, tempStaff);

    fclose(tempStaff);

    printf("\nWelcome back, %s !\n", staffInfo[staffIndex].name);
    printf("\n1. Modify Staff Details\n2. Modify Train Schedule\n3. Punch Card\n4. Go Back\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 4) {

        if (selected > 0 && selected < 5) {
            if (selected == 1) {
                modifyStaff(staffIndex);
            } else if (selected == 2) {
                modifyTrainSchedule();
            } else if (selected == 3) {
                punchCard();
            }
        } else {
            printf("\nInvalid input, please try again.\n");
        }

        printf("\nWelcome back, %s !\n", staffInfo[staffIndex].name);
        printf("\n1. Modify Staff Details\n2. Modify Train Schedule\n3. Punch Card\n4. Go Back\n");
        printf("> Select: ");
        scanf("%d", &selected);
        rewind(stdin);
    }

    introMenu();

}

void modifyStaff(int staffIndex) {

    int selected = -1;
    char confPass = 'n';
    char confName = 'n';
    char tempName[100];
    char tempPass[20];

    printf("Select a info to edit: \n1. Staff Name\n2. Password\n3. Go back\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 3) {

        if (selected > 0 && selected < 4) {

            if (selected == 1) {

                printf("Your current name is %s , are you sure you want to change?\n", staffInfo[staffIndex].name);

                while (1) {
                    printf("> Press 'Y' to continue modify, press 'N' go back to MENU (Data will LOST) : ");
                    scanf("%c", &confName);
                    rewind(stdin);

                    if (confName == 'Y' || confName == 'N') {
                        if (confName == 'Y') {

                            printf("> New Name (no space): ");
                            scanf("%[^\n]", tempName);
                            rewind(stdin);
                            strcpy(staffInfo[staffIndex].name, tempName);
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
                       staffInfo[staffIndex].password);

                while (1) {
                    printf("> Press 'Y' to continue modify, press 'N' go back to MENU (Data will LOST) : ");
                    scanf("%c", &confPass);
                    rewind(stdin);

                    if (confPass == 'Y' || confPass == 'N') {
                        if (confPass == 'Y') {
                            printf("> New Password (no space): ");
                            scanf("%s", tempPass);
                            rewind(stdin);
                            strcpy(staffInfo[staffIndex].password, tempPass);

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

    // Update staff data
    FILE *updateStaff = fopen("/Users/jhui/CLionProjects/untitled1/staffData.bin", "wb");

    if (updateStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 4; i++) {
        fwrite(&staffInfo[i], sizeof(struct staff), 1, updateStaff);
    }

    fclose(updateStaff);
}

void punchCard() {

    int selected = -1;
    int staffIndex = -1;

    FILE *tempStaff = fopen("/Users/jhui/CLionProjects/untitled1/tempStaff.bin", "rb");

    if (tempStaff == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fread(&staffIndex, sizeof(staffIndex), 1, tempStaff);

    fclose(tempStaff);

    printf("1. Punch In\n2. View Punch Card\n3. Go Back\n");
    printf("> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 3) {
        if (selected > 0 && selected < 4) {
            if (selected == 1) {
                updatePunchCard(staffIndex);
            } else if (selected == 2) {
                displayPunchCard(staffIndex);
            }
        } else {
            printf("\nInvalid input, please try again.\n");
        }
        printf("\n1. Punch In\n2. View Punch Card\n3. Go Back\n");
        printf("> Select: ");
        scanf("%d", &selected);
        rewind(stdin);
    }

}

void updatePunchCard(int staffIndex) {

    time_t rawtime;

    struct tm *timeInfo;
    struct punchCard tempPunchCard;

    char timeString[80];

    time(&rawtime);
    timeInfo = localtime(&rawtime);

    // Format the Time
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Format data
    strcpy(tempPunchCard.id, staffInfo[staffIndex].id);
    strcpy(tempPunchCard.timePunchIn, timeString);

    // Store stringify Time in File
    FILE *updatePunchCard = fopen("/Users/jhui/CLionProjects/untitled1/punchCardData.bin", "ab");

    if (updatePunchCard == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fwrite(&tempPunchCard, sizeof(tempPunchCard), 1, updatePunchCard);

    fclose(updatePunchCard);

    printf("\nPunch in at: %s\n", timeString);
    printf("\nUpdate Completed!\n");

}

void displayPunchCard(int staffIndex) {

    struct punchCard punchCardList[100];

    int counter = 0;

    printf("================================================================================\n");
    printf("                                    Punch Card \n");
    printf("================================================================================\n");
    // Get Punch Card Data from File
    FILE *outputPunchCard = fopen("/Users/jhui/CLionProjects/untitled1/punchCardData.bin", "rb");

    if (outputPunchCard == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 100; i++) {
        fread(&punchCardList[i], sizeof(struct punchCard), 1, outputPunchCard);
        if (strcmp(staffInfo[staffIndex].id, punchCardList[i].id) == 0) {
            counter++;
            printf("%d. %30s\n", counter, punchCardList[i].timePunchIn);
        }
    }

    fclose(outputPunchCard);
}