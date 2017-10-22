enum STATE{INIT,PRE,RULE,EXE,ANSWER,GG,WIN,TIE,END};


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
int answer(void);
int gg(void);
int win(void);
int tie(void);
int end(void);
int card(void);
int pattern(void);
int point(void);
