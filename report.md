## Approach
The goal for this project was to develop a program capable of identifying the optimal route from room 441 on the CF Building 4th floor to any other room on the 4th floor and back to 441.
In order to accomplish this task, I implemented a classic Q-Learning algorithm.
Through trial and error, the program is able to slowly learn optimal paths through the connected rooms.
This Q-Learning algorithm is based loosely off of [1].

## Difficulties
One particular difficulty I ran into with this project was determining when the Q-Matrix has converged.
The example found in [1] runs for a set number of iterations rather than to convergence, so I had to come up with my own definition of convergence.
I chose to consider the Q-Matrix converged if the program was able to successfully train for an entire iteration without any Q-Matrix values changing.
With this convergence definition and a gamma parameter of 0.9, the program usually converges within 3-4 training iterations.

## Interesting Findings
An interesting behavior I noticed while training the program is that the random selection of rooms can sometimes lead to training loops.
What I mean by "training loops" is that the program will sometimes switch between two states repeatedly.
It might choose to go from state 1 to state 2, back to 1, back to 2, etc.
Since action selection is random, this training loop does eventually terminate as the program randomly selects a third state, however this loop slows training significantly.
A potential solution to this problem could be to have a flag that an action has already been taken.
An alternative solution could be to use some sort of timeout, where the program will restart the epoch if it is taking longer than the timeout.
I have a feeling however that this second solution would not be ideal as it seems to be more of a work-around than an actual solution.

## Special Features
One special feature incorporated into my program is the ability to easily test all rooms in the system through one command:

    all
Another special feature is the ability to easily use the program with different floor layouts.
By using an adjacency list to hold rooms and their adjacent rooms, the program can easily adapt to new datasets.
Defining a new adjacency list for a new building is all that is needed to use the program on another floor plan.

## References
[1] John McCullock, "Q-Learning.*", A Painless Q-Learning Tutorial,
    http://mnemstudio.org/path-finding-q-learning-tutorial.htm
