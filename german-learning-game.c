#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT 100
#define NUM_OPTIONS 4

typedef struct {
    char german[50];
    char english[50];
    char level[3];  // B1, B2, C1, C2
} Word;

typedef struct {
    int health;
    int score;
    char current_word[50];
} Player;

// Advanced German vocabulary (B1-C2)
Word vocabulary[] = {
    {"allerdings", "however", "B1"},
    {"ausgerechnet", "of all things", "B2"},
    {"beziehungsweise", "respectively", "B2"},
    {"dennoch", "nevertheless", "B1"},
    {"erstaunlich", "astonishing", "B1"},
    {"gewissermaßen", "in a way", "C1"},
    {"hingegen", "on the other hand", "B2"},
    {"insbesondere", "especially", "B1"},
    {"jedenfalls", "in any case", "B1"},
    {"mindestens", "at least", "B1"},
    {"nämlich", "namely", "B1"},
    {"offensichtlich", "obviously", "B2"},
    {"quasi", "practically", "B2"},
    {"schließlich", "finally", "B1"},
    {"sozusagen", "so to speak", "B2"},
    {"tatsächlich", "actually", "B1"},
    {"übrigens", "by the way", "B1"},
    {"vermutlich", "presumably", "B2"},
    {"womöglich", "possibly", "C1"},
    {"zumal", "especially since", "C2"}
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printStatus(Player *player) {
    printf("\nHealth: %d | Score: %d\n", player->health, player->score);
    printf("----------------------------------------\n");
}

void shuffleArray(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void getMultipleChoiceOptions(int correctIndex, int *optionIndices) {
    int vocabSize = sizeof(vocabulary) / sizeof(vocabulary[0]);
    int allIndices[vocabSize];
    
    // Initialize array with all indices
    for (int i = 0; i < vocabSize; i++) {
        allIndices[i] = i;
    }
    
    // Remove the correct answer from pool
    allIndices[correctIndex] = allIndices[vocabSize - 1];
    
    // Shuffle remaining indices
    shuffleArray(allIndices, vocabSize - 1);
    
    // Place correct answer in random position
    int correctPosition = rand() % NUM_OPTIONS;
    for (int i = 0; i < NUM_OPTIONS; i++) {
        if (i == correctPosition) {
            optionIndices[i] = correctIndex;
        } else {
            optionIndices[i] = allIndices[i < correctPosition ? i : i - 1];
        }
    }
}

void gameLoop(Player *player) {
    char input[MAX_INPUT];
    int vocabSize = sizeof(vocabulary) / sizeof(vocabulary[0]);
    int currentWord = 0;
    int optionIndices[NUM_OPTIONS];
    
    srand(time(NULL));  // Initialize random seed
    
    while (player->health > 0 && currentWord < vocabSize) {
        clearScreen();
        printStatus(player);
        
        printf("\nTranslate this German word (%s level):\n", vocabulary[currentWord].level);
        printf("\n\t%s\n\n", vocabulary[currentWord].german);
        
        getMultipleChoiceOptions(currentWord, optionIndices);
        
        printf("Choose the correct English translation:\n");
        for (int i = 0; i < NUM_OPTIONS; i++) {
            printf("%d) %s\n", i + 1, vocabulary[optionIndices[i]].english);
        }
        printf("\nYour choice (1-%d): ", NUM_OPTIONS);
        
        fgets(input, MAX_INPUT, stdin);
        int choice = atoi(input) - 1;
        
        if (choice >= 0 && choice < NUM_OPTIONS && optionIndices[choice] == currentWord) {
            printf("\nCorrect! Excellent work!\n");
            printf("This word is commonly used in %s level German.\n", vocabulary[currentWord].level);
            player->score += 10;
            currentWord++;
        } else {
            printf("\nIncorrect! The right answer was: %s\n", vocabulary[currentWord].english);
            player->health -= 1;
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    clearScreen();
    if (player->health <= 0) {
        printf("\nGame Over! You ran out of health!\n");
    } else {
        printf("\nCongratulations! You've mastered these advanced German words!\n");
    }
    printf("Final Score: %d\n", player->score);
}

int main() {
    Player player = {3, 0, ""};  // Start with 3 health
    
    printf("Welcome to Advanced German Vocabulary Training!\n");
    printf("Test your knowledge of B1-C2 level words!\n");
    printf("Press Enter to begin...");
    getchar();
    
    gameLoop(&player);
    
    return 0;
}
