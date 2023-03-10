#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numAlloc = 0, numCard = 0, numBots = 0;
char *players[11];

typedef struct {
  int ativa;
  char num[3];
  char naipe[4];
} card;

card *hand;
card mesa;

void initHand() {
  hand = (card *)malloc(10 * sizeof(card));
  numAlloc = 10;
}

void insertInHand(char *newCard) {
  if (numCard == numAlloc) {
    numAlloc *= 2;
    hand = (card *)realloc(hand, numAlloc * sizeof(card));
  }
  int posNaipe = 1;
  if (newCard[0] == '1') {
    posNaipe = 2;
  }
  strcpy(hand[numCard].naipe, &newCard[posNaipe]);
  newCard[posNaipe] = 0;
  strcpy(hand[numCard].num, newCard);
  hand[numCard].ativa = 1;
  numCard++;
}

int main() {
  setbuf(stdin, NULL);   
  setbuf(stdout, NULL); 
  setbuf(stderr, NULL);

  char temp[100], meuId[10], temp2[100], handtemp[100], tabletemp[10], coringatemp[100], valetetemp[100], buytemp[10];
  char *pedaco, *carta;

  scanf("%*s %[^\n]", temp);

  pedaco = strtok(temp, " ");
  while (pedaco != NULL) {
    players[numBots] = strdup(pedaco);
    numBots++;
    pedaco = strtok(NULL, " ");
  }

  scanf("%*s %s", meuId);

  initHand();

  scanf("%*s [ %[^]] ]", handtemp);

  carta = strtok(handtemp, " ");
  while (carta != NULL) {
    insertInHand(carta);
    carta = strtok(NULL, " ");
  }

  scanf("%*s %s", tabletemp);

  int posNaipe = 1;
  if (tabletemp[0] == '1') {
    posNaipe = 2;
  }
  strcpy(mesa.naipe, &tabletemp[posNaipe]);
  tabletemp[posNaipe] = 0;
  strcpy(mesa.num, tabletemp);

  char turnId[10], acao[15], comp1[5], comp2[5], discard[8] = "DISCARD", buy[4]="BUY";

  while (1) {
    while (1) {
      scanf("%*s %s", turnId);
      if (strcmp(meuId, turnId) == 0) {
        break;
      }
      scanf("%s %s", acao, comp1);
      if (strcmp(acao, discard) == 0) {
        if (comp1[0] == 'A') {
          scanf("%s", comp2);
        }
        if (comp1[0] == 'C') {
          scanf("%s", comp2);
        }
        int posNaipe = 1;
        if (comp1[0] == '1') {
          posNaipe = 2;
        }
        strcpy(mesa.naipe, &comp1[posNaipe]);
        if (comp1[0] == 'A') {
          strcpy(mesa.naipe, comp2);
        }
        if (comp1[0] == 'C') {
          strcpy(mesa.naipe, comp2);
        }
        comp1[posNaipe] = 0;
        strcpy(mesa.num, comp1);
      }
    }
    
    char discard[32];
    if (mesa.num[0] == 'C' || mesa.num[0] == 'V' && strcmp(acao, "DISCARD")==0) {
      if (mesa.num[0] == 'C') {
        printf("BUY 4\n");
        for (int i = 0; i < 4; i++) {
          scanf("%s", coringatemp);
          insertInHand(coringatemp);
        }
      }
      else if (mesa.num[0] == 'V') {
        printf("BUY 2\n");
        for (int i = 0; i < 2; i++) {
          scanf("%s", valetetemp);
          insertInHand(valetetemp);
        }
      }
    } 
    else {
      int jaJoguei = 0;
      for (int k = 0; k < numCard; k++) {
        if (hand[k].ativa == 1) {
            if (strcmp(hand[k].naipe, mesa.naipe) == 0) {
              
              if (hand[k].num[0] == 'C' || hand[k].num[0] == 'A'){
                printf("DISCARD %s%s ♦\n", hand[k].num, hand[k].naipe);
                jaJoguei = 1;
                hand[k].ativa = 0;
                strcpy(mesa.num, hand[k].num);
                strcpy(mesa.naipe, hand[k].naipe);
                break;
              }
              
              else {
		        printf("DISCARD %s%s\n", hand[k].num, hand[k].naipe);
                jaJoguei = 1;
                hand[k].ativa = 0;
                strcpy(mesa.num, hand[k].num);
                strcpy(mesa.naipe, hand[k].naipe);
                break;
              }
            } 
            else if (strcmp(hand[k].num, mesa.num) == 0) {

              if (hand[k].num[0] == 'A' || hand[k].num[0] == 'C') {
		        printf("DISCARD %s%s ♦\n", hand[k].num, hand[k].naipe);
                jaJoguei = 1;
                hand[k].ativa = 0;
                strcpy(mesa.num, hand[k].num);
                strcpy(mesa.naipe, hand[k].naipe);
                break;
              } 
              
              else {
                printf("DISCARD %s%s\n", hand[k].num, hand[k].naipe);
                jaJoguei = 1;
                hand[k].ativa = 0;
                strcpy(mesa.num, hand[k].num);
                strcpy(mesa.naipe, hand[k].naipe);
                break;
              }
            } 
        }
      }
      
	    if (jaJoguei == 0) {
        for (int k = 0; k < numCard; k++) {
          if ((hand[k].num[0] == 'C' || hand[k].num[0] == 'A') && hand[k].ativa == 1) {
            printf("DISCARD %s%s ♦\n", hand[k].num, hand[k].naipe);
            strcpy(mesa.num, hand[k].num);
            strcpy(mesa.naipe, hand[k].naipe);
            jaJoguei = 1;
            hand[k].ativa =0;
            break;
          }
        }
      }
        if (jaJoguei==0) {
          printf("BUY 1\n");
          scanf("%s", buytemp);
          insertInHand(buytemp);
        }
    }
  }
  
  return 0;
}