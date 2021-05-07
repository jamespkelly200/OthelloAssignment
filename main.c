// Othello James Kelly J.K
// 5/5/2021
// 20200666 Software Engineering Project Assignment 2
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 8 // Size of board is 8*8
const char p1_c = 'B';// p1_c stands for player 1 character
const char p2_c = 'W';// player 2 character

//functions
void start_game();
void display(char board[][SIZE]);
void make_move(char board[][SIZE], int row, int col, char player);
void move_choose(char player);
int countPiecesBlack();
int countPiecesWhite();
int validateMove(char board[][SIZE], char player);
///bool available_moves[SIZE][SIZE] = {false};
bool available_moves[SIZE][SIZE];// they all get initialized to false in validateMove function
void goPlayer1();
void goPlayer2();

void writeToFileOutput();

// Othello board struct
struct Board{
    char othello[SIZE][SIZE];
};struct Board Othello;
// position on the board in terms of x and y
struct position{
    int x;
    char y;
};struct position Position;

int stopGame=0;// this entire variable's only purpose is for the passing of moves between players and if after a move has been passed
// and then the other player moved, the game has to end. This variable helps us do that.
// I have added this right at the end of my program when i was doing testing and when a player needed to pass/ be skipped,
// the program would crash. So now with this feature, everything works and now including when a player has to be skipped
// because he cant move.

// struct holds players names and scores as well as their black and white characters
struct game{
    char player1Name[20];
    char player2Name[20];
    char p1_c;
    char p2_c;
    int scorePlayer1;
    int scorePlayer2;
};struct game event;


