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