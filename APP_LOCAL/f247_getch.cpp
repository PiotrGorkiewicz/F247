#ifndef __F247_GETCH_CPP__
#define __F247_GETCH_CPP__



#if __INCLUDE_LEVEL__ == 0
#include <termios.h>
#include <stdio.h>
#include <string.h>
static struct termios told, tnew;
#endif // if __INCLUDE_LEVEL__ == 0



char F247_GETCH_GetchWait(void)
#if __INCLUDE_LEVEL__ == 0
    {
    char c;
    if(tcgetattr(0, &told)<0)
        perror("tcgetattr()");
    memcpy(&tnew,&told,sizeof(tnew));
    tnew.c_lflag&=~ICANON;
    tnew.c_lflag&=~ECHO;
    tnew.c_cc[VMIN]=1;
    tnew.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &tnew)<0)
        perror("tcsetattr() [new]");
    c=getchar();
    if(tcsetattr(0, TCSANOW, &told)<0)
        perror("tcsetattr() [old]");
    return c;
    }
#else  // if __INCLUDE_LEVEL__ == 0
;
#endif // if __INCLUDE_LEVEL__ == 0










#if 0
static struct termios told, tnew;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &told); /* grab old terminal i/o settings */
  tnew = told; /* make new settings same as old settings */
  tnew.c_lflag &= ~ICANON; /* disable buffered i/o */
  tnew.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &tnew); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &told);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

/* Let's test it out */
int main(void) {
  char c;
  printf("(getche example) please type a letter: ");
  c = getche();
  printf("\nYou typed: %c\n", c);
  printf("(getch example) please type a letter...");
  c = getch();
  printf("\nYou typed: %c\n", c);
  return 0;
} 



#endif




#if 0

char getch(){
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios told={0};
    fflush(stdout);
    if(tcgetattr(0, &told)<0)
        perror("tcsetattr()");
    told.c_lflag&=~ICANON;
    told.c_lflag&=~ECHO;
    told.c_cc[VMIN]=1;
    told.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &told)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    told.c_lflag|=ICANON;
    told.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &told)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }

#endif



#endif /* __F247_GETCH_CPP__ */