int main() {
    event.p1_c = 'B';            // Player 1 is black and Player 2 is White
    event.p2_c = 'W';
    start_game();
    display(Othello.othello);

    // while the whole board is not filled (both scores added together equal to 64), or while a players score is not 0, Continue with the game.
    // If one of these conditions is met, then the game is over.
while(stopGame == 0){
    while ((event.scorePlayer1 != 32 && event.scorePlayer2 != 32) || (event.scorePlayer1 + event.scorePlayer2 != 64) ||
           (event.scorePlayer1 != 0) ||
           (event.scorePlayer2 != 0)) {// || (countPiecesWhite() != 0) || (countPiecesBlack()!=0)

        // call goPlayer1 function to go through the process of making the move for player 1
        goPlayer1();

        // VERY IMPORTANT
        // After the player has moved, the scores and the board have been altered, therefore, if statements
        // have to be used to check if a player can or cant go after a move has just been made.
        // So check if both players cant go!! If this is the case, then the game has to end so check why the game
        // has to end. It could be because player 1 has no pieces left and therefore cant make any move, which means
        // player 2 also cant make any move; both players validate move function returns 0. And visa versa.
        // Or, while both players scores are above 0 and not equal to 0, it could have ended because both players
        // just cant make any moves. So this instance, the game ends in a draw.
        if ((validateMove(Othello.othello, event.p1_c)) == 0 && (validateMove(Othello.othello, event.p2_c)) == 0) {
            stopGame=1;
            if (event.scorePlayer1 == 0) {
                printf("Game ends because %s has 0 pieces left!! (#1 break)\n", event.player1Name);
                break;
            } else if (event.scorePlayer2 == 0) {
                printf("Game ends because %s has 0 pieces left!! (#2 break)\n", event.player2Name);
                break;
            } else {
                printf("Both players cant go!! Therefore, the game ends (#3 break)\n");
                break;
            }
        }

        // After checks have been performed, if the game is still live, the next player makes his/her turn.
        // in this case player 2 now plays.
        goPlayer2();

        // Once again, just like above, the same checks have to be used to see if the game has now ended on that specific move \
        // just made by player 2. So go through same checks again.
        if ((validateMove(Othello.othello, event.p1_c)) == 0 && (validateMove(Othello.othello, event.p2_c)) == 0) {
            stopGame=1;
            if (event.scorePlayer1 == 0) {
                printf("Game ends because %s has 0 pieces left!! (#4 break)\n", event.player1Name);
                break;
            } else if (event.scorePlayer2 == 0) {
                printf("Game ends because %s has 0 pieces left!! (#5 break)\n", event.player2Name);
                break;
            } else {
                printf("Both players cant go!! Therefore, the game ends (#6 break)\n");
                break;
            }
        }

        // checks ended so continue in while loop until the condition/break is met.
    }
}
    // while loop has been exited. This means the game has ended.
    // SO, print the final board and the scores of both players.
    printf("The final board is:\n");
    display(Othello.othello);
    printf("END OF GAME!! WELL PLAYED TO BOTH PLAYERS\n");
    printf("Black has %d pieces and white has %d pieces\n", event.scorePlayer1, event.scorePlayer2);
    // Then work out who won. Whichever players score is higher, wins.
    // If both players scores are equal, the game ends in a draw.
    if(event.scorePlayer1>event.scorePlayer2){
        printf("Congratulations!! %s has won the game with %d tokens\n", event.player1Name, event.scorePlayer1);
    }
    else if(event.scorePlayer1<event.scorePlayer2){
        printf("Congratulations!! %s has won the game with %d tokens\n", event.player2Name, event.scorePlayer2);
    }else{
        printf("No player managed to beat the other. The game ends in a draw. WEll DONE TO BOTH!!");
    }

    // Finally, write out the results to the file "othello-results.txt"
    writeToFileOutput();

    return 0;
}
void start_game(){// Start the game function
    printf("***     Welcome to Othello      ***\n");// print the Welcome
    printf("Please enter the name of player 1 (Black): \n");// ask for player details
    scanf("%s",event.player1Name);

    //printf("%s\n", player1Name);
    printf("Please enter the name of player 2 (White): \n");
    scanf("%s",event.player2Name );
    //printf("%s\n", player2Name);

    event.scorePlayer1 = 2;// set players scores to 2 each since that is how the board starts
    event.scorePlayer2 = 2;

    // double nested for loop looping a total of 64 times to initialize each square on the board to empty!!
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            // board[row][col] = ' ';
            Othello.othello[row][col] = ' ';
        }
    }

    //Once we have initialized the board, we want to set up the start of the board which has 2 characters of each  player
    // in the center of the board.

    int middle = SIZE / 2;// declare middle variable as the middle of the board, (SIZE of Board/2)

    // -4 -3 0 -3
    Othello.othello[middle][middle] = p2_c;// Othello board struct of middle, middle = W
    Othello.othello[middle - 1][middle - 1] = p2_c;// Othello board struct of middle-1, middle-1 = W

    Othello.othello[middle][middle - 1] = p1_c;// Othello board struct of middle, middle-1 = B
    Othello.othello[middle - 1][middle] = p1_c;// Othello board struct of middle-1, middle = B

    //Othello.othello[middle - 1-2][middle-1] = p2_c; // this was just used for testing purposes.
}
void display(char board[][SIZE])// display the board function
{
    // print out the scores of each player.
    printf("Score: %s (Black) %d:%d %s (White)\n", event.player1Name , event.scorePlayer1,event.scorePlayer2, event.player2Name );
    char column = 'a';               // Make the first column = a
    printf("\n ");                   // print new line
    for(int i = 0 ; i < 8; i++){
        printf("   %c", column + i);   // now loop through 8/SIZE times and print out the label for the columns starting with
        // a and ending up at h. No new line character is needed as the different columns are printed on one line.
    }

    printf("\n");                       // Now print a new line to end the top line

    // Now start filling the rest of the board.
    for(int row = 0;row < SIZE;row++)
    {
        // print out the top line for each row.
        printf("   ");// this is the start of each row
        for(int i = 0;i < 8;i++){ // within each row,print --- to make the blocks.
            printf("--- ");
        }

        // after each row is printed individually, print the | character going down for the boarder between blocks on the board.
        printf("\n%2d|",row + 1);// the row for loop starts at 0, we want the label of the rows to read from 1, not 0.
        // So solution: just print (row + 1).
        // Now print out the characters in the current row. Most of them will be ' ' at the start with some 'B' and 'W'
        for(int i = 0;i < 8;i++)
            printf(" %c |", board[row][i]);  //  print the characters in the current row we are in.

        printf("\n");// new line for the next row.

    }

    // print the botton line.
    printf("   ");
    for(int i = 0;i < 8;i++){
        printf("--- ");// print --- for the botttom of the board.
    }
    printf("\n");
}

