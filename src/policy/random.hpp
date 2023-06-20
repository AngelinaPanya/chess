#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random{
public:
  static Move get_move(State *state, int depth);
  static int minimax(State* state,int depth, bool Max_player,int alpha,int beta);
};