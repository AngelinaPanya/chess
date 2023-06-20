#include <cstdlib>
#include <fstream>
#include <limits.h>

#include "../state/state.hpp"
#include "./random.hpp"
//std::ofstream fout("randomPol.txt", std::ios::app);

static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Random::get_move(State *state, int depth){
  if(!state->player){
  int best = INT_MIN;
  Move best_move(Point(-1,-1),Point(-1,-1));
  state->get_legal_actions();
  for (auto temps : state->legal_actions){
    int num = minimax(state->next_state(temps),5,false,INT_MIN,INT_MAX);
    if(num > best){
      best = num;
      best_move = temps;
    }
  }
  return best_move;
  }
  else{
    int best_min=INT_MAX;
    Move best_move(Point(-1,-1),Point(-1,-1));
    state->get_legal_actions();
    for (auto temps : state->legal_actions){
    int num = minimax(state->next_state(temps),5,true,INT_MIN,INT_MAX);
    if(num < best_min){
      best_min = num;
      best_move = temps;
    }
  }
  return best_move;
  }
}

int Random :: minimax(State *state,int depth, bool Max_player,int alpha,int beta){
  int evall;
  if(depth<=0 || state->game_state == WIN || state->game_state == DRAW){
    return state->evaluate();
  }
  if(Max_player){
    int Maxi=INT_MIN;
    for (auto child : state->legal_actions){
        evall=minimax(state->next_state(child),depth-1,false, alpha,beta);
        Maxi=std::max(Maxi,evall);
        alpha= std::max(alpha,Maxi);
        if (beta<=alpha) break;
    }
    return Maxi;
  }
  else {
    int MINI=INT_MAX;
    for (auto child : state->legal_actions){
        evall=minimax(state->next_state(child),depth-1,true,alpha,beta);
        MINI=std::min(MINI,evall);
        beta=std::min(beta,MINI);
        if (beta<=alpha) break;
    }
    return MINI;
  }
}