void goPlayer1() {
    // This is just a small extra feature that just tells the user how many available moves they can make!!
    // But, also, calling the number of moves available initializes the bool available_moves variable to true on the valid moves.
    // THis is ver important, without it, the program would crash.
    printf("%s You have %d moves available\n", event.player1Name, validateMove(Othello.othello, event.p1_c));
    // validate move returns an integer of the number of moves available. If it returns 0, there is no moves available

    // THis if statement below is basically the "pass" aspect of Othello. THe computer does the pass for the user/player
    // so that there is no confusion. So if a player cant go, they are passed, and the next player plays again.
    // So to check this, we use this statement:
    // "if(validateMove(Othello.othello, moves, event.p1_c)) == 0"
    // if there is no moves available for player 1, then pass to player 2.
    // But very importantly, if a player cant go and needs to pass, (so in this case player 1 cant go)
    // we also need to check that the other player (player 2) can actually go.
    // There is no use passing if both players cant go.
    // SO we add in the part of the check:
    // "&& (validateMove(Othello.othello, moves, event.p2_c)) != 0 )"
    // to make sure that available moves for the other player exist.
    while (1) {// this is just so that when we hit a break statement, we can break out of this function

    if ((validateMove(Othello.othello, event.p1_c)) == 0 &&
        (validateMove(Othello.othello, event.p2_c)) != 0) {// if player 1 cant go but player 2 can go:
        printf("There is no available moves for %s!! SO, %s will be skipped\n", event.player1Name, event.player1Name);
        printf("It is now %s's turn\n", event.player2Name);
        goPlayer2();// make player 2 go.
        // but straight after player 2 has gone, we have to check again if any one can move and if the game should now be over.
        if((validateMove(Othello.othello, event.p1_c)) == 0 && (validateMove(Othello.othello, event.p2_c)) == 0) {
        stopGame=1;// if both players at this point cant go, then stopGame = 1 to end the while in the main function
        break;
        ///break;
        }
        //checkStatementsAfterturn();
        ///if((validateMove(Othello.othello, event.p1_c)) != 0 ) {
            goPlayer1();// we have to call goPlayer1 again because after we skipped player1 and player 2 went, the
            // program would break out of this function go back to the main and player 2 would go again. We cant have that
            // so player 1 has to go so that the order is kept in tact. So to walk you through why we need to call
            // goPlayer1 again is because coming into this function,:
            // 1) player 2 would have just gone
            // 2) then player 1 needed to be skipped
            // 3) so skip player 1 and goPlayer2 (player 2 has now gone twice in a row)
            // 4) after goPlayer2, goPlayer1 has to go because outside this function, the next go is player2.
            // If we didnt call goPlayer1, player 2 would have gone 3 times in a row!
        ///}
        break;
    } else {// so if player 1 has available moves > 0 and can play, (i.e they dont need to pass) then choose the move
        move_choose(event.p1_c);// call fucntion move_choose.
    }


    // the available_moves variable only stores true or false and returns true or false depending
    // on if the move chosen is valid or not. This has been implemented in the validateMove function.
    // keep asking for the players move until the available moves returns true.
    while (available_moves[Position.x][Position.y] != true) {// while user has entered wrong move:
        printf("YOU HAVE MADE AN INCORRECT MOVE. PLEASE TRY AGAIN!!!\n");
        move_choose(event.p1_c);//  implement function move_choose again.
    }


    // They have now made a valid move, so
    // Then make the move in terms of where they chose in x and y
    make_move(Othello.othello, Position.x, Position.y, p1_c);
    countPiecesBlack();// count black and white pieces
    countPiecesWhite();
    display(Othello.othello);// display board again after move made successfully
    printf("%s's score is %d\n\n", event.player1Name, event.scorePlayer1);// print out their score.
    break;
    }
}

