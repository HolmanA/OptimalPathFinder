# Program Description
This program is a classic Q-Learning virtual bot. Using a Q-Learning algorithm, it is able to determine the optimal route from the home state, to any user-specified state, and back to the home state.
This program was written in C++ on a Linux machine and is intended to be run in a Linux environment.
A more in-depth report on this program including references can be found in the file:
	report.md

## How to compile
You must first change directories to 'src' in order to compile the program.
To compile the program, simply use the included makefile and execute the command:

	make

## Program execution
You must first change directories to 'src' in order to execute the program.
To run the program, execute the command:

	./qBot
The program will train until the Q-Table converges before prompting for user input. By default training output data is not printed.
To print training data while the program trains, execute the command:

    ./qBot -t
The '-t' flag tells the program to print training info. This is the command executed for the output script found in '/out/OUTPUT_FILE'.

## Program output
The program will initially print information obtained from parsing the room adjacency list file along with some hyper-parameters.
The program then alerts the user where it will be storing matrix weights.
Next, the program begins training. If the program was run using the '-t' flag, some training data will be displayed each time a q-matrix value changes.
This training data includes which iteration and epoch the program is on, the to and from room numbers, and the old and new q values.
If the program was run without this flag, the program will output no information while training.
Upon the completion of training, the program displays a table of room numbers and their corresponding index along with the help dialog.
When an optimal route from the home room to another room is requested, the program will list the optimal route to the goal room and back home.
A sample of the program's output sequence can be found under:
	out/OUTPUT_FILE
Initial Q and R weights are stored in '.out' files within the 'out' directory. At the end of each training iteration, Q-values are stored in a new file within the 'out' directory.

## Notes
Due to the way I have decided to store and parse initial room data, the indexes of the Q and R matricies are swapped. Usually 2d arrays have the form X[from][to], however for this project, the Q and R matrices have the form X[to][from].
