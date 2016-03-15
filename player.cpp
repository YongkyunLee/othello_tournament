#include "player.h"
#include "limits.h"
#include <unistd.h>

#define SIZE 8
#define DEPTH 5

/* Change:
Github repository created
Team Name: Solo
Member: Yongkyun Lee
*/

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = new Board();

    /*
    // testminimax
    char boardData[64] = {
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', 
        'b', 'w', 'b', 'b', 'b', 'b', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    board->setBoard(boardData);
    // to be erased if not testminimax
    */

    my_side = side;
    if (my_side == BLACK) {
        opp_side = WHITE;
    }
    else {
        opp_side = BLACK;
    }

    //need to take an initial move if black

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */

/*
 * Updated using alphabeta pruning
 */
int Player::minimax(Board *node, int depth, int alpha, int beta, bool max_player) {
    int best_score, curr_score, it;
    std::vector<Move *> pos_move;
    // helper to take care of sides
    Side curr_side;
    if (DEPTH % 2 == 1) {
        (depth % 2 == 1) ? curr_side = my_side : curr_side = opp_side;
    }
    else {
        (depth % 2 == 0) ? curr_side = my_side : curr_side = opp_side;
    }

    if (depth == 0 || !node->hasMoves(curr_side)) { // depth is 0 or the current board has no more possible moves
        return node->countScore(my_side);
    }

    if (max_player == true) {
        best_score = INT_MIN;
        node->allmoves(pos_move, my_side); // store all the possible movements in pos_move vector
        for (int i = 0; i < (int)pos_move.size(); i++) {
            Board *temp = node->copy();
            temp->doMove(pos_move[i], my_side); // move
            curr_score = minimax(temp, depth - 1, alpha, beta, false);
            if (curr_score > best_score) {
                best_score = curr_score;
                it = i;
            }
            if (best_score < alpha) {
                alpha = best_score;
            }
            if (beta <= alpha) {
                break;
            }
            delete temp;
        }
        if (depth == DEPTH) { // if the decided best score is from the choices of the move that needs to be made
            next_move = new Move(pos_move[it]->getX(), pos_move[it]->getY());
        }

        return best_score;
    }
    else { // min player
        best_score = INT_MAX;
        node->allmoves(pos_move, opp_side);
        for (int i = 0; i < (int)pos_move.size(); i++) {
            Board *temp = node->copy();
            temp->doMove(pos_move[i], opp_side); // move
            curr_score = minimax(temp, depth - 1, alpha, beta, false);
            if (curr_score < best_score) {
                best_score = curr_score;
            }
            if (best_score > beta) {
                beta = best_score;
            }
            if (beta <= alpha) {
                break;
            }
            delete temp;
        }
        return best_score;
    }

}

/*
 * Working AI and Basic implementation of heuristic function are commented out
*/
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // process opponent's move
    board->doMove(opponentsMove, opp_side);

    
    // "Working" AI
    /*
    // make the left-top most move
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Move *my_move = new Move(i, j);
            if (board->checkMove(my_move, my_side)) {
                board->doMove(my_move, my_side);
                return my_move;
            }
            else {
                delete my_move;
            }
        }
    }
    return NULL;
    */

    // Simple Player
    /*
    // go through all the squares and check if they have possible moves
    // then copy board and simulate the move and check the score
    int curr_score, best_score = INT_MIN;
    int count = 0;
    Move *current = new Move(0, 0);
    Move *best = new Move(0, 0);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            current->setX(i);
            current->setY(j);
            if (board->checkMove(current, my_side)) {
                count++;
                Board *temp = board->copy();
                temp->doMove(current, my_side);
                curr_score = temp->countScore(my_side);
                if (curr_score > best_score) {
                    best_score = curr_score;
                    best->setX(current->getX());
                    best->setY(current->getY());
                }
                delete temp;
            }
        }
    }
    delete current;
    if (count == 0) {
        return NULL;
    }
    else {
        board->doMove(best, my_side);
        return best;
    }
    */

    // Minimax Algorithm

    // use helper function: Player::minimax
    // the best move at current state is saved at variable next_move
    if (!board->hasMoves(my_side)) {
        return NULL;
    }
    minimax(board, DEPTH, INT_MIN, INT_MAX, true);
    board->doMove(next_move, my_side);
    return next_move;
}