void goPlayer2(){
    // calling the number of moves available initializes the bool available_moves variable to true on the valid moves.
    // THis is ver important, without it, the program would crash.
    printf("%s You have %d moves available\n", event.player2Name, validateMove(Othello.othello, event.p2_c));

    // THis if statement below is basically the "pass" aspect of Othello. THe computer does the pass for the user/player
    // so that there is no confusion. So if a player cant go, they are passed, and the next player plays again.
    // So to check this, we use this statement:
    // "if(validateMove(Othello.othello, moves, event.p2_c)) == 0"
    // if there is no moves available for player 2, then pass back to player 1.
    // But very importantly, if a player cant go and needs to pass, (so in this case player 2 cant go)
    // we also need to check that the other player (player 1) can actually go.
    // There is no use passing if both players cant go.
    // SO we add in the part of the check:
    // "&& (validateMove(Othello.othello, moves, event.p1_c)) != 0 )"
    // to make sure that available moves for the other player exist.

    while (1) {// this is just so that when we hit a break statement, we can break out of this function
    if((validateMove(Othello.othello, event.p2_c)) == 0 && (validateMove(Othello.othello, event.p1_c)) != 0){// while....  != true
        printf("There is no available moves for %s!! SO, %s will be skipped\n", event.player2Name, event.player2Name);
        printf("It is now %s's turn\n", event.player1Name);
        goPlayer1();
        // but straight after player 2 has gone, we have to check again if any one can move and if the game should now be over.
        if((validateMove(Othello.othello, event.p2_c)) == 0 && (validateMove(Othello.othello, event.p1_c)) == 0) {
            stopGame=1;// if both players at this point cant go, then stopGame = 1
            break;
        }
        ///if((validateMove(Othello.othello, event.p2_c)) != 0 ) {
        goPlayer2();
        ///}
        break;
    }else{// so if player 2 has available moves > 0 and can play, (i.e they dont need to pass) then choose the move
        move_choose(event.p2_c);// call function
    }

    // the available_moves variable only stores true or false and returns true or false depending
    // on if the move chosen is valid or not. This has been implemented in the validateMove function.
    // keep asking for the players move until the available moves returns true.
    while(available_moves[Position.x][Position.y] != true){// while user has entered wrong move:
        printf("YOU HAVE MADE AN INCORRECT MOVE. PLEASE TRY AGAIN!!!\n");
        move_choose(event.p2_c);// implement function again
    }


    // They have now made a valid move, so
    // Then make the move in terms of where they chose in x and y
    make_move(Othello.othello, Position.x, Position.y, p2_c);
    countPiecesBlack();// count pieces
    countPiecesWhite();
    display(Othello.othello);// display board again after move made succesfully
    printf("%s's score is %d\n\n",event.player2Name, event.scorePlayer2);// print out their score.
        break;
    }
}

void move_choose(char player){// this function asks the player where they want to move characters.

        printf("%c please enter your move in the form of row number first followed by column character: Then press enter\n", player);

        scanf("%d%c", &Position.x, &Position.y);// scan input into Position.x and Position.y
        printf("%c you chose to move to %d%c.\n", player, Position.x, Position.y);
        Position.y = tolower(Position.y) - 'a';      // Convert Position.y to an index, to a number and not a character
        // Starts from 0 but the board reads from 1
        Position.x--;  // Also decrement x because it starts from 0 but the board reads from 1

}

