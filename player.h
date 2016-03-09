#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
	Side my_side;
	Side opp_side;
    Board *board;
    vector<int> arr_score;
    int minimax(Board *node, int depth, bool max_player);
    Move * next_move;
};

#endif
