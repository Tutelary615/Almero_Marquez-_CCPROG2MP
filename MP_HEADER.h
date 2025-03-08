#define ERRORFORMATSTRING "\033[0;31m%s\033[0m"
#define WARNINGFORMATSTRING "\033[0;33m%s\033[0m"

typedef char string20[21];
typedef char string50[51];

typedef struct {
    string20 language;
    string20 translation;

} languageTranslationPair;

typedef struct {
	languageTranslationPair pairs[10];
	int pairCount;
} entry;

bool getInteger(int* num);
void printMenu(string50 choices[], int numberOfChoices);
bool isMenuInputValid(bool isInputValid, int lowerBound, int upperBound, int input);
int getAndValidateMenuInput(int lowerBound, int upperBound);
int mainMenu();
int manageDataMenu(int entryCount);
void getPair(string20 tempLanguage, string20 tempTranslation, 
             char* characterAfterLanguage, char* characterAfterTranslation);
bool isLanguageTranslationPairValid(string20 tempLanguage, string20 tempTranslation, 
                                    char characterAfterLanguage, char characterAfterTranslation);
void formatLanguageOrTranslation(string20 str);
void addEntry(entry* e);
void sortEntryAlphabeticallyByLanguage(entry* e);
int searchForLanguageTranslationPair(entry e, string20 languageKey, string20 translationKey);