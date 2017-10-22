enum STATE{INIT,PRE,RULE,EXE,PLAYER_CARD1,PLAYER_CARD2,PLAYER_CARD3,PLAYER_CARD4,PLAYER_CARD5,COMPUTER_CARD1,COMPUTER_CARD2,COMPUTER_CARD3,COMPUTER_CARD4,COMPUTER_CARD5,GG,WIN,TIE,END};


STATE  state;

bool begin;
double highestpoint;
int money ;
int re_money;
int bet;
int A;
int B;
int player_point;
int computer_point;
int card1;
int card2;
int card3;
int card4;
int card5;
int point1;
int point2;
int point3;
int point4;
int point5;

int main(void);
int init(void);
int rule(void);
int pre(void);
int exe(void);
int gg(void);
int win(void);
int tie(void);
int end(void);
int card(void);
int pattern(void);
int point(void);
int player_card1(void);
int player_card2(void);
int player_card3(void);
int player_card4(void);
int player_card5(void);
int computer_card1(void);
int computer_card2(void);
int computer_card3(void);
int computer_card4(void);
int computer_card5(void);