int countPiecesBlack(){ // function counts black pieces
    int totalBlack=0;
    for(int j=0;j<SIZE;j++){
        for(int i=0;i<SIZE;i++){// nested for loop to go through each block on the board and detirmine if the Black character
            // is in the block.
            if(Othello.othello[i][j]=='B'){// if the block is = to B, then thats a black character so count it.
                totalBlack++;// increment the counter
            }
        }

    }
    event.scorePlayer1 = totalBlack;// score of Black(Player 1) = counter.
    printf("Black has %d pieces\n", event.scorePlayer1);
    return(totalBlack);
}
int countPiecesWhite(){ // function counts black pieces
    int totalWhite=0;
    for(int j=0;j<SIZE;j++){
        for(int i=0;i<SIZE;i++){// nested for loop to go through each block on the board and detirmine if the White character
            // is in the block.
            if(Othello.othello[i][j]=='W'){// if the block is = to W, then thats a white character so count it.
                totalWhite++;// increment the counter
            }
        }

    }
    event.scorePlayer2 = totalWhite;// score of White(Player 2) = counter.
    printf("White has %d pieces\n", event.scorePlayer2);
    return(totalWhite);
}

void make_move(char board[][SIZE], int row, int col, char player)// this function makes the actual move on the board
{
    // Identify who the opponent is, ie, whp the player is, and then who the opponent is
    char myOpponent;// the character to see who the opposition is. If make_move is being run with p1_c, then that means the opponent
    // and the opponents squares are all p2_c's. So myOpponent needs to be = to p2_c. And vis versa
    if(player == p1_c){
        myOpponent = p2_c;
    }else{
        myOpponent= p1_c;
    }


    board[row][col] = player;   //Place the player character token where they chose to move.

    // now check all the squares around this new character for the opponents character to see if opponents character needs to
    // be swapped to players character.
    for(int rowIncrement = -1; rowIncrement <= 1; rowIncrement++) {
        for (int colIncrement = -1; colIncrement <= 1; colIncrement++) {
            if (row + rowIncrement < 0 || row + rowIncrement >= SIZE || col + colIncrement < 0 || col + colIncrement >= SIZE || (rowIncrement == 0 && colIncrement == 0)){
                continue;// dont need to do anything; these cases are when the position the person has moved their token/character
                // to is either right on the edge of the board. ie. on the first or last row or first or last column
            }

            // Now check each of the squares around the position of the character of whatever the result is of the row
            // plus the current rowIncrement and and then the result of the column + the current column increment from
            // our two nested for loops above.
            if (board[row + rowIncrement][col + colIncrement] == myOpponent) {
                // Basically if the position of board[row][column] plus the current rowIncrement and current columnIncrement is equal
                // to the opponents character, then use our variables x and y for searching in a similar direction for more
                // opponent characters.

                int x = row + rowIncrement;           // Make x equal to the position of the opponent we are working with
                int y = col + colIncrement;           // same with y to make the square.



                while(1) {// while(1) is while true.
                    // so keep looping until there is a break statement and then exit the while if
                    // exncontering a break statement. So because we have the for loop above and the nested for loop looping through
                    // rowIncrement and colIncrement, and this whole while loop is within the for loop, we will get and use
                    // all the different values of x and y as x and y were initially 0 but now they get incremted whatever the
                    // current rowIncremnt and colIncremtn is. We using x and y in the below algorithm to detirmine what
                    // board piece should be what character player after a specific move has been made. So, once a
                    // break statement has been executed, its not the end of the function!! Remember there is still for loops above
                    // that this while loop is within and so after a break statement the for loop increments again and the process
                    // then starts again and x and y then become different values becaue of the increments
                    // and new checks are then made below according to the different x and y values of the board position.

                    // increment x by the row increment and also y by the column increment
                    // so that we move on to do all the if statement checks below of the next square.
                    x += rowIncrement;
                    y += colIncrement;



                    // This is if x or y are off the board then theres nothing to do so execute break statement which will
                    // then exit the while loop and then increment the various variables in the for loops and start again
                    // with different x and y values.
                    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE){
                        break;
                    }

                    // same thing if the square of the board of x and y is a blank and no character is on it, then
                    // execute break statement.
                    if (board[x][y] == ' '){
                        break;
                    }

                    // If and when we actually find the player character that is currently making the move, whether it be
                    //W for white of B for Black, then now execute a different check to sort of see the line it came from
                    //and then change the relevant opponent characters to
                    //the player characters as the player has taken the opponents character.
                    //For example if Black was moving and a piece of the board was looking like | B | W |
                    // and Black chose to move to the right of white, like this, | B | W | B |
                    // then rules of Othello state that white needs to be flipped over anad become black.
                    // So after the move it should look like | B | B | B |.
                    // So if we encounter the player character, we need to check around the character for the opponents character.
                    // and then IF NECCESSARY, change the opponetns character.
                    if (board[x][y] == player) {

                        int change_x, change_y;
                        change_x = x - rowIncrement;// basically another x variable that is set the value of x - the rowIncrement
                        change_y = y - colIncrement;// same thing here with this variable = y-colIncrement.
                        //This is to keep the x and y values unchanged.
                        // So go bakwards from the move made and minus the increments to see if the change variables need to
                        // be changed to the player character.

                        while(board[change_x][change_y] == myOpponent){  // if the position(x and y minus the increments) is = to opponent then: change it:
                            printf("THIS IS A VALID MOVE\n");
                            printf("change_x is (%d)\n", change_x);
                            printf("change_y is (%d)\n", change_y);
                            printf("x is %d\ny is %d\n", x, y);
                            board[change_x][change_y] = player;   // The position of the board (change_x, change_y) needs to be changed so change
                            // the opponents character to player character. Do the change just by
                            // setting the position on the board that was the opponent, = equal to
                            // the player character.
                            // now update the change variables to check if there are any other opposition characters
                            // that need to be changed, and if they are, the while loop will run again and change them
                            // and if they are no more to be changed, execute break statement.
                            change_x = change_x - rowIncrement;
                            change_y = change_y - colIncrement;
                            printf("after - increments, change_x = (%d), change_y = %d\n", change_x, change_y);
                        }

                        break; // the while has finished, i.e we have checked all the blocks of the opponent
                        // character and changed the ones we needed to. SO execute break statement.
                    }

                }

            }

        }
    }
}

