#include "checkers.h"

//************This file contains definition of all functions************

int playerTurn;

void initBoard(checkersGrid Board[][SIZE])
{
    //Create empty board
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            Board[i][j].state = EMPTY;
            (Board[i][j].checkers).colour = NOCOLOUR;
            (Board[i][j].checkers).type = NOPEICE;
        }
    }

    //place the inital pieces

    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < SIZE; j = j + 2)
        {
            if (i == 1)
            {
                Board[i][j].state = FULL;
                (Board[i][j].checkers).colour = RED;
                (Board[i][j].checkers).type = NORMAL; //initially all peices are normal

                Board[SIZE - 1 - i][j + 1].state = FULL;
                (Board[SIZE - 1 - i][j + 1].checkers).colour = BLUE;
                (Board[SIZE - 1 - i][j + 1].checkers).type = NORMAL;
            }
            else
            {
                Board[i][j + 1].state = FULL;
                (Board[i][j + 1].checkers).colour = RED;
                (Board[i][j + 1].checkers).type = NORMAL;

                Board[SIZE - 1 - i][j].state = FULL;
                (Board[SIZE - 1 - i][j].checkers).colour = BLUE;
                (Board[SIZE - 1 - i][j].checkers).type = NORMAL;
            }
        }
    }
}

void printBoard(checkersGrid Board[][SIZE])
{

    for (int i = 0; i < SIZE; i++)
    {
        printf("              ");

        for (int k = 0; k < SIZE + 1; k++)
        {
            if (k == 0)
                printf("   ");
            else
                printf("----");
        }
        printf("-");

        if (i == 1)
            printf("   Enter:\n");
        else if (i == 2)
            printf("   0 to exit\n");
        else if (i == 3)
            printf("   1 to a input\n");
        else if(i == 4){
            printf("   2 to propose a draw\n");
        }
        else
            printf("\n");

        printf("              ");

        printf("%d  |", i + 1);
        for (int j = 0; j < SIZE; j++) //print all peices in their current state
        {
            if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == RED))
            {
                if ((Board[i][j].checkers).type == KING)
                    printf("\033[31m X*"); //king will be denoted with an asterix next to it
                else
                    printf("\033[31m X ");
                printf("\033[0m|");
            }
            else if ((Board[i][j].state == FULL) && ((Board[i][j].checkers).colour == BLUE))
            {
                if ((Board[i][j].checkers).type == KING)
                    printf("\033[36m O*");
                else
                    printf("\033[36m O ");
                printf("\033[0m|");
            }
            else
            {
                printf("   |");
            }
        }
        printf("\n");
    }
    printf("                ");

    for (int k = 0; k < SIZE + 1; k++)
    {
        if (k == 0)
            printf(" ");
        else
            printf("----");
    }
    printf("              ");

    printf("\n");
    printf("   ");
    printf("              ");

    for (int i = 0; i < SIZE; i++)
    {
        printf("  %c ", 'A' + i);
    }
    printf("\n");
}

// this check if double capture moves are possible
bool ifdouble(checkersGrid Board[][SIZE], coordinates a, char turn)
{
    int x = a.x;
    char y = a.y + 'A';
    // calls is valid to check if capture is valid
    int variable = isvalid(Board, turn, y, x, y + 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x - 2) + isvalid(Board, turn, y, x, y + 2, x - 2);
    return variable > 0;
}

char switchTurn(char turn)
{
    if (turn == 'X')
    {
        // Player- O turn
        playerTurn = 2;
        turn = 'O';
    }
    else
    { // Player- X turn
        playerTurn = 1;
        turn = 'X';
    }
    return turn;
}

