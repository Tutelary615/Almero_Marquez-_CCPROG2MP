#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include "MP_HEADER.h"

// CODING CONVENTIONS 
/*
    - put space between tokens (e.g. x = 1, NOT x=1)
    - pointer data types will be written as: char*, int*; NOT char *, int *
    - follow normal CCPORG2 code block format
    - variable naming: NO HUNGARIAN NOTATION, use camel case (first letter always lowercase)
    - typedef all structures 
        i.e:
            typedef struct
            {
                data...
            } <alias>;

*/

// INSTRUCTIONS FOR ALLOCATION
/*
    max number of entries: 150
    language and translation strings: max 20 characters
    language-translation pair: max 10 per entry 
*/
void 
printStringAscii(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        printf("%d_", str[i]);
    }
    printf("\n");
}
void initString(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}

bool 
getInteger(int* num)
{
    char firstCharacterEntered;
    char lastCharacterAfterNum;
    bool isInputValid = false;

    firstCharacterEntered = getc(stdin);

    if (firstCharacterEntered != '\n')
    {
        ungetc(firstCharacterEntered, stdin);
        scanf("%d", num);
        lastCharacterAfterNum = getc(stdin);
    }

    if (lastCharacterAfterNum == '\n')
    {
        isInputValid = true;
    }
    fflush(stdin);
    return isInputValid;
}

bool
isMenuInputValid(bool isInputValid, int lowerBound, int upperBound, int input)
{
	bool isValid = true;

	if (!isInputValid || input < lowerBound || input > upperBound)
	{
		printf(REDFORMATSTRING, "Entered number is invalid, try again\n");
		isValid = false;
	}
		
	return isValid;
}

int 
getAndValidateMenuInput(int lowerBound, int upperBound)
{
    int choice;
    bool isChoiceValid;
    do
	{
        printf("Enter choice: ");
		isChoiceValid = getInteger(&choice);
				
	} while (!isMenuInputValid(isChoiceValid, 1, upperBound, choice));
	return choice;
}

void 
printMenu(string50 choices[], int numberOfChoices)
{
    int i;
    for (i = 0; i < numberOfChoices; i++)
    {
        printf("%d - %s\n", (i + 1), choices[i]);
    }
}

int
mainMenu()
{
	int choice;
	bool isChoiceValid;
	string50 options[3] = {"Manage Data", "Translate Menu", "Exit"};
	
	printMenu(options, 3);
	
	do
	{
		printf("Select an option from the menu above: ");
		isChoiceValid = getInteger(&choice);
				
	} while (!isMenuInputValid(isChoiceValid, 1, 3, choice));
	return choice;
}

int 
manageDataMenu(int entryCount)
{
    string50 options[10] = {"Add Entry", "Import Data", "Add Translations", "Delete Entry", "Delete Translation",
                            "Display All Entries", "Search by Word", "Search By Translation", "Export Data", "Exit"};
    int choice;
    int upperBound;
    if (entryCount > 0)
    {
        printMenu(options, 10);
        upperBound = 10;
    }
    else
    {
        printMenu(options, 2);
        upperBound = 2;
    }
    printf("Select and option from the menu above\n");
    choice = getAndValidateMenuInput(1, upperBound);
    return choice;
}

bool 
isOperationConfirmed()
{
    int choice;
    printf("Enter the number corresponding to your choice\n");
    printf("1 - Yes\n");
    printf("2 - No\n");
    choice = getAndValidateMenuInput(1, 2);
    return (choice == 1);
}

void
getPair(string20 tempLanguage, string20 tempTranslation, char* characterAfterLanguage, char* characterAfterTranslation)
{
	
	printf("Enter language: ");
	fgets(tempLanguage, 21, stdin);
    if (strlen(tempLanguage) == 20)
    {
        *characterAfterLanguage = getc(stdin);
    }
    fflush(stdin);
	
	printf("Enter translation: ");
	fgets(tempTranslation, 21, stdin);
    if (strlen(tempTranslation) == 20)
    {
        *characterAfterTranslation = getc(stdin);
    }
    fflush(stdin);	
}

