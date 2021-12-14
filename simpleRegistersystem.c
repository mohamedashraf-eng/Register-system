/*
  * Author: Mohamed Ashraf (Wx).
  * Date: 4/5/2021
  * Code: Training on simple register system.
*/
//=================================================================
#include "Wx_Encryption_H.h"

// DEFINES:
#define ENTER 13
#define BKSP   8
#define ESC   27
#define SPC    32
#define TAB   9
#define DEL   127

// FUNCTIONS DEC:
void wx_GETNAME(char *);
void wx_PASSWORD(char *);
uint32_t FILTER_INPUT_DEC(uint32_t);

// Structs:
#define MAXDATA 255
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 15

#pragma pack(1)
typedef struct
{
  char name[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];

} DATA; DATA data[MAXDATA];

uint8_t _passwordcounter = 0;
uint8_t _namecounter = 0;

int main(void)
{
  system("COLOR 0a");
  int32_t  ENTER_TEMP = 0;
  int32_t  SEE_TEMP   = 0;
  uint32_t SWITCH     = 0;

  static uint8_t D_COUNTER  = 0;
  uint8_t D_COUNTERC = 0;
  //uint8_t D_COUNTERT        = 0;
  uint32_t TEMPSTACK[5] = {0};

  while((char)SWITCH != -1)
  {
    system("cls");

    printf("\n How can I surve you?");
    printf("\n [ 1 ]: Enter data?\n [ 2 ]: See data?");
    printf("\n [ 3 ]: Save & Exit?");
    printf("\n [ > ]: ");
    scanf("%d", &SWITCH);
    uint8_t SCANNED_INPUT = FILTER_INPUT_DEC(SWITCH);
    // Loop for data entering:
    switch(SCANNED_INPUT)
    {
      case 1: system("cls");
            {
              printf("\n ENTERING NEW DATA.\n");
              while(1)
              {

                system("cls");
                printf("\n Add user?('1' for \"yes\", '-1' for \"NO\")\n");
                printf(" [ > ]: ");
                scanf("%d", &ENTER_TEMP);
                if(ENTER_TEMP == -1) {break;}
                else if(ENTER_TEMP == 1)
                {
                   _passwordcounter = 0;
                   _namecounter = 0;

                  wx_GETNAME(data[D_COUNTER].name);
                  wx_PASSWORD(data[D_COUNTER].password);
                  D_COUNTER++;
                }
                else
                {
                  printf("\n Please Enter valid input! & Try again\n");
                  break;
                }//end else

                printf("\n Data entered! successfully\n");
              }//end while 1
              break;
            }// end case:1

      // SEE_DATA-Label for controlled_jump_statement.
      SEE_DATA:
      case 2: system("cls");
            {
              D_COUNTERC = 0; // To view the data from [0,n] ->
              printf("\n TOTAL DATA STORED [ %d ]. \n",D_COUNTER);
              while(1)
              {
                while(D_COUNTERC < D_COUNTER)
                {
                  printf("\n [ %d ]> Username(%d): %s",D_COUNTERC,
                                    (_namecounter),
                                    data[D_COUNTERC].name);
                  printf("\n [ %d ]> Password(%d): %s\n", D_COUNTERC,
                                    (_passwordcounter),
                                    data[D_COUNTERC].password);
                  D_COUNTERC++;
                  printf("--------------------------------------\n");
                }
                // User_Options:
                printf("\n [ 1 ]: Edit?\n [ 2 ]: See Data?");
                printf("\n [ 3 ]: Exit?");
                printf("\n [ > ]: ");
                scanf("%d", &SEE_TEMP);

                // Detect Input_Inject:
                uint8_t SCANNED_SEE_TEMP = FILTER_INPUT_DEC(SEE_TEMP);
                if(SCANNED_SEE_TEMP == 3) {break;}

                // Input_Passed:
                switch(SCANNED_SEE_TEMP)
                {
                  // DATA EDITING: CASE-1
                  case 1: system("cls");
                        {
                          printf("\n What ID do you want to edit?\n");
                          printf("\n [ > ]: ");
                          scanf("%d", &TEMPSTACK[0]);

                          // ERRO_ID_DETECTOR:
                          bool ID_CHECKER = false;
                          for(uint8_t i = 0; i < D_COUNTERC; i++)
                          {
                            if(TEMPSTACK[0] == i)
                            {
                              ID_CHECKER = true;
                            }
                            else
                            {
                              ID_CHECKER = false;
                            }
                          }
                          // Entered ID passed:
                          if(ID_CHECKER)
                          {
                            printf("\n What editing operation do you want?\n");
                            printf("\n [ 1 ]: Remove?\n [ 2 ]: Change Name?");
                            printf("\n [ 3 ]: Change Password?");
                            printf("\n [ 4 ]: Both 2 & 3?\n [ 5 ]: Exit?");
                            printf("\n [ > ]: ");

                            uint32_t SWITCH2 = 0;
                            scanf("%d", &SWITCH2);
                            uint8_t TEMPSCANNED2 = FILTER_INPUT_DEC(SWITCH2);
                            if(TEMPSCANNED2 == 5) {break;}

                            switch(TEMPSCANNED2)
                            {
                              // Removing Proccess:
                              case 1: system("cls");
                                    {
                                      //data[TEMPSTACK[0]].name = 0
                                      //data[TEMPSTACK[0]].password = 0;
                                      break;
                                    }//end case:1.
                              // Change name proccess:
                              case 2: system("cls");
                                    {
                                     _namecounter = 0;
                                     printf("\n ID[%d]: New name. \n", TEMPSTACK[0]);
                                     wx_GETNAME(data[TEMPSTACK[0]].name);
                                     printf("\n Data Changed successfully!\n");
                                     break;
                                    }
                              // Change password proccess:
                              case 3: system("cls");
                                    {
                                     _passwordcounter = 0;
                                     printf("\n ID[%d]: New password. \n", TEMPSTACK[0]);
                                     wx_PASSWORD(data[TEMPSTACK[0]].password);
                                     printf("\n Data Changed successfully!\n");
                                     break;
                                    }
                              // Change Name & Password proccess:
                              case 4: system("cls");
                                    {
                                      _namecounter = 0;
                                     _passwordcounter = 0;
                                     printf("\n ID[%d]: New name.", TEMPSTACK[0]);
                                     wx_GETNAME(data[TEMPSTACK[0]].name);

                                     printf("\n");

                                     printf("\n ID[%d]: New password.", TEMPSTACK[0]);
                                     wx_PASSWORD(data[TEMPSTACK[0]].password);

                                     printf("\n Data Changed successfully!\n");
                                     break;
                                    }
                              default: {break;}
                            }
                          }//end if(ID_CHECKER).
                          else
                          {
                            printf("\n ID Not Found! Try again.\n");
                            break;
                          }
                          break;
                        }//end case:1.

                  // SEE DATA: CASE-2
                  case 2: system("cls");
                        {
                          // Conditional_Jump_Instruction
                          goto SEE_DATA;
                          break;
                        }//end case:2.

                  default:
                        {
                          break;
                        }//end default.
                    break;
                }//end switch 2
              }//end while.
              break;
            } // end case:2
      case 3: system("cls");
            {
              printf("\n Saved!, Have a nice day!\n");
              exit(0);
              break;
            }
      default: system("cls");
            {
              printf("\n ERROR:STATE:WRONG_INPUT<Lx1,SW>\n");
              break;
            }
    }// end switch.
  }// end big while.

  printf("\n");
  return 0;
}