int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d)
{
    int m;
    if (P == 'O')
    {
        m = 0;
    }
    // here m represents the player O or X

    // m=0(player-O) and m=1(player-X)
    if (P == 'X')
    {
        m = 1;
    }

    int a, c;
    a = M - 65;
    c = N - 65;

    b = b - 1;
    d = d - 1; // to have index from 0 t0 7 instead of 1 to 8
               // here a,b are coordinates of initial position and c,d are coordinates of final position

    int g, h;
    if (a < 0 || b < 0 || c < 0 || d < 0) // if they are not valid coordinates
    {
        return 0;
    }
    if (a > 7 || b > 7 || c > 7 || d > 7) // if coordinates are out of bounds function returns 0
    {
        return 0;
    }

    g = c - a > 0 ? c - a : a - c;
    h = d - b > 0 ? d - b : b - d;

    if (g != h || g > 2 || h > 2) // if difference between the x-coordinates not equal to difference between y-coordinates or if they are greater than 2 function returns 0
        return 0;

    // checks whether  peice is present at coordinates (a,b)  and no piece is present at coordinates (c,d)
    if ((Board[b][a]).state == EMPTY || (Board[d][c]).state != EMPTY)
    {
        return 0;
    }

    if (m == 0) // for player-O(BLUE)
    {
        if ((Board[b][a].checkers).type == NORMAL) // if the piece is normal
        {
            if ((Board[b][a].checkers).colour == RED) // if that position contains another player's piece
                return 0;

            if (d == b + 1 || d == b + 2) // it can move only forward cannot move backward
            {
                return 0;
            }
            if (d == b - 2)
            {
                if (c == a - 2) // if the difference is greater than 2 checks whether diagnolly middle position contains opposite colour or not
                {
                    if ((Board[b - 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {

                    if ((Board[b - 1][a + 1].checkers).colour == BLUE || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }
        }

        if ((Board[b][a].checkers).type == KING)
        {
            if ((Board[b][a].checkers).colour == RED) // if that position contains another player's piece
                return 0;
            if (d == b - 2) // as it is a king it can move diagnolly backward or forward
            {
                if (c == a - 2) // checks whether the middle piece is of opposite colour or not
                {
                    if ((Board[b - 1][a - 1].checkers).colour == BLUE || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)

                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b - 1][a + 1].checkers).colour == BLUE || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }

            if (d == b + 2)
            {
                if (c == a - 2)
                {

                    if ((Board[b + 1][a - 1].checkers).colour == BLUE || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == BLUE || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)

                        return 0;
                }
            }
        }
    }

    if (m == 1) //for player-X(RED)
    {
        if ((Board[b][a].checkers).type == NORMAL)
        {
            if ((Board[b][a].checkers).colour == BLUE) // if that position contains another player's piece
                return 0;

            if (d == b - 1 || d == b - 2) // it can move only forward cannot move backward
            {
                return 0;
            }
            if (d == b + 2) // if the difference of y coordinates is equal to 2
            {
                if (c == a - 2)
                {

                    if ((Board[b + 1][a - 1].checkers).colour == RED || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)

                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == RED || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }
        }

        if ((Board[b][a].checkers).type == KING)
        {
            if ((Board[b][a].checkers).colour == BLUE) // if that position contains another player's piece
                return 0;
            if (d == b + 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b + 1][a - 1].checkers).colour == RED || (Board[b + 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {
                    if ((Board[b + 1][a + 1].checkers).colour == RED || (Board[b + 1][a + 1].checkers).colour == NOCOLOUR)
                        return 0;
                }
            }

            if (d == b - 2)
            {
                if (c == a - 2)
                {
                    if ((Board[b - 1][a - 1].checkers).colour == RED || (Board[b - 1][a - 1].checkers).colour == NOCOLOUR)
                        return 0;
                }

                if (c == a + 2)
                {

                    if ((Board[b - 1][a + 1].checkers).colour == RED || (Board[b - 1][a + 1].checkers).colour == NOCOLOUR)

                        return 0;
                }
            }
        }
    }

    return 1;
}

/******************************************************************
 * Movements return 0 in case of an invalid move
 * In case of valid move it captures if capture is possible, 
 * else just changes the coordinates of the player with
 * turn from c1 (initial coordinates) to c2(final coordinates).
 * For valid moves, it returns 1.
******************************************************************/
int movements(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2)
{
    char Y1, Y2;
    Y1 = c1.y + 'A';
    Y2 = c2.y + 'A';

    // isvalid=0 if invalid move, else isvalid=1
    int ans = isvalid(Board, turn, Y1, c1.x, Y2, c2.x);

    if (ans == 0) // Invalid move
    {
        return 0;
    }

    if ((abs(c1.y - c2.y) != 1) && (abs(c1.x - c2.x) != 1)) // Invalid move as it should be diagonal
    {
        return 0;
    }
    else // Valid move
    {
        // For Player - X
        if (turn == 'X')
        {
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = RED;
            if (c2.x == 8) // For KING
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = Board[c1.x - 1][c1.y].checkers.type;
            }
        }

        // For Player - O
        else
        {
            // Change the current piece features
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = BLUE;
            if (c2.x == 1) // For KING
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = Board[c1.x - 1][c1.y].checkers.type;
            }
        }

        // Update the previous piece features
        Board[c1.x - 1][c1.y].state = EMPTY;
        Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
        Board[c1.x - 1][c1.y].checkers.type = NOPEICE;
    }
    return 1; // Returns 1 for a Successful Move
}

//function that performs capture
int captures(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2)
{
    char y1, y2;
    y1 = c1.y + 'A';
    y2 = c2.y + 'A';
    int ans, x_coordinate, y_coordinate;
    x_coordinate = (c2.x + c1.x) / 2;
    y_coordinate = (c2.y + c1.y) / 2;
    int x;
    ans = isvalid(Board, turn, y1, c1.x, y2, c2.x);
    if (ans == 0)
    {
        return 0;
    }
    else if ((abs(c2.x - c1.x) != 2) && (abs(c2.y - c1.y) != 2))
    {
        return 0;
    }
    else
    { //capture is performed by making the peice properties- empty, nocolour
        Board[x_coordinate - 1][y_coordinate].state = EMPTY;
        Board[x_coordinate - 1][y_coordinate].checkers.colour = NOCOLOUR;
        if (Board[x_coordinate - 1][y_coordinate].checkers.type == KING) //if king is captured 2 is returned
            x = 2;
        else
            x = 1;                                                     //if a normal peice is captured 1 is returned
        Board[x_coordinate - 1][y_coordinate].checkers.type = NOPEICE; //updates that there is no peice at the coordinate anymore
        if (turn == 'X')
        {
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = RED;
            if (c2.x == 8)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING; //checks whether upon capture the peice becomes a king
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = Board[c1.x - 1][c1.y].checkers.type; //else retain the peice type from earlier
            }
        }
        else //same changes for red
        {
            Board[c2.x - 1][c2.y].state = FULL;
            Board[c2.x - 1][c2.y].checkers.colour = BLUE;
            if (c2.x == 1)
            {
                Board[c2.x - 1][c2.y].checkers.type = KING;
            }
            else
            {
                Board[c2.x - 1][c2.y].checkers.type = Board[c1.x - 1][c1.y].checkers.type;
            }
        }
        //old coordinates are made empty
        Board[c1.x - 1][c1.y].state = EMPTY;
        Board[c1.x - 1][c1.y].checkers.colour = NOCOLOUR;
        Board[c1.x - 1][c1.y].checkers.type = NOPEICE;
    }
    return x;
}

//checking for coordinates where captures can be continued, from before
coordinates *double_captures(checkersGrid Board[][SIZE], char turn, coordinates c)
{
    int x = c.x, i = 0, temp;
    char y = c.y + 'A';
    int size = isvalid(Board, turn, y, x, y + 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x - 2) + isvalid(Board, turn, y, x, y + 2, x - 2);
    coordinates *final_coordinates;
    //These are all the coordinates where captures will be taking place
    // Check the coordinates diagonally situated from the current square by two squares, and check for the existence of captures
    // x + 2, y + 2 | x - 2, y - 2 | x + 2, y - 2 | x - 2, y + 2 are all checked, now all that is left to check is to see if the captures can be done, upon which the size of the final_coordinates array increases
    final_coordinates = (coordinates *)malloc(sizeof(coordinates) * size);
    // checks for all diagnol moves
    if (isvalid(Board, turn, y, x, y + 2, x + 2) == 1)
    {
        final_coordinates[i].x = x + 2;
        temp = y + 2 - 'A';
        final_coordinates[i].y = temp;
        i++;
    }
    if (isvalid(Board, turn, y, x, y - 2, x + 2) == 1)
    {
        final_coordinates[i].x = x + 2;
        temp = y - 2 - 'A';
        final_coordinates[i].y = temp; //int(y - 2 - 'A');
        i++;
    }
    if (isvalid(Board, turn, y, x, y - 2, x - 2) == 1)
    {
        final_coordinates[i].x = x - 2;
        temp = y - 2 - 'A';
        final_coordinates[i].y = temp; //int(y - 2 - 'A');
        i++;
    }
    if (isvalid(Board, turn, y, x, y + 2, x - 2) == 1)
    {
        final_coordinates[i].x = x - 2;
        temp = y + 2 - 'A';
        final_coordinates[i].y = temp;
        i++;
    }
    return final_coordinates;
}

//checking if capture is possible for a single square
int is_capture(checkersGrid Board[][SIZE], char turn, coordinates c)
{
    //if captures is possible, return 1 else return 0
    int x = c.x;
    char y = c.y + 'A';
    return isvalid(Board, turn, y, x, y + 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x + 2) + isvalid(Board, turn, y, x, y - 2, x - 2) + isvalid(Board, turn, y, x, y + 2, x - 2);
}

///checking if captures is possible at all
int if_capture(checkersGrid Board[][SIZE], char turn)
{
    int colour, flag = 0;
    //char input;
    coordinates temp;
    if (turn == 'X')
    {
        colour = RED;
    }
    else
    {
        colour = BLUE;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            //we'll first check which one of these are within bounds.
            if (Board[j][i].checkers.colour == colour)
            {
                temp.x = j + 1;
                temp.y = i;
                //flag = flag | isvalid(Board, turn, input, i, input + 2, i + 2) | isvalid(Board, turn, input, i, input + 2, i - 2) | isvalid(Board, turn, input, i, input - 2, i + 2) | isvalid(Board, turn, input, i, input - 2, i - 2);
                flag = flag | is_capture(Board, turn, temp);
                if (flag == 1)
                    return flag;
                // j will be the alphabet, i is the letter input
                //pass all possible vanues to is_valid function and see if a one is being returned
            }
        }
    }

    return flag;
}

int winner(checkersGrid Board[][SIZE], char turn)
{
    int x_count = 0;
    int o_count = 0;
    bool x_move = false;
    bool o_move = false;

    // checks for the number of peices for both colors and if there are any valid moves for both parties
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (Board[i][j].checkers.colour == BLUE)
            {
                o_count++;
                if (o_move == false)
                {
                    for (int z = 1; z <= 2; z++)
                    {
                        if (isvalid(Board, 'O', j + 'A', i + 1, j + 'A' + z, i + 1 + z) + isvalid(Board, 'O', j + 'A', i + 1, j + 'A' - z, i + 1 + z) + isvalid(Board, 'O', j + 'A', i + 1, j + 'A' + z, i + 1 - z) + isvalid(Board, 'O', j + 'A', i + 1, j + 'A' - z, i + 1 - z))
                            o_move = true;
                        if (o_move)
                            break;
                    }
                }
            }
            else if (Board[i][j].checkers.colour == RED)
            {
                x_count++;
                if (x_move == false)
                {
                    for (int z = 1; z <= 2; z++)
                    {
                        if (isvalid(Board, 'X', j + 'A', i + 1, j + 'A' + z, i + 1 + z) + isvalid(Board, 'X', j + 'A', i + 1, j + 'A' - z, i + 1 + z) + isvalid(Board, 'X', j + 'A', i + 1, j + 'A' + z, i + 1 - z) + isvalid(Board, 'X', j + 'A', i + 1, j + 'A' - z, i + 1 - z))
                            x_move = true;
                        if (x_move)
                            break;
                    }
                }
            }
        }
    }
    // if count of X is 0, O is the winner
    if (x_count == 0)
    {
        return 1;
    }
    // if count of O is 0, X is the winner
    else if (o_count == 0)
    {
        return 2;
    }
    // game is tie, if either parties can't move
    if (x_move == false && o_move == false)
    {
        return 3;
    }
    // if X can't move, O is the winner
    if (x_move == false)
    {
        return 1;
    }
    // if O can't move, X is the winner
    if (o_move == false)
    {
        return 2;
    }
    return 0;
}