bool 
isLanguageTranslationPairValid(string20 tempLanguage, string20 tempTranslation, char characterAfterLanguage, char characterAfterTranslation)
{
    bool isValid = true;
    if (characterAfterLanguage != '\n' || characterAfterTranslation != '\n' || strlen(tempLanguage) == 0 || strlen(tempTranslation) == 0)
    {
        printf(REDFORMATSTRING, "Input(s) invalid. Try again.\n");
        isValid = false;
    }
    return isValid;
}

void 
formatLanguage(string20 language)
{
    int i;
    int lengthOfLanguage = strlen(language);
    if (lengthOfLanguage < 20)
    {
        language[lengthOfLanguage - 1] = '\0';
        lengthOfLanguage--;
    }
    
    language[0] = toupper(language[0]);
    for (i = 1; i < lengthOfLanguage; i++)
    {
        language[i] = tolower(language[i]);
    }
}

void 
formatTranslation(string20 translation)
{
    int i;
    int lengthOfTranslation = strlen(translation);
    if (lengthOfTranslation < 20)
    {
        translation[lengthOfTranslation - 1] = '\0';
        lengthOfTranslation--;   
    }
    for (i = 0; i < lengthOfTranslation; i++)
    {
        translation[i] = tolower(translation[i]);
    }

}

void 
addLanguageTranslationPair(entry* e)
{
    string20 tempLanguage;
    string20 tempTranslation;
    int addAnotherPair;
    char characterAfterLanguage = '\n';
    char characterAfterTranslation = '\n';
    bool isSavedConfirmed;
    
        do 
        {
            getPair(tempLanguage, tempTranslation, &characterAfterLanguage, &characterAfterTranslation);
            formatLanguage(tempLanguage);
            formatTranslation(tempTranslation);
            
        } while (!isLanguageTranslationPairValid(tempLanguage, tempTranslation, 
                              characterAfterLanguage, characterAfterTranslation));
        
        
        printf("\n");
        if (searchForLanguageTranslationPair(*e, tempLanguage, tempTranslation) == -1)
        {
            printf("Would you like to save change(s)?\n");
            if (e->pairCount == 0)
            {
                printf("\t- create new entry");
            } 
            printf("\t- Add translation: %s (%s)\n");
            
            if (isOperationConfirmed())        
            {
                strcpy(e->pairs[e->pairCount].language, tempLanguage);
                strcpy(e->pairs[e->pairCount].translation, tempTranslation);
                e->pairCount++;
                printf(GREENFORMATSTRING, "Changes saved\n");
            }
            else
            {
                printf(YELLOWFORMATSTRING, "Changes cancelled\n");
            }
        }

        else
        {
            printf(YELLOWFORMATSTRING, "The language-translation pair entered already exists in the entry\n");
        }


}

void
addEntry(entry* e)
{ 
    bool addAnotherPair;
    e->pairCount = 0;
    
    do
    {
        addLanguageTranslationPair(e);
    
        if (e->pairCount < MAXPAIRSPERENTRY)
        {
            printf("Would you like to add another pair?\n");
            addAnotherPair = isOperationConfirmed();
        }
    } while (addAnotherPair && e->pairCount < MAXPAIRSPERENTRY);

    if (e->pairCount == MAXPAIRSPERENTRY)
    {
        printf("The maximum of 10 translations per entry has been reached\n");
        printf("Press any key to return to Manage Data menu\n");
        getch();
        fflush(stdin);
    }
}

int 
findIndexsWhereSourceIsFound(entry entries[], string20 sourceLanguage, string20 wordToTranslate, int indexesWhereEntriesAreFound[])
{
    int numberOfEntriesWhereSourceIsFound = 0;
    int i;

    for (i = 0; i < MAXENTRIES; i++)
    {
        if (searchForLanguageTranslationPair(entries[i], sourceLanguage, wordToTranslate) != -1)
        {
            indexesWhereEntriesAreFound[numberOfEntriesWhereSourceIsFound] = i;
            numberOfEntriesWhereSourceIsFound++;
        }
    }
    return numberOfEntriesWhereSourceIsFound;
}

