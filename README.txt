1. I am working by myself.

2. To improve my AI, I tried to make a better heuristic function.
A better heuristic function here means breaking the board into more specific cases.
For example, when there is an opponent's block on the diagonal line of the board, it is not wise to put my block on
the (1, 1), (6, 1), (1, 6), (6, 6) space because the opponent can get the corner.
Like this, I tried to specify the situations to make a better working heuristic function.
Also, I implemented alpha-beta pruning alogrithm to the minimax to make it faster.