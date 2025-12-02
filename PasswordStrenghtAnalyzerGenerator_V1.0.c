#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//define
#define ZERO 0
#define UNO 1
#define OTTO 8
#define DIECI 10
#define DODICI 12
#define QUINDICI 15
#define SEDICI 16
#define VENTI 20
#define M_MOLTO_DEBOLE 30 //macro molto debole
#define M_DEBOLE 50 //macro debole
#define M_MEDIO 70 //macro medio
#define M_FORTE 90 //macro forte
#define MAX_LUNGHEZZA_PASSWORD 15
#define GENERAZIONE_MIN 33
#define GENERAZIONE_MAX 126

//enum-struct
typedef enum{MOLTO_DEBOLE, DEBOLE, MEDIO, FORTE, MOLTO_FORTE} LivelloSicurezza;
typedef enum{ESCI, ANALIZZA, GENERA, MOSTRA_SUGGERIMENTI};

typedef struct {
    int lunghezza;
    int contieneMaiuscole;
    int contieneMinuscole;
    int contieneNumeri;
    int contieneSpeciali;
    int score;
    LivelloSicurezza livelloSicurezza;
} Analizzatore;

//inizializzazione funzioni
void menu();
Analizzatore passwordAnalyzer(char password[]);
void stampaRisultati(Analizzatore analisi);
void mostraSuggerimenti();
char *generatoreDiPassword(int dim);
void stampaPassword( char *password);

int main(void) {

    srand(time(NULL));

    //variabili
    int scelta;
    char password[MAX_LUNGHEZZA_PASSWORD + UNO];
    char *databasePasswordGenerate = NULL;
    int dim = MAX_LUNGHEZZA_PASSWORD;

    //stampa menu
    do {
        menu();
        printf("\nScelta: ");
        scanf("%d", &scelta);

        //switch che permette la scelta dell'opzione
        switch (scelta) {
            case ESCI:
                printf("Chiusura programma in corso\n");
                break;
            case ANALIZZA:
                printf("Scrivi una password\n");
                scanf("%s", password);

                //chiamo la funzione analizza
                stampaRisultati(passwordAnalyzer(password));
                break;
            case GENERA:

                databasePasswordGenerate = generatoreDiPassword( dim );
                stampaPassword(databasePasswordGenerate);

                free(databasePasswordGenerate);
                break;
            case MOSTRA_SUGGERIMENTI:
                mostraSuggerimenti();
                break;
            default:
                printf("Scelta non valida\n\n");
        }

    } while (scelta != ZERO);


    return 0;
}

//funzione stampa del menu
void menu() {
    printf("============================\n");
    printf(" PASSWORD SECURITY ANALYZER\n");
    printf("============================\n");
    printf("1) Analizza una password\n");
    printf("2) Genera una password sicura\n");
    printf("3) Mostra suggerimenti di sicurezza\n");
    printf("0) Esci\n");
}