void 
addLanguageTranslationPairToExistingEntry(entry entries[], int numberOfEntries)
{   
    string20 sourceLanguage;
    string20 wordToTranslate;
    int indexesOfEntriesWhereWordIsFound[MAXENTRIES];
    int numberOfEntriesWhereSourceIsFound;
    char characterAfterLanguage = '\n';
    char characterAfterTranslation = '\n';
    int indexOfEntryToModify;
    int i;

    printf("Enter the language to translate from and the word you want to translate\n");
    
    do
    {
        initString(sourceLanguage);
        initString(wordToTranslate);
            
        getPair(sourceLanguage, wordToTranslate, &characterAfterLanguage, &characterAfterTranslation);

    } while (!isLanguageTranslationPairValid(sourceLanguage, wordToTranslate, characterAfterLanguage, characterAfterTranslation));

    numberOfEntriesWhereSourceIsFound =  findIndexsWhereSourceIsFound(entries, sourceLanguage, wordToTranslate, indexesOfEntriesWhereWordIsFound);

    printf("Enter the number corresponding to the entry you want to add a translation to\n");
    indexOfEntryToModify = indexesOfEntriesWhereWordIsFound[getAndValidateMenuInput(1, numberOfEntriesWhereSourceIsFound) - 1];
    printf("\n");
    printf("Enter the language-translation pair to be added\n");
    addLanguageTranslationPair(&entries[indexOfEntryToModify]);
}

void 
sortEntryAlphabeticallyByLanguage(entry* e)
{
    int i; 
    int j;
    languageTranslationPair temp;

    for (i = 0; i < e->pairCount - 1; i++)
    {
        for (j = 0; j < e->pairCount - 1 - i; j++)
        {
            if (strcmp(e->pairs[j].language,  e->pairs[j + 1].language) == 1)
            {
                temp = e->pairs[j];
                e->pairs[j] = e->pairs[j + 1];
                e->pairs[j + 1] = temp;
            }
        }
    }

}

int 
searchForLanguageTranslationPair(entry e, string20 languageKey, string20 translationKey)
{
    int i;
    int indexOfKey = -1;
    int startIndex = 0;
    int endIndex = e.pairCount - 1;

    while (strcmp(languageKey, e.pairs[startIndex].language) == 1 && startIndex < e.pairCount) 
    {
        startIndex++;
    }

    while (strcmp(languageKey, e.pairs[endIndex].language) == -1 && endIndex > startIndex)
    {
        endIndex--;
    }
    
    for (i = startIndex; i <= endIndex && indexOfKey == -1; i++)
    {
        if((strcmp(languageKey, e.pairs[i].language) == 0) && (strcmp(translationKey, e.pairs[i].translation) == 0))
        {
            indexOfKey = i;
        }
    }

    return indexOfKey;
}

void 
printEntriesToFile(entry entries[], int numberOfEntries, FILE* filename)
{
    int i;
    int j;

    for (i = 0; i < numberOfEntries; i++)
    {
        for (j = 0; j < entries[i].pairCount; j++)
        {
            fprintf(filename, "%s: %s\n", entries[i].pairs[j].language, entries[i].pairs[j].translation);
        }
        fprintf(filename, "\n");
    }
}

void
formatFilename(string30 filename)
{   
    int lengthOfString = strlen(filename);
    
    if (lengthOfString < 30)
    {
        filename[lengthOfString - 1] = '\0';
    }
}