int validateMove(char board[][SIZE], char player){// this function is very similar to the above,
    // make_move function in that it uses the same thinking to count up all the possible valid moves there is to make for player.
    // It returns an integer representing the number of moves available for the player.
    // But, it also initializes all the available moves that there is to that player to true under the global variable
    // name, available_moves. For instance, all 64 squares will be initialized to false and then when a valid move pops up,
    // that specific square on the board, (Ohello.othello), will be set to true. So that
    // when validating a move in the main function, if a move of a certain position (that entered by the user)
    // is true under available_moves, then that move is validated.
    // If it is false under available_moves, then that means its not a valid move, so then the user would have to enter
    // another choice.


    // SINCE THIS FUNCTION IS VERY SIMILAR TO THE MAKE MOVE FUNCTION ABOVE, THERE WONT BE MANY COMMENTS BECAUSE THE METHODS
    // ARE VERY SIMILAR, IF NOT THE SAME

    int moveCounter = 0;// this variable holds the number of possible moves to make. Its initialized when there is an available move

    // Identify who the opponent is, ie, whp the player is, and then who the opponent is.
    char myOpponent;// the character to see who the opposition is. If make_move is being run with p1_c, then that means the opponent
    // and the opponents squares are all p2_c's. So myOpponent needs to be = to p2_c. And vis versa
    if(player == p1_c){
        myOpponent = p2_c;
    }else{
        myOpponent= p1_c;
    }

    // make all moves to false. ie. no available moves
    for(int row = 0; row<SIZE; row++){
        for(int col = 0; col<SIZE; col++){
            available_moves[row][col] = false;
        }
    }

    // now try get places to move that are actually valid.
    for(int row = 0; row<SIZE; row++){
        for(int col = 0; col<SIZE; col++){
            if(board[row][col] != ' ')   {
                ///return false;
                continue;
            }


            for(int rowdelta = -1; rowdelta <= 1; rowdelta++) {
                for (int coldelta = -1; coldelta <= 1; coldelta++) {
                    if (row + rowdelta < 0 || row + rowdelta >= SIZE || col + coldelta < 0 || col + coldelta >= SIZE || (rowdelta == 0 && coldelta == 0)){
                        ///return false;
                        continue;
                    }


                    if (board[row + rowdelta][col + coldelta] == myOpponent) {
                        int x = row + rowdelta;
                        int y = col + coldelta;

                        while(1) {// while true. loop until find a break statement or exit etc.
                            x += rowdelta;              // at the same time incrementing x and y by row delta and col delta
                            y += coldelta;


                            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE){
                                break;
                            }



                            if (board[x][y] == ' '){
                                break;
                            }


                            if (board[x][y] == player) {
                                // Most important part is available_moves. If this isnt set to true, we wont know what moves
                                // are actually available as all moves will still be set to false.
                                available_moves[row][col] = true;// gloval variable available_moves of row and col = true
                                moveCounter++;// its an available move so increment the moveCounter.
                                ///return true;
                                break;                    /* We are done    */

                            }

                        }

                    }

                }
            }


        }
    }
   /// return false;
    return moveCounter;// moveCounter will be the number of moves available to the player.
}


