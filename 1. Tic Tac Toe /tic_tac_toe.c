#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Points {
    int user_wins;
    int comp_wins;
    int ties;
};

int level;
struct Points scores = {0, 0, 0};

void ask_level();
void print_board(char board[3][3]);
int check_win(char board[3][3], char symbol);
int check_draw(char board[3][3]);
void start_game();
void user_turn(char board[3][3]);
void comp_turn(char board[3][3]);
void fix_input(); 

int main() {
    srand(time(NULL));
    int play_again;
    
    do {
        ask_level();
        start_game();
        
        while (1) {
            printf("\nWanna play again? 1 for yes, 0 for no: ");
            
            if (scanf("%d", &play_again) != 1) {
                fix_input();
                printf("Numbers only plz!\n");
            } else if (play_again != 0 && play_again != 1) {
                printf("Invalid numbers plz enter 1 or 0\n");
            } else {
                break; // Valid input (1 or 0)
            }
        }
        
    } while (play_again == 1);
    
    printf("\nGoodbye!!!\n");
    return 0;
}

void fix_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void ask_level() {            
    while (1) {
        printf("\n    TIC TAC TOE    \n");
        printf("1. Easy Mode\n");
        printf("2. Hard Mode\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &level) != 1) {
            fix_input();
            printf("\nNumbers only plz!\n");
            continue;
        }

        if (level == 1 || level == 2) {
            break;
        } else {
            printf("\nInvalid numbers plz enter 1 or 2\n");
        }
    }
}

void print_board(char board[3][3]) {        
    printf("\n\n\n\n\n\n");
    printf("---------------------------\n");
    printf("Scores: User: %d | Comp: %d | Draws: %d\n\n", scores.user_wins, scores.comp_wins, scores.ties);
    
    for (int r = 0 ; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            printf(" %c ", board[r][c]);
            if (c < 2) {
                printf("|");
            }
        }
        if (r < 2) {
            printf("\n---+---+---\n");
        }
    }
    printf("\n\n");
}

int check_win(char board[3][3], char symbol) {              
    for (int i = 0; i < 3; i++) {
        // Checking rows and columns
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
            return 1;
        }
    }

    // Checking diagonals
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||        
        (board[2][0] == symbol && board[1][1] == symbol && board[0][2] == symbol)) {        
        return 1;
    }
    return 0;
}

int check_draw(char board[3][3]) {                
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') { 
                return 0; // empty spot
            }
        }
    }
    return 1; // board is full
}

void start_game() {                      
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };
    
    char turn = (rand() % 2 == 0) ? 'X' : 'O'; 
    print_board(board);
  
    while (1) {                                  
        if (turn == 'X') {                
            user_turn(board);                       
            print_board(board);                     
            if (check_win(board, 'X')) {                 
                scores.user_wins++;                          
                print_board(board);                      
                printf("Congrats you won!!!\n");
                break;
            }
            turn = 'O'; 
        } else {
            comp_turn(board);                          
            print_board(board);
            if (check_win(board, 'O')) {
                scores.comp_wins++;
                print_board(board);
                printf("Better luck next time\n");
                break;
            }
            turn = 'X'; 
        }

        if (check_draw(board)) {
            scores.ties++;
            print_board(board);
            printf("Draw\n");
            break;
        }
    }
}

void user_turn(char board[3][3]) {
    int r, c;
    while (1) {
        printf("\nUser turn (X).");
        
        printf("\nEnter row (1-3): ");
        if (scanf("%d", &r) != 1) {
            fix_input();
            printf("Numbers only plz!\n");
            continue;
        }
        if (r < 1 || r > 3) {
            printf("Invalid numbers plz enter 1, 2 or 3\n");
            continue;
        }

        printf("Enter col (1-3): ");
        if (scanf("%d", &c) != 1) {
            fix_input();
            printf("Numbers only plz!\n");
            continue;
        }
        if (c < 1 || c > 3) {
            printf("Invalid numbers plz enter 1, 2 or 3\n");
            continue;
        }

        r--; 
        c--; 
        
        if (board[r][c] != ' ') {
            printf("Already filled plz select another one grid\n");
            continue;
        }

        break;
    }
    
    board[r][c] = 'X';
}

void comp_turn(char board[3][3]) {
    // 1. Can comp win now
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = 'O';
                if (check_win(board, 'O')) {
                    return; 
                }
                board[r][c] = ' '; 
            }
        }
    }

    // 2. Can user win now? block the user
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = 'X';
                if (check_win(board, 'X')) {
                    board[r][c] = 'O'; 
                    return;
                }
                board[r][c] = ' '; 
            }
        }
    }

    // 3. Hard Mode
    if (level == 2) {     
        if (board[1][1] == ' ') {       
            board[1][1] = 'O';
            return;
        }

        int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
        for (int i = 0; i < 4; i++) {
            if (board[corners[i][0]][corners[i][1]] == ' ') {
                board[corners[i][0]][corners[i][1]] = 'O';
                return;
            }
        }
    }

    // 4. Take first empty spot
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = 'O';
                return;
            }
        }
    }
}
