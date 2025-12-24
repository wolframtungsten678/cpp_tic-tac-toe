#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// structs
struct Board
{
    char slots[9];
    int turns;

    Board(char array[])
    {
        for (int j = 0; j < 9; j++)
        {
            slots[j] = array[j];
        }
        turns = 1;
    }
    Board()
    {
        fill_n(slots, 9, '\0');
        turns = 1;
    }
};

// function prototypes
void drawBoard(Board board);
void updateBoard(int move, int player, Board &board);
void checkBoardStatus(bool &gameState, Board board);
void endGame(int &player, Board board, bool gameState);

int main()
{
    Board board;
    int player = 1;
    bool gameState = false;
    char numberedBoard[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    Board exampleBoard(numberedBoard);

    // game intro
    string longDivider(67, '-');
    cout << longDivider << endl;
    cout << setw(39) << "TIC TAC TOE" << endl;
    cout << longDivider << endl;
    cout << "Player 1 is X and player 2 is O. Try to get three in a row!" << endl;
    cout << "Refer to this example board to select your space." << endl
         << endl;
    drawBoard(exampleBoard);
    cout << endl;
    cout << longDivider << endl;

    // player turns
    while (board.turns < 10)
    {
        int move = 0;

        cout << "Player " << player << "'s move. " << endl;
        cout << "Enter a space number to make your move: ";
        cin >> move;
        cout << endl;
        if ((move > 9) || move < 0)
        {
            cout << "Invalid move. Please enter a valid space for your move: " << endl;
            cout << "Enter a space number to make your move: ";
            cin >> move;
            cout << endl;
        }
        updateBoard(move, player, board);
        cout << endl;
        drawBoard(board);
        cout << endl;
        checkBoardStatus(gameState, board);
        if (gameState || (board.turns == 10))
        {
            endGame(player, board, gameState);
        }

        // determine next player #
        if (board.turns % 2)
        {
            player = 1;
        }
        else
        {
            player = 2;
        }
        cout << longDivider << endl;
    }

    return 0;
}

void drawBoard(Board board)
{
    string divider(11, '-');
    string padding(28, ' ');

    for (int i = 0; i < 9; i++)
    {
        if ((i == 3) | (i == 6))
        {
            cout << setw(39) << divider << endl;
        }

        if ((i == 0) || (i == 3) || (i == 6))
        {
            cout << padding;
        }

        if (board.slots[i] != '\0')
        {
            cout << " " << board.slots[i] << " ";
        }
        else
        {
            cout << "   ";
        }

        if ((i + 1) % 3 != 0)
        {
            cout << "|";
        }
        else
        {
            cout << endl;
        }
    }
}

void updateBoard(int move, int player, Board &board)
{
    if (board.slots[move - 1] == '\0')
    {
        switch (player)
        {
        case 1:
            board.slots[move - 1] = 'X';
            board.turns += 1;
            break;
        case 2:
            board.slots[move - 1] = 'O';
            board.turns += 1;
            break;
        default:
            cout << "Error--unrecognized player.";
            break;
        }
    }
    else
    {
        cout << "Invalid move. Please enter a valid space for your move: " << endl;
    }
}

void checkBoardStatus(bool &gameState, Board board)
{

    bool row_1 = ((board.slots[0] == board.slots[1]) && (board.slots[1] == board.slots[2])) && ((board.slots[0] == 'X') || (board.slots[0] == 'O'));
    bool row_2 = ((board.slots[3] == board.slots[4]) && (board.slots[4] == board.slots[5])) && ((board.slots[3] == 'X') || (board.slots[3] == 'O'));
    bool row_3 = ((board.slots[6] == board.slots[7]) && (board.slots[7] == board.slots[8])) && ((board.slots[6] == 'X') || (board.slots[6] == 'O'));
    bool col_1 = ((board.slots[0] == board.slots[3]) && (board.slots[3] == board.slots[6])) && ((board.slots[0] == 'X') || (board.slots[0] == 'O'));
    bool col_2 = ((board.slots[1] == board.slots[4]) && (board.slots[4] == board.slots[7])) && ((board.slots[1] == 'X') || (board.slots[1] == 'O'));
    bool col_3 = ((board.slots[2] == board.slots[5]) && (board.slots[5] == board.slots[8])) && ((board.slots[2] == 'X') || (board.slots[2] == 'O'));
    bool diag_1 = ((board.slots[0] == board.slots[4]) && (board.slots[4] == board.slots[8])) && ((board.slots[0] == 'X') || (board.slots[0] == 'O'));
    bool diag_2 = ((board.slots[2] == board.slots[4]) && (board.slots[4] == board.slots[6])) && ((board.slots[2] == 'X') || (board.slots[2] == 'O'));

    if (row_1 || row_2 || row_3 || col_1 || col_2 || col_3 || diag_1 || diag_2)
    {
        gameState = true;
    }
}

void endGame(int &player, Board board, bool gameState)
{
    char anotherGame;

    cout << "Game over!" << endl;

    if (gameState)
    {
        cout << "Player " << player << " wins!" << endl;
    }
    else
    {
        cout << "It's a tie!" << endl;
    }

    cout << endl
         << "Play again? (Y/N): ";
    cin >> anotherGame;

    if (anotherGame == 'Y')
    {
        for (int k = 0; k < 9; k++)
        {
            board.slots[k] = '\0';
        }
        player = 2;
        board.turns = 1;
        cout << endl
             << endl;
        drawBoard(board);
    }
    else
    {
        exit(0);
    }
}