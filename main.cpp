#include <iostream>
#include <ctime>
#include <cctype>

char chooseSign(char &playerSign, char &botSign);
void buildMap(char map[3][3]);
void pickRowCol(int &row, int &col, char map[3][3], char playerSign);
void botPick(int &row, int &col, char map[3][3], char botSign);
void winCheck(char map[3][3], char playerSign, char botSign, bool &gameover);

int main() {

    // end the game flag
    bool endGame = false;

    // define map, player and bot chars
    char map[3][3] =    {
                            {' ', ' ', ' '}, 
                            {' ', ' ', ' '}, 
                            {' ', ' ', ' '}
                        };
    char playerSign, botSign = ' ';

    // define player's position
    int row, col = 0;

    // player & bot signs setup
    chooseSign(playerSign, botSign);

    // game loop
    if(playerSign == 'X') {
        do {
                buildMap(map);
                std::cout << std::endl;

                pickRowCol(row, col, map, playerSign);
                system("cls");
                winCheck(map, playerSign, botSign, endGame);  

                buildMap(map);
                system("pause");
                system("cls");

                if(endGame == true) break;

                botPick(row, col, map, botSign);
                winCheck(map, playerSign, botSign, endGame);  

                buildMap(map);
                system("pause");
                system("cls");

        } while(!endGame);
    } else {
        do {
                // bot starts first
                botPick(row, col, map, botSign);
                winCheck(map, playerSign, botSign, endGame);  

                buildMap(map);
                std::cout << std::endl;

                if(endGame == true) {
                    system("pause");
                    break;   
                }

                // then player starts
                pickRowCol(row, col, map, playerSign);
                system("cls");
                winCheck(map, playerSign, botSign, endGame);  

                buildMap(map);
                system("pause");
                system("cls");
        } while(!endGame);
    }

    return 0;
}

// function that return player and bot signs
char chooseSign(char &playerSign, char &botSign) {

    bool leaveLoop = false;

    do {
        std::cout << "Choose your sign (x/o): ";
        std::cin >> playerSign;
        playerSign = toupper(playerSign);


        switch (playerSign) {
        case 'X':
            botSign = 'O';
            leaveLoop = true;
            system("cls");
            break;
        case 'O':
            botSign = 'X';
            leaveLoop = true;
            system("cls");
            break;
        default:
            std::cout << "Please enter only 'x' or 'y' signs!" << std::endl;
            leaveLoop = false;
            break;
        }
    } while(!leaveLoop);

    return playerSign, botSign;
}

// draw map
void buildMap(char map[3][3]) {

    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << map[0][0] << "  |  " << map[0][1] << "  |  " << map[0][2] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;

    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << map[1][0] << "  |  " << map[1][1] << "  |  " << map[1][2] << "  " << std::endl;
    std::cout << "_____|_____|_____" << std::endl;

    std::cout << "     |     |     " << std::endl;
    std::cout << "  " << map[2][0] << "  |  " << map[2][1] << "  |  " << map[2][2] << "  " << std::endl;
    std::cout << "     |     |     " << std::endl;
}

// pick row and col in tab
void pickRowCol(int &row, int &col, char map[3][3], char playerSign) {

    bool correctChoice = false;

    do {
            std::cout << "Pick a row: ";
            std::cin >> row;
            std::cout << "Pick a column: ";
            std::cin >> col;

            if(row <= 3 && row >= 1 && col <= 3 && col >= 1) {
                correctChoice = true;
            } else {
                std::cout << std::endl;
                std::cout << "Row and Column has to be between 1-3 values!" << std::endl;
                system("pause");
                system("cls");
                buildMap(map);
                correctChoice = false;
            }

    } while(!correctChoice);


    if(map[row-1][col-1] == ' ') {
        map[row-1][col-1] = playerSign;
    } else {
        std::cout << "This position is not permitted! \n Pick a position with no sign!" << std::endl;
        system("pause");
        system("cls");
    }
}

// bot pick generator
void botPick(int &row, int &col, char map[3][3], char botSign) {

    bool lotteryDone = false;

    do {
            srand(time(NULL));
            row = rand() % 3;
            col = rand() % 3;
            if(map[row][col] == ' ') {
                map[row][col] = botSign;
                lotteryDone = true;
            } else {
                lotteryDone = false;
            }
    } while(!lotteryDone);
}

// function that check is it a win/loose/draw
void winCheck(char map[3][3], char playerSign, char botSign, bool &gameover) {

    // ----------------------------------------------------------------------------------------
    // ========================================================================================
    // ----------------------------------------------------------------------------------------

    // ---- Player Won ----
    for(int i = 0; i < 3; i++) {
        if(map[i][0] == playerSign && map[i][1] == playerSign && map[i][2] == playerSign) {
            system("cls");
            std::cout << std::endl;
            std::cout << " --> You Win! <--" << std::endl;
            std::cout << std::endl;
            gameover = true;
        }
        if(map[0][i] == playerSign && map[1][i] == playerSign && map[2][i] == playerSign) {
            system("cls");
            std::cout << std::endl;
            std::cout << " --> You Win! <--" << std::endl;
            std::cout << std::endl;
            gameover = true;
        }
    }

    if(map[0][0] == playerSign && map[1][1] == playerSign && map[2][2] == playerSign) {
        system("cls");
        std::cout << std::endl;
        std::cout << " --> You Win! <--" << std::endl;
        std::cout << std::endl;
        gameover = true;
    }
    if(map[0][2] == playerSign && map[1][1] == playerSign && map[2][0] == playerSign) {
        system("cls");
        std::cout << std::endl;
        std::cout << " --> You Win! <--" << std::endl;
        std::cout << std::endl;
        gameover = true;
    }

    // ----------------------------------------------------------------------------------------
    // ========================================================================================
    // ----------------------------------------------------------------------------------------

    // ---- Bot Won ----
    for(int i = 0; i < 3; i++) {
        if(map[i][0] == botSign && map[i][1] == botSign && map[i][2] == botSign) {
            system("cls");
            std::cout << std::endl;
            std::cout << " --> Game Over! You loose! <--" << std::endl;
            std::cout << std::endl;
            gameover = true;
        }
        if(map[0][i] == botSign && map[1][i] == botSign && map[2][i] == botSign) {
            system("cls");
            std::cout << std::endl;
            std::cout << " --> Game Over! You loose! <--" << std::endl;
            std::cout << std::endl;
            gameover = true;
        }
    }

    if(map[0][0] == botSign && map[1][1] == botSign && map[2][2] == botSign) {
        system("cls");
        std::cout << std::endl;
        std::cout << " --> Game Over! You loose! <--" << std::endl;
        std::cout << std::endl;
        gameover = true;
    }
    if(map[0][2] == botSign && map[1][1] == botSign && map[2][0] == botSign) {
        system("cls");
        std::cout << std::endl;
        std::cout << " --> Game Over! You loose! <--" << std::endl;
        std::cout << std::endl;
        gameover = true;
    }

    // ----------------------------------------------------------------------------------------
    // ========================================================================================
    // ----------------------------------------------------------------------------------------

    // ---- Draw ----

    if(gameover == false) {
        int drawcounter = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(map[i][j] != ' ') {
                    drawcounter++;
                }
                if(drawcounter == 9) {
                    system("cls");
                    std::cout << std::endl;
                    std::cout << " --> Game Over! It's a draw! <--" << std::endl;
                    std::cout << std::endl;
                    gameover = true;
                }
            }
        }
    }
}
