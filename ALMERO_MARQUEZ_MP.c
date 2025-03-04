#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// CODING CONVENTIONS 
/*
    - put space between tokens (e.g. x = 1, NOT x=1)
    - pointer data types will be written as: char*, int*; NOT char *, int *
    - follow normal CCPORG2 code block format
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

bool getInteger(int* num)
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

// TASK 1: Add entry 

/* TODO:
    - ask user for input
    - check if pair already exists
      
    (Suggested implementation: 
        - create function that will format the entered string for simplicity of comparison
        - the existing entry must also be formatted)



        if pair exists: show information then ask if he would like to make new entry
            if make entry: ask for input
            else: go back to menu

        else:
        - validate input:
        
            If valid:
                -  ask user to confirm
                - if confirmed: make new entry
                - else: ask user if he would like to make another input or abort
            else:
                - display error message
                -  ask user if he would like to make another input or abort

                if abort: go back to menu
                else: ask for input
*/

// TASK 2: Add translation

/* TODO:
    - ask user for language translation pair 
        if pair already exists 
            if pair exists in more than 1 entry
                - ask where new language translation pair will be added (int input)
        
        if language translation pair count < 10:
            - get new language translation pair
            - validate input

                    If valid:
                        -  ask user to confirm
                        - if confirmed: add translation
                        - else: ask user if he would like to make another input or abort
                    else:
                        - display error message
                        -  ask user if he would like to make another input or abort
                
                        if abort: 
                            - ask user if he would like add another translation to same entry
                            if add: ask for input 
                            else: return to menu

                
                else if translation already exists for specified language:
                    - ask user if he would like to replace existing translation

                    if replace: replace translation

                else: 
                     - incrament pair count
                     - ask user if he would like add another translation to same entry
                        if add: ask for input 
                        else: return to menu



        else:
            - display error message (and recommendation to delete translation pair)
            - return to menu

       
*/

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

// FUNCTION 6: Search translation

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