void wx_GETNAME(char *nptr)
{
  char temp;

  printf("\n Username: ");
  while(_namecounter < MAX_USERNAME_LENGTH)
  {
    temp = getch();
    // If user pressed "ENTER button":
    if(temp == ENTER)
    {
      nptr[_namecounter] = '\0';
      break;
    }
    // If user pressed "Backspace button":
    else if(temp == BKSP)
    {
      // ALready user typed a thing to delete:
      if(_namecounter > 0)
      {
        _namecounter--;
        nptr[_namecounter] = '\0';
        printf("\b \b");
      }
    }
    // If user pressed "SPACE/TAB/ESC/DEL button":
    else if(temp == TAB || temp == ESC)
    {
      continue;
    }
    else if(temp == SPC)
    {
      printf(" ");
      nptr[_namecounter] = SPC;
      _namecounter++;
    }
    else if(temp == DEL)
    {
      break;
    }
    else
    {
      printf("%c", temp);
      nptr[_namecounter] = temp;
      _namecounter++;
    }
  }// end while.
}

void wx_PASSWORD(char *pptr)
{
  char temp;

  printf("\n Password(MAX LENGTH: 15): ");
  while(_passwordcounter <= MAX_PASSWORD_LENGTH)
  {
    temp = getch();
    // If user pressed "ENTER button":
    if(temp == ENTER)
    {
      pptr[_passwordcounter] = '\0';
      break;
    }
    // If user pressed "Backspace button":
    else if(temp == BKSP)
    {
      // ALready user typed a thing to delete:
      if(_passwordcounter > 0)
      {
        _passwordcounter--;
        pptr[_passwordcounter] = '\0';
        printf("\b \b");
      }
    }
    // If user pressed "SPACE/TAB/ESC/DEL button":
    else if(temp == TAB || temp == ESC)
    {
      continue;
    }
    else if(temp == SPC)
    {
      printf(" ");
      pptr[_passwordcounter] = SPC;
      _passwordcounter++;
    }
    else if(temp == DEL)
    {
      break;
    }
    else
    {
      printf("*");
      pptr[_passwordcounter] = temp;
      _passwordcounter++;
    }
  }
}

#define UPPERCHARA 65
#define UPPERCHARZ 90
#define LOWERCHARA 97
#define LOWERCHARZ 122

uint32_t FILTER_INPUT_DEC(uint32_t INPUT)
{
  uint32_t SCANNED_INPUT = 0;
  const uint8_t LIMIT[2] = {1, 9};

  if( ((INPUT) >= LIMIT[0]) && ((INPUT) <= LIMIT[1]) )
  {
    (SCANNED_INPUT) = (INPUT);
    return (SCANNED_INPUT);
  }
  else if( ((INPUT) >= UPPERCHARA && (INPUT) <= UPPERCHARZ) ||
           ((INPUT) >= LOWERCHARA && (INPUT) <= LOWERCHARZ))
  {
    (SCANNED_INPUT) = '\0';
    return (SCANNED_INPUT);
  }
  return 0;
}
