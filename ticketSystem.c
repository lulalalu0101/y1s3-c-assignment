#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#pragma warning(disable:4996)

struct train {
    char code[10];
    char from[50];
    char to[50];
    double price;
    int timing;
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

struct member {
    char id[10];
    char name[50];
    char password[50];
};

struct member memberInfo[10];
struct train trainSchedule[10];
struct ticket temp;

void getTrainData();

void getMemberData();

void introMenu();

void bookingTicket();

void showTrainSchedule();

void memberMenu();

void generateCode(char *code);

void convertTime(int time);

void ticketTracking();

void bookingTicket() {

    char inputCode[50];
    int trainIndex = -1;
    int qtyTicket = -1;
    char confBooking = 'n';
    int day = -1;
    int month = -1;
    int checkDate = -1;
    int time = -1;
    int memberIndex = -1;
    char confPurchase = 'n';

    getTrainData();

    getMemberData();

    showTrainSchedule();

    FILE *tempMember = fopen("/Users/jhui/CLionProjects/untitled1/tempMember.bin", "rb");

    if (tempMember == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fread(&memberIndex, sizeof(memberIndex), 1, tempMember);

    fclose(tempMember);

    while (trainIndex < 0) {

        printf("> Please enter the Train Code : ");
        scanf("%s", inputCode);
        rewind(stdin);

        for (int i = 0; i < 10; i++) {
            if (strcmp(inputCode, trainSchedule[i].code) == 0) {
                trainIndex = i;
                break;
            }
        }

        if (trainIndex < 0) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    while (qtyTicket <= 0 || qtyTicket > 99) {
        printf("> Quantity : ");
        scanf("%d", &qtyTicket);
        rewind(stdin);

        if (qtyTicket <= 0 || qtyTicket > 99) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    while (1) {
        printf("\n%d ticket(s) for train code %s\n", qtyTicket, trainSchedule[trainIndex].code);
        printf("> Press 'Y' to confirm the Booking, press 'N' to go back : ");
        scanf("%c", &confBooking);

        if (confBooking == 'Y' || confBooking == 'N') {
            if (confBooking == 'N') {
                memberMenu();
                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }


    while (checkDate < 0) {
        printf("> Data (day month): ");
        scanf("%d %d", &day, &month);
        rewind(stdin);

        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day > 0 && day < 32) {
                    checkDate = 1;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day > 0 && day < 31) {
                    checkDate = 1;
                }
                break;
            case 2:
                if (day > 0 && day < 30) {
                    checkDate = 1;
                }
                break;
        }

        if (checkDate < 0) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    while (time < 1 || time > 10) {

        printf("===================================================\n");
        printf("                   Department Time\n");
        printf("===================================================\n");
        printf("No.               AM           No.               PM\n");
        printf("===================================================\n");
        printf("1.             07.00           6.             02.00\n");
        printf("2.             08.00           7.             03.00\n");
        printf("3.             09.00           8.             04.00\n");
        printf("4.             10.00           9.             05.00\n");
        printf("5.             11.00           10.            06.00\n");
        printf("===================================================\n");

        printf("> Select: ");
        scanf("%d", &time);
        rewind(stdin);

        if (time < 1 || time > 10) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    generateCode(temp.code);
    strcpy(temp.trainCode, trainSchedule[trainIndex].code);
    strcpy(temp.memberID, memberInfo[memberIndex].id);
    temp.qty = qtyTicket;
    temp.date = day;
    temp.month = month;
    temp.time = time;

    printf("\n===================================================");
    printf("\nBooking.ID     Train Code     QTY     PER.       RM");
    printf("\n===================================================");
    printf("\n%-15s%-15s%d%11.2lf%9.2lf", temp.code, temp.trainCode, temp.qty, trainSchedule[trainIndex].price / 100,
           (trainSchedule[trainIndex].price * temp.qty) / 100);
    printf("\n===================================================\n");
    printf("\nTotal                                         %.2lf", (trainSchedule[trainIndex].price * temp.qty) / 100);
    printf("\n===================================================\n");

    while (1) {
        printf("> Press 'Y' to confirm the Purchase, press 'N' go back to MENU (Data will LOST) : ");
        scanf("%c", &confPurchase);
        rewind(stdin);

        if (confPurchase == 'Y' || confPurchase == 'N') {
            if (confPurchase == 'N') {
                memberMenu();
                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }

    // Store ticket into File
    FILE *inputTicket = fopen("/Users/jhui/CLionProjects/untitled1/ticketData.txt", "a");

    if (inputTicket == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    fprintf(inputTicket, "%s %s %s %d %d %d %d\t", temp.code, temp.trainCode, temp.memberID, temp.qty, temp.date,
            temp.month, temp.time);

    fclose(inputTicket);

    printf("\n===================================================\n");
    printf("                Booking Complete!\n");
    printf("===================================================\n");
    printf("\nHere's your Ticket Details:\n");
    printf("\nBooking ID      : %s\n", temp.code);
    printf("Train Code      : %s\n", temp.trainCode);
    printf("From            : %s\n", trainSchedule[trainIndex].from);
    printf("To              : %s\n", trainSchedule[trainIndex].to);
    printf("Data            : %d / %d / 2024\n", temp.date, temp.month);
    printf("From            : %s\n", trainSchedule[trainIndex].from);
    printf("Time            : ");
    convertTime(temp.time);
    printf("\n===================================================\n");

}

void generateCode(char *code) {

    const char *characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digits = "0123456789";
    const int codeLength = 6;

    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        code[i] = characters[rand() % 26]; // Randomly select a character from 'A' to 'Z'
    }
    for (int i = 3; i < codeLength; i++) {
        code[i] = digits[rand() % 10]; // Randomly select a digit from '0' to '9'
    }

    code[codeLength] = '\0';
}

void convertTime(int time) {
    switch (time) {
        case 1:
            printf("07:00 AM\n");
            break;
        case 2:
            printf("08:00 AM\n");
            break;
        case 3:
            printf("09:00 AM\n");
            break;
        case 4:
            printf("10:00 AM\n");
            break;
        case 5:
            printf("11:00 AM\n");
            break;
        case 6:
            printf("02.00 PM\n");
            break;
        case 7:
            printf("03.00 PM\n");
            break;
        case 8:
            printf("04.00 PM\n");
            break;
        case 9:
            printf("05.00 PM\n");
            break;
        default:
            printf("06.00 PM\n");
            break;
    }
}

void ticketTracking() {

    char inputCode[10] = "";
    int ticketIndex = -1;
    int trainIndex = -1;
    int memberIndex = -1;

    struct ticket ticketList[100];

    getTrainData();
    getMemberData();

    FILE *outputTicket = fopen("/Users/jhui/CLionProjects/untitled1/ticketData.txt", "r");

    if (outputTicket == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 100; i++) {
        fscanf(outputTicket, "%s %s %s %d %d %d %d\t", ticketList[i].code, ticketList[i].trainCode, ticketList[i].memberID, &ticketList[i].qty, &ticketList[i].date, &ticketList[i].month, &ticketList[i].time);
    }

    fclose(outputTicket);

    while (ticketIndex < 0) {
        printf("> Enter the BookingID (Enter 'back' to go back): ");
        scanf("%s", inputCode);
        rewind(stdin);

        for (int i = 0; i < 100; i++) {
            if (strcmp(inputCode, ticketList[i].code) == 0) {
                ticketIndex = i;
                break;
            }
        }

        if (strcmp(inputCode, "back") == 0) {
            introMenu();
            break;
        } else if (ticketIndex < 0) {
            printf("\nInvalid input, please try again.\n");
        }
    }

    // check train index via train code
    for (int i = 0; i < 10; i++) {
        if (strcmp(ticketList[ticketIndex].trainCode, trainSchedule[i].code) == 0) {
            trainIndex = i;
            break;
        }
    }

    // check member index via member id
    for (int i = 0; i < 4; i++) {
        if (strcmp(ticketList[ticketIndex].memberID, memberInfo[i].id) == 0) {
            memberIndex = i;
            break;
        }
    }

    printf("\nHere's your Ticket Details:\n");
    printf("\n===================================================\n");
    printf("\nBooking ID      : %s\n", ticketList[ticketIndex].code);
    printf("Member Name     : %s\n", memberInfo[memberIndex].name);
    printf("Train Code      : %s\n", trainSchedule[trainIndex].code);
    printf("From            : %s\n", trainSchedule[trainIndex].from);
    printf("To              : %s\n", trainSchedule[trainIndex].to);
    printf("Data            : %d / %d / 2024\n", ticketList[ticketIndex].date, ticketList[ticketIndex].month);
    printf("Time            : ");
    convertTime(ticketList[ticketIndex].time);
    printf("\n===================================================\n");

}