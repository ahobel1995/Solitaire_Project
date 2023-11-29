void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int* moveCount);
void cardMoveDrop(int play[19][7], int hidden[19][7], int cardPos[2], int dropDeck[4], int* moveCount);
void cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int dropDeck[4], int deck[53],
                  int* draw, int* moveCount);
void playerMoveDecision(int play[21][7], int hidden[19][7], int dropDeck[4], int deck[53],
                        int playerCardChoice[2], int playerMoveChoice[2], int* draw, int* game);
void deckPull(int play[21][7], int deck[53], int cardPos[2], int* draw, int hidden[21][7], int dropDeck[4],
              int deckPullChoice);