//funzione calcolo sicurezza con sistema di punteggio
Analizzatore passwordAnalyzer(char password[]) {

    //variabili
    Analizzatore analisi;
    int i;

    //inizializzo tutta la struttura Analizzatore a 0
    analisi.lunghezza = ZERO;
    analisi.contieneMaiuscole = ZERO;
    analisi.contieneMinuscole = ZERO;
    analisi.contieneNumeri = ZERO;
    analisi.contieneSpeciali = ZERO;
    analisi.score = ZERO;
    analisi.livelloSicurezza = MOLTO_DEBOLE;

    analisi.lunghezza = strlen(password);

    //ciclo for che scorre l'array password e ritorna il valore 0 se non contenente, 1 se contenente
    for (i = ZERO; i < analisi.lunghezza; i++) {

        //verifica maiuscola
        if (password[i] >= 'A' && password[i] <= 'Z') {
            analisi.contieneMaiuscole = UNO;
        }

        //verifica minuscola
        if (password[i] >= 'a' && password[i] <= 'z') {
            analisi.contieneMinuscole = UNO;
        }

        //verifica contiene numero
        if (password[i] >= '0' && password[i] <= '9') {
            analisi.contieneNumeri = UNO;
        }

        //verifica contiene caratteri speciali
        if (!((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z') || (password[i] >= '0' && password[i] <= '9'))) {
            analisi.contieneSpeciali = UNO;
        }
    }

    //calcolo dello score
    if (analisi.lunghezza >= OTTO) {
        analisi.score += VENTI;
    };
    if (analisi.lunghezza >= DODICI) {
        analisi.score += DIECI;
    }
    if (analisi.lunghezza >= SEDICI) {
        analisi.score += DIECI;
    }
    if (analisi.contieneMaiuscole) {
        analisi.score += QUINDICI;
    }
    if (analisi.contieneMinuscole) {
        analisi.score += QUINDICI;
    }
    if (analisi.contieneNumeri) {
        analisi.score += QUINDICI;
    }
    if (analisi.contieneSpeciali) {
        analisi.score += QUINDICI;
    }

    //determinare risultato dello score
    if (analisi.score < M_MOLTO_DEBOLE) {
        analisi.livelloSicurezza = MOLTO_DEBOLE;
    }
    else if (analisi.score < M_DEBOLE) {
        analisi.livelloSicurezza = DEBOLE;
    }
    else if (analisi.score < M_MEDIO) {
        analisi.livelloSicurezza = MEDIO;
    }
    else if (analisi.score < M_FORTE) {
        analisi.livelloSicurezza = FORTE;
    }
    else {
        analisi.livelloSicurezza = MOLTO_FORTE;
    }

    return analisi;
}

//funzione della stampa risultati
void stampaRisultati(Analizzatore analisi) {
    //variabili

    //stampe
    printf("\n>RISULTATI:\n");
    // Stampa la lunghezza
    printf("Lunghezza: %d caratteri\n", analisi.lunghezza);

    // Stampa se ha maiuscole
    if (analisi.contieneMaiuscole == UNO) {
        printf("Maiuscole: SI\n");
    } else {
        printf("Maiuscole: NO\n");
    }

    // Stampa se ha minuscole
    if (analisi.contieneMinuscole == UNO) {
        printf("Minuscole: SI\n");
    } else {
        printf("Minuscole: NO\n");
    }

    // Stampa se ha numeri
    if (analisi.contieneNumeri == UNO) {
        printf("Numeri: SI\n");
    } else {
        printf("Numeri: NO\n");
    }

    // Stampa se ha caratteri speciali
    if (analisi.contieneSpeciali == UNO) {
        printf("Caratteri speciali: SI\n");
    } else {
        printf("Caratteri speciali: NO\n");
    }

    // Stampa lo score
    printf("\nScore: %d/100\n", analisi.score);

    // Stampa il livello
    printf("Livello: ");
    if (analisi.livelloSicurezza == MOLTO_DEBOLE) {
        printf("MOLTO DEBOLE\n\n");
    } else if (analisi.livelloSicurezza == DEBOLE) {
        printf("DEBOLE\n\n");
    } else if (analisi.livelloSicurezza == MEDIO) {
        printf("MEDIO\n\n");
    } else if (analisi.livelloSicurezza == FORTE) {
        printf("FORTE\n\n");
    } else {
        printf("MOLTO FORTE\n\n");
    }
}

//funzione mostra suggerimenti
void mostraSuggerimenti() {
    printf("\n--- SUGGERIMENTI DI SICUREZZA ---\n");
    printf("- Usa almeno 12 caratteri\n");
    printf("- Combina maiuscole, minuscole, numeri e simboli\n");
    printf("- Evita parole comuni o date di nascita\n");
    printf("- Non riutilizzare la stessa password\n");
    printf("- Cambia password regolarmente\n\n");
}

//funzione di generazione di password forte casuale
char *generatoreDiPassword(int dim) {
    char *stringa = (char*)malloc((dim + UNO) * sizeof(char)); // +1 per '\0'

    if (stringa == NULL) {
        printf("Generazione non portata a termine\n");
        exit(EXIT_FAILURE);
    }

    // Insieme di caratteri validi per la password
    const char caratteri[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
    int num_caratteri = strlen(caratteri);

    for (int i = ZERO; i < dim; i++) {
        stringa[i] = caratteri[rand() % num_caratteri];
    }

    stringa[dim] = '\0'; // Terminatore nullo

    return stringa;
}

//stampa password generata
void stampaPassword( char *password) {

    int lunghezza = strlen(password);

    // Stampa completa
    printf("Password generata: %s\n", password);
    printf("Ora provala sull'analizzatore\n\n");
}