void sound()
{
    // To add sound when a valid move(either diagonal or capture) is made
    printf("\a");
}

// derived from if_capture
int if_capture_possible(checkersGrid Board[][SIZE], char turn)
{
    int colour;
    coordinates temp;
    if (turn == 'X')
    {
        colour = RED;
    }
    else
    {
        colour = BLUE;
    }
    // checks if any captures for the specific turn are possible and return accrodingly
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (Board[i][j].checkers.colour == colour)
            {
                temp.x = i + 1;
                temp.y = j;
                if (ifdouble(Board, temp, turn))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
// removes whitespace from a string
char *remove_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

Player p1;
Player p2;

int validatedNames(){
    for(int i = 0; i<strlen(p1.name);i++){
        if(isalpha(p1.name[i]) == 0){
            printf("\nThe names can't have digits or special characters!\n");
            return 0;
        }
    }
    for(int i = 0; i<strlen(p2.name);i++){
        if(isalpha(p2.name[i]) == 0){
            printf("\nThe names can't have digits or special characters!\n");
            return 0;
        }
    }
    return 1;
}

void toUpper(char *name){
    for(int i=0;i<strlen(name);i++){
        name[i] = toupper(name[i]);
   }
}

void selectPlayers() {
     int valid = 0;
     while(valid == 0){
        system("cls");
        printf("\nInput player 1's name: ");
        scanf("%s", &p1.name);
        printf("\nInput plyers 2's name: ");
        scanf("%s", &p2.name);
        p1.points = 0;
        p2.points = 0;
        valid = validatedNames();
        printf("\nPress any key to continue!\n");
        getch();
     }
    toUpper(p1.name);
    toUpper(p2.name);
}

int addRanking(char *name, int points){
   char line[1024];
   char s1[10];
   int count = 0;
   int countTmp = 0;
   int exist = 0;

   FILE *file;
   FILE * fTemp;

   file = fopen(ranking, "r+");
   while (fgets(line , sizeof(line) , file )!= NULL)
   {
      count++;
      if (strstr(line , name)!= NULL){
          exist = 1;

          for(int i = 0; i<strlen(line); i++){
               if(isdigit(line[i]) == 1){
                    for(int a = 0; a<sizeof(s1); a++){
                        if (isdigit(s1[a]) == 0){
                            s1[a] = line[i];
                            break;
                        }
                    }
                }
            }
            break;
         }
    }
    if (exist == 1){
        int i = atoi(s1);
        char s2[10];
        char s3[100] = "";

        fTemp = fopen("config/replace.tmp", "w");
        points += i;
        sprintf(s2, "%d", points);
        strcat(s3, name);
        strcat(s3, " = ");
        strcat(s3, s2);
        strcat(s3, "\n");
        
        rewind(file);
         while ((fgets(line, sizeof(line), file)) != NULL)
        {
            countTmp++;
            if (countTmp == count){
                fputs(s3, fTemp);
            }
            else{
                fputs(line, fTemp);
            }
        }

        fclose(file);
        fclose(fTemp);

        remove(ranking);
        rename("config/replace.tmp", ranking);
    }
    else{
        fprintf(file, "%s = %d \n", name, points);
        fclose(file);
    }

   }

int game(void)
{
    selectPlayers();
    // variables
    checkersGrid CheckerBoard[SIZE][SIZE];
    initBoard(CheckerBoard);
    char turn = 'X';
    playerTurn = 1;
    int capture, valid;
    coordinates start, final;
    char temp1, temp2;
    char dummy[100];
    int win = 0;
    int capture_possible;
    int capture_temp;
    char input[100];
    int draw;
    getchar();

    while (1)
    {
        system("cls");    
        printBoard(CheckerBoard);
        printf("\n               ");
        printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
        printf("Input: ");
        scanf("%[^\n]", input);
        getchar();
        remove_spaces(input);
        // draw
        if (!strcmp(input, "2"))
        {
            if (win == 0)
            {
                system("cls");
                printBoard(CheckerBoard);
                printf("\n               ");

                turn = switchTurn(turn);
                printf("Does %s accept the draw offer?\nEnter 1 to accept, else enter any other number\n", (playerTurn == 1) ? p1.name : p2.name);
                scanf("%d", &draw);
                getchar();
                if (draw == 1)
                {
                    win = 3;
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("The game is a draw\n");
                    turn = switchTurn(turn);
                }
                else
                {
                    printf("Player %s does not accept\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                }
            }
            else
            {
                printf("Can't offer draw after win\n");
            }
            printf("Enter anything to continue.");
            scanf("%[^\n]", dummy);
            getchar();
        }
        // Exit
        else if (!strcmp(input, "0"))
        {
            system("cls");
            printBoard(CheckerBoard);
            printf("\n                  Thank you for playing the game!!\n\n");
            return 0;
        }
        // Input moves
        else if (!strcmp(input, "1"))
        {
            // if win or draw has taken place input cannot be called
            if (win != 0)
            {
                system("cls");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                printf("You cannot input as winner is declared\n");
                printf("Enter anything to continue.\n");
                scanf("%[^\n]", dummy);
                getchar();
            }
            else
            {
                system("cls");
                printBoard(CheckerBoard);
                printf("\n               ");
                printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                printf("             ");
                printf("      Enter values of X1 Y1 X2 Y2\n");
                scanf(" %c %d %c %d", &temp1, &start.x, &temp2, &final.x);
                getchar();
                temp1 = toupper(temp1);
                temp2 = toupper(temp2);
                start.y = temp1 - 65;
                final.y = temp2 - 65;
                // check if captures in the current position are possible
                capture_possible = if_capture_possible(CheckerBoard, turn);
                // check if capture move was played
                capture = captures(CheckerBoard, turn, start, final);
                capture_temp = capture > 0 ? 1 : 0;
                // if capture was possible and that move was not played
                if (capture_temp != capture_possible)
                    valid = -1;
                else
                    valid = movements(CheckerBoard, turn, start, final) || capture; //move will be valid if either of capture or movements are true

                printf("\n\n");
                // if the move made was valid
                if (valid == 0)
                {
                    // Invalid move
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("                     Invalid Move, Try Again!\n");
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
                // capture was possible but was not inputted my the player
                else if (valid == -1)
                {
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("\n           Invalid Move, Try Again! Capture is possible\n");
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
                // Valid move
                else
                {
                    sound();
                    if (ifdouble(CheckerBoard, final, turn) && capture > 0)
                        ;
                    else
                        turn = switchTurn(turn);
                }
                // check for winner
                win = winner(CheckerBoard, turn);
                // draw
                if (win == 3)
                {
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("The game is a draw\n");
                }
                // O is the winner
                if (win == 1)
                {
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("The winner is %s\n", p2.name);
                    addRanking(p2.name, 1);
                }
                // X is the winner
                else if (win == 2)
                {
                    system("cls");
                    printBoard(CheckerBoard);
                    printf("\n               ");
                    printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
                    printf("The winner is %s\n", p1.name);
                    addRanking(p1.name, 1);
                }
                // if winner has been declared
                if (win != 0)
                {
                    printf("Enter anything to continue.\n");
                    scanf("%[^\n]", dummy);
                    getchar();
                }
            }
        }
        // invalid input
        else
        {
            system("cls");
            printBoard(CheckerBoard);
            printf("\n               ");
            printf(" ************ %s's Turn | Pieces '%c' ************\n", (playerTurn == 1) ? p1.name : p2.name, turn);
            printf("Invalid input\n");
            printf("Enter anything to continue.\n");
            scanf("%[^\n]", dummy);
            getchar();
        }
    }
    return 0;
}