void writeToFileOutput(){
    FILE *fPtr;

    //"othello-results.txt"
    // read mode of the file is "a" for append so that we keep appending results to the file. If we used "w", we
    // would be overwriting everything all the time
    if((fPtr = fopen("C:/Users/James Kelly/CLionProjects/SoftwareEngineeringProject1/Ass2Beginning/inputFiles/othello-results.txt", "a")) == NULL){
        puts("File couldn't open");
    }
    else{
        //print out to file date and time of the game and the result of the game(winner and score)

        char date[10];
        char time[10];
        char winner[30];
        char looser[30];
        int score;

        // ask the user for the date and time of the game played
        printf("Please enter the date of this game and then once pressed enter, the time played:\n");
       scanf("%s%s", date, time);

       // work out the winner and the looser to print to file
        if(event.scorePlayer1>event.scorePlayer2){
            strcpy(winner, event.player1Name);
            score = event.scorePlayer1;
            strcpy(looser, event.player2Name);
        }
        else if(event.scorePlayer1<event.scorePlayer2){
            strcpy(winner, event.player2Name);
            score = event.scorePlayer2;
            strcpy(looser, event.player1Name);
        }else{
            strcpy(winner, event.player1Name);
            strcpy(looser, event.player2Name);
            score = event.scorePlayer1;
        }


        // if its a draw, print out a draw to the file
        if(event.scorePlayer1 == event.scorePlayer2){
            printf("DATE\t\t\tTIME\t\t\tRESULT\n");
            printf("%s\t\t%s\t\t%s drew to %s with %d tokens each\n", date, time, winner, looser, score);
            fprintf(fPtr, "%s\t\t%s\t\t%s drew to %s with %d tokens each\n", date, time, winner,looser, score);
            //scanf("%s%s", date, time);
        }else{// a player has won, so print out who he beat and what the score that he had was.
            printf("DATE\t\t\tTIME\t\t\tRESULT\n");
            printf("%s\t\t%s\t\t%s beat %s with %d tokens\n", date, time, winner, looser, score);
            fprintf(fPtr, "%s\t\t%s\t\t%s beat %s with %d tokens\n", date, time, winner,looser, score);
            //scanf("%s%s", date, time);
        }


        fclose(fPtr);

    }
}
