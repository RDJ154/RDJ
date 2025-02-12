Snake Game

1. Introduction :

   This document provides detailed documentation for the Snake Game imple- mented in C++. The game follows classic snake mechanics where the         player controls a snake that moves around the screen, eats food, and grows in length. The objective is to achieve the highest possible score      while avoiding collisions with the walls and the snake’s own body.

2. Game Features :

   (i) Classic snake movement controlled via keyboard (WASD keys).
   (ii) Food appears randomly on the board, and consuming it increases the snake’s length.
   (iii) Collision detection with the walls and the snake’s own body. Score tracking.
   (iv) Restart and Quit options after game over.
   (v) Color-coded display using console attributes.
   (vi) A linked list-based approach to manage the snake’s body. Adjustable game speed.
   (vii) Simple but effective ASCII-based game rendering.

3. Code Structure :

   The game is structured using the following classes:
   
3.1 Node : 

  Represents a single segment of the snake. • Stores x and y coordinates.
   
   • Stores x and y coordinates.
   • Pointer to the next node.

3.2 Direction : 

  Stores movement direction as x and y offsets.

  • Used to determine the next position of the snake. 
  • Updated based on user input.

3.3 Snake : 

  Manages the snake’s movement and growth.
  
  • Head and tail tracking.
  • Movement logic by shifting positions in the linked list. • Collision detection with boundaries and self.
  • Adding tail segments when food is consumed.

3.4 Food : 

  Handles food generation at random positions.
  
  • Randomly places food within the game grid.
  • Ensures that food does not appear on the snake’s body.
  
3.5 Game Board :  

  Manages the game rendering and logic.
  
  • Displays the board with the snake and food.
  • Handles score tracking and game-over conditions.
  • Uses system calls for clearing and updating the console display.

4. How to Play

   1. Use ’W’ to move up, ’A’ to move left, ’S’ to move down, and ’D’ to move right.
   2. Eat food (’F’) to increase the snake’s length and score.
   3. Avoid colliding with the walls and yourself.
   4. Press ’X’ to exit the game.
   5. After game over, press ’R’ to restart or ’Q’ to quit.

5. Code Implementation

5.1 Main Function

The entry point of the game, responsible for initializing game objects and han- dling the game loop.

Listing 1: Main function implementation

int main() { 
      char choice;
      do {
        Snake snake;
        Food food;
        GameBoard game;
        snake.head->x = game.width / 2; 
        snake.head->y = game.height / 2; 
        food.Generate(game.width, game.height); 
        while (!game.gameOver) {
            game.Draw(snake, food); 
            if (_kbhit()) {
                  switch (_getch()) {
                  case ’a’: snake.dir = {-1, 0}; break; 
                  case ’d’: snake.dir = {1, 0}; break; 
                  case ’w’: snake.dir = {0, -1}; break; 
                  case ’s’: snake.dir = {0, 1}; break; 
                  case ’x’: game.gameOver = true; break;
                  } 
            }
            snake.Move();
            if (snake.Collided(game.width, game.height))
                      game.gameOver = true;
            if (snake.head->x == food.x && snake.head->y == food.y) {
                      game.score += 10; 
                      food.Generate(game.width, game.height); 
                      snake.AddTail();
            }
            Sleep (100);
        }
        std::cout << "Game␣Over!␣Final␣Score:␣" << game.score << std::endl; 
        std::cout << "Press␣’R’␣to␣restart␣or␣’Q’␣to␣quit:␣";
        std::cin >> choice;
} while (choice == ’R’ || choice == ’r’);
return 0; 

6. Compilation and Execution

    To compile the program, use a C++ compiler like g++:
    g++ snake_game.cpp -o snake_game
    Run the executable:
    ./snake_game

7. Possible Improvements

  1. Implementing a graphical user interface (GUI) instead of console-based rendering.
  2. Adding different difficulty levels.
  3. Introducing obstacles on the board.
  4. Implementing a pause and resume functionality.
  5. Multiplayer mode.
  6. Saving high scores.

8. License

   This project is licensed under the MIT License - see the LICENSE file for details.

9. Modification and Contributions

    Modifications and improvements are encouraged! Feel free to fork the repository, make       changes, and submit a pull request.