bool
isThereProhibitedCharacterInFilename(string30 filename)
{
    bool isThereProhibitedCharacter = false;
    char prohibitedCharacters[9] = {'<', '>', ':', '"', '/', '\\', '|', '?', '*'};
    int i;
    int j;

    for (i = 0; i < strlen(filename) && !isThereProhibitedCharacter; i++)
    {
        for (j = 0; j < 9 && !isThereProhibitedCharacter; j++)
        {
            if (filename[i] == prohibitedCharacters[j])
            {
                isThereProhibitedCharacter = true;
            }
        }
    }
    return isThereProhibitedCharacter;
}

bool
isFilenameValid(string30 filename, char characterAfterFilename)
{
    bool isValid = true;
    if (strlen(filename) == 0)
    {
        printf(REDFORMATSTRING, "No filename was entered\n");
        isValid = false;
    }
    else if (characterAfterFilename != '\n')
    {
        printf(REDFORMATSTRING, "File name entered contains more than 30 characters\n");
        isValid = false;
    }
    else if (isThereProhibitedCharacterInFilename(filename))
    {
        printf(REDFORMATSTRING, "Filename entered contains prohibited character(s)\n");
        isValid = false;
    }
    else if (strcmp(filename, ".txt") == 0) 
    {
        printf(REDFORMATSTRING, "There must be at least one character before the \".txt\" extension\n");
        isValid = false;
    }
    else if (strcmp((filename + strlen(filename) - 4), ".txt") != 0)
    {
        printf(REDFORMATSTRING, "Filename must end in \".txt\"\n");
        isValid = false;
    }
    
    return isValid;
}

void 
getFilename(string30 filename, char* characterAfterFilename)
{
    printf("Enter filename: ");
    fgets(filename, 31, stdin); 
    if (strlen(filename) == 30)
    {
        *characterAfterFilename = getc(stdin);
    }
    fflush(stdin);
}

void exportData(entry entries[], int numberOfEntries)
{
    FILE* exportFile;
    string30 filename;
    char characterAfterFilename;

    printf("Provide filename of file where data will be exported to\n");
    printf(" - the file name must end in \".txt\"\n");
    printf(" - There must be at least 1 character before the \".txt\" extension\n");
    printf(" - the file name must not exceed 30 characters (including file extension)\n");
    printf(" - The following characters are not allowed to be used in the file name:\n");
    
    printf("\n");
    printf("   - < (less than)\n");
    printf("   - > (greater than)\n");
    printf("   - : (colon)\n");
    printf("   - \" (double quote)\n");
    printf("   - ' (single quote)\n");
    printf("   - \\ (forward slash)\n");
    printf("   - / (back slash)\n");
    printf("   - | (vertical bar)\n");
    printf("   - ? (question mark)\n");
    printf("   - * (asterisk)\n");
    

    printf("\n");
    do
    {
        characterAfterFilename = '\n';
        initString(filename);
        getFilename(filename, &characterAfterFilename);
        formatFilename(filename);
    } while (!isFilenameValid(filename, characterAfterFilename));

    printf("\n");
    printf("Would you like to proceed with export?\n");

    if (isOperationConfirmed())
    {
        exportFile = fopen(filename, "w");
        printEntriesToFile(entries, numberOfEntries, exportFile);
        fclose(exportFile);
        printf(GREENFORMATSTRING, "Data successfully exported to ");
        printf(GREENFORMATSTRING, filename);
        printf("\n");
    }
    else
    {
        printf(YELLOWFORMATSTRING, "Export cancelled\n");
    }
    
}

