
#include "ALMERO_MARQUEZ_MP.c"

int main()
{
    entry e;
    string20 languageKey = "English";
    string20 translationKey = "Hate";
    addEntry(&e);
    printf("%s %s\n", e.pairs[0].language, e.pairs[0].translation);
    printf("%s %s\n", e.pairs[1].language, e.pairs[1].translation);
    printf("%s %s\n", e.pairs[2].language, e.pairs[2].translation);
    printf("\n");
    sortEntryAlphabeticallyByLanguage(&e);
    printf("%s %s\n", e.pairs[0].language, e.pairs[0].translation);
    printf("%s %s\n", e.pairs[1].language, e.pairs[1].translation);
    printf("%s %s\n", e.pairs[2].language, e.pairs[2].translation);
   printf("%d\n",  searchForLanguageTranslationPair(e, languageKey, translationKey));
}