#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

struct train {
    char code[10];
    char from[50];
    char to[50];
    double price;
    int timing;
};

struct train trainSchedule[10];

void getTrainData();

void updateTrainData();

void staffMenu();

void showTrainSchedule();

void modifyTrainSchedule();

void editFrom(int trainIndex);

void editTo(int trainIndex);

void editPrice(int trainIndex);

void editTiming(int trainIndex);


void getTrainData() {

    FILE *firstOutputTrain = fopen("/Users/jhui/CLionProjects/untitled1/trainSchedule.bin", "rb");

    if (firstOutputTrain == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 10; i++) {
        fread(&trainSchedule[i], sizeof(struct train), 1, firstOutputTrain);
    }

    fclose(firstOutputTrain);

}

void showTrainSchedule() {

    getTrainData();

    printf("================================================================================\n");
    printf("                              Train Schedule\n");
    printf("================================================================================\n");
    printf("Code      From                To                  Price(RM)             Est.Time\n");
    printf("================================================================================\n");
    for (int i = 0; i < 10; i++) {
        printf("%-10s%-20s%-20s%9.2lf%9d hr%4d mins \n", trainSchedule[i].code, trainSchedule[i].from,
               trainSchedule[i].to, trainSchedule[i].price / 100.00, trainSchedule[i].timing / 60,
               trainSchedule[i].timing % 60);
    }
    printf("================================================================================\n");
}

void modifyTrainSchedule() {

    int trainIndex = -1;
    char inputCode[10] = "";
    int selected = -1;

    getTrainData();

    showTrainSchedule();

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

    printf("\nEdit Train Destination: \n1. From Location\n2. Destination Location\n\nEdit Train Details:\n3. Train Price\n4. Time Duration\n\n5. Go back");
    printf("\n> Select: ");
    scanf("%d", &selected);
    rewind(stdin);

    while (selected != 5) {

        if (selected > 0 && selected < 6) {
            if (selected == 1) {
                editFrom(trainIndex);
                selected = 5;
            } else if (selected == 2) {
                editTo(trainIndex);
                selected = 5;
            } else if (selected == 3) {
                editPrice(trainIndex);
                selected = 5;
            } else if (selected == 4) {
                editTiming(trainIndex);
                selected = 5;
            }
        } else {
            printf("\nInvalid input, please try again.\n");

            printf("\nEdit Train Destination: \n1. From Location\n2. Destination Location\n\nEdit Train Details:\n3. Train Price\n4. Time Duration\n\n5. Go back");
            printf("\n> Select: ");
            scanf("%d", &selected);
            rewind(stdin);
        }
    }

    staffMenu();
}


void editFrom(int trainIndex) {

    char conf = 'n';
    char temp[50];

    printf("The current train FROM Location is %s,  are you sure you want to change?\n",
           trainSchedule[trainIndex].from);

    while (1) {
        printf("> Press 'Y' to continue edit, press 'N' go back to MENU (Data will LOST) : ");
        scanf("%c", &conf);
        rewind(stdin);

        if (conf == 'Y' || conf == 'N') {
            if (conf == 'Y') {

                printf("> New FROM Location: ");
                scanf("%[^\n]", temp);
                rewind(stdin);

                printf("\nUpdate Completed!\n");

                strcpy(trainSchedule[trainIndex].from, temp);

                updateTrainData();

                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }
}

void editTo(int trainIndex) {

    char conf = 'n';
    char temp[50];

    printf("The current train TO Location is %s,  are you sure you want to change?\n", trainSchedule[trainIndex].to);

    while (1) {
        printf("> Press 'Y' to continue edit, press 'N' go back to MENU (Data will LOST) : ");
        scanf("%c", &conf);
        rewind(stdin);

        if (conf == 'Y' || conf == 'N') {
            if (conf == 'Y') {
                printf("> New TO Location: ");
                scanf("%[^\n]", temp);
                rewind(stdin);

                printf("\nUpdate Completed!\n");

                strcpy(trainSchedule[trainIndex].to, temp);

                updateTrainData();
                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }
}

void editPrice(int trainIndex) {

    char conf = 'n';
    double temp;

    printf("The current train PRICE is %.2lf,  are you sure you want to change?\n",
           trainSchedule[trainIndex].price / 100.00);

    while (1) {
        printf("> Press 'Y' to continue edit, press 'N' go back to MENU (Data will LOST) : ");
        scanf("%c", &conf);
        rewind(stdin);

        if (conf == 'Y' || conf == 'N') {
            if (conf == 'Y') {

                while (1) {
                    printf("> New PRICE: ");
                    scanf("%lf", &temp);
                    rewind(stdin);

                    if (temp > 0) {
                        break;
                    }
                }

                printf("\nUpdate Completed!\n");

                trainSchedule[trainIndex].price = temp * 100;
                updateTrainData();
                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }

}

void editTiming(int trainIndex) {
    char conf = 'n';
    int hour = trainSchedule[trainIndex].timing / 60;
    int mins = trainSchedule[trainIndex].timing % 60;
    int tempHr = -1;
    int tempMins = -1;
    int temp = 0;

    printf("The current train TIME DURATION is %.d hr %d mins,  are you sure you want to change?\n", hour, mins);

    while (1) {
        printf("> Press 'Y' to continue edit, press 'N' go back to MENU (Data will LOST) : ");
        scanf("%c", &conf);
        rewind(stdin);

        if (conf == 'Y' || conf == 'N') {
            if (conf == 'Y') {
                while (1) {
                    printf("> Hour: ");
                    scanf("%d", &tempHr);
                    rewind(stdin);

                    printf("> Minutes: ");
                    scanf("%d", &tempMins);
                    rewind(stdin);

                    if (tempHr >= 0 && tempMins >= 0 && tempMins <= 60) {
                        temp = tempHr * 60 + tempMins;
                        if (temp > 0) {
                            break;
                        }
                    }
                    printf("\nInvalid input, please try again.\n");
                };

                trainSchedule[trainIndex].timing = temp;

                updateTrainData();
                break;
            }
            break;
        } else {
            printf("\nInvalid input, please try again.\n");
        }
    }

    printf("\nUpdate Completed!\n");

}

void updateTrainData() {
    FILE *inputTrain = fopen("/Users/jhui/CLionProjects/untitled1/trainSchedule.bin", "wb");

    if (inputTrain == NULL) {
        printf("Error opening file!\n");
        system("pause");
    }

    for (int i = 0; i < 10; i++) {
        fwrite(&trainSchedule[i], sizeof(struct train), 1, inputTrain);
    }

    fclose(inputTrain);
}