bool
isImportFilenameValid(string30 filename, char characterAfterFilename, FILE* importFile)
{
    bool isValid = true;
    if (strlen(filename) == 0)
    {
        printf(REDFORMATSTRING, "No filename was entered. Try again\n");
        isValid = false;
    }
    else if (characterAfterFilename != '\n')
    {
        printf(REDFORMATSTRING, "File name entered contains more than 30 characters. Try again\n");
        isValid = false;
    }
    else if (isThereProhibitedCharacterInFilename(filename))
    {
        printf(REDFORMATSTRING, "File name entered is not valid. Try again\n");
        isValid = false;
    }
    else if (strcmp(filename, ".txt") == 0) 
    {
        printf(REDFORMATSTRING, "File name entered is not valid. Try again\n");
        isValid = false;
    }
    else if (strcmp((filename + strlen(filename) - 4), ".txt") != 0)
    {
        printf(REDFORMATSTRING, "\".txt\" extension was not included in input. Try again\n");
        isValid = false;
    }
    else if (importFile == NULL)
    {
        printf(REDFORMATSTRING, "File not found. Try again\n");
        isValid = false;   
    }
    
    return isValid;
}

void
importData()
{
    FILE* importFile;
    string30 filename;
    char characterAfterFilename;
    printf("provide the file name of the text file (.txt) to import from\n");
    printf(" - include the \".txt\" file extension in input\n");
    printf(" - file name should not exceed 30 characters (including file extesion)\n");
    printf("\n");
   
    do
    {
        initString(filename);
        characterAfterFilename = '\n';
        printf("Enter file name: ");
        getFilename(filename, &characterAfterFilename);
        formatFilename(filename);
        importFile = fopen(filename, "r");
    } while (!isImportFilenameValid(filename, characterAfterFilename, importFile));
    printf("\n");
    
    printf("Would you like to proceed with import\n");
    if (isOperationConfirmed())
    {

    }
    else 
    {
        fclose(importFile);
        printf(YELLOWFORMATSTRING, "import cancelled\n");
        printf("Press any key to return to manage data menu\n");
        getch();
        fflush(stdin);
    }
    
}

// TASK 3: Delete entry

/* PSUEDOCODE:

    - display all entries along with indexes
    - ask user for the number corresponding to the entry to be deleted
    - validate input (input is from 1 - 10 and chosen entry is intialize)

    if input out of range:
     - display error message
     - ask for input until valid or proccess has been aborted

   else if chosen entry not initialized
        - ask user if deletion will still be executed
            if yes: execute
            
            else:
                - ask for input until valid or proccess has been aborted

    - ask user to confirm deletion 
        if confirmed
            - move structs "to the left"  to fill in empty pairs (using struct assignment)
            - clear last last struct
            - decrement entry count

        else: return to menu
    */

// FUNCTION 4: Delete translation 

/* PSUEDOCODE:
    - display all entries
    - ask user to select entry to delete from (int input)
    - validate input 
        if invalid:
            continue asking for input until valid or process is aborted
        
        if valid and not aborted
                - display translation to be deleted
                -  ask user to confirm
                - if confirmed: 
                    - delete translation
                    - decriment translation count
        
        
        - ask user if he would like to make another deletion in same entry or abort
        

*/

// FUNCTION 5: Display all entries

/* PSUEDOCODE:

    - sort translations (per entry) according to language alphabetically for display 
        (suggested implementation: make temp array containing indeces of language translation pairs and sort them accordingly)
    - display entries
    
    Need help with this part, don't understand:
        (If there is no English language 
        within an entry at the time of sorting, this entry can after all entries that have English and those 
        entries that do not have English need not be sorted anymore inter-entry. Meaning, let’s say, there 
        is an entry with only “Filipino” and “kape” as the language and translation pair, this entry is the 
        third  entry.]  Provide a  way  for  the  user  to  view  the next  or  previous  word  or exit the  view)

*/

// FUNCTION 6: Search word

/* PSUEDOCODE:
    - ask user for word to search
        if not found: 
        - display message
        - return to menu
        
        else:
        - display all entries where word is found 
        (SUGGESTION: also highlight word in entry using ANSI color)
        - ask input from user to return to menu
        

*/

// FUNCTION 7: Search translation

/* PSUEDOCODE:
    - ask user for language translation pair to search
        if not found: 
        - display message
        - return to menu
        
        else:
        - display all entries where pair is found 
        (SUGGESTION: also highlight word in entry using ANSI color)
        - ask input from user to return to menu
        

*/
