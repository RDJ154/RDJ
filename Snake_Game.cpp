#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct Node {
    int x, y;
    Node* next;
    Node(int posX, int posY)  {
        x=(posX);
        y=(posY); 
        next=(nullptr);
    }
};

struct Direction {
    int x;
    int y;
};

class Snake {
public:
    Node* head;
    int nTail;
    Direction dir;

    Snake() {
        head = new Node(0, 0);
        nTail = 2; // Initially, snake length is 3 (head + 2 tail nodes)
        dir = {1, 0}; //Initial direction of movement
        head->next = new Node(0, 0);
        head->next->next = new Node(0, 0);
    }

    void Move() {
        Node* prev = nullptr;
        Node* current = head;
        int prevX = head->x;
        int prevY = head->y;

        head->x += dir.x;
        head->y += dir.y;

        while (current != nullptr) {
            if (prev != nullptr) {
                int tempX = current->x;
                int tempY = current->y;
                current->x = prevX;
                current->y = prevY;
                prevX = tempX;
                prevY = tempY;
            }
            prev = current;
            current = current->next;
        }
    }

    void AddTail() {
        Node* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = new Node(tail->x, tail->y);
        nTail++;
    }
 
    bool Collided(int width, int height) {
        if (head->x >= width || head->x < 0 || head->y >= height || head->y < 0)
            return true;

        Node* current = head->next;
        while (current != nullptr) {
            if (current->x == head->x && current->y == head->y)
                return true;
            current = current->next;
        }
        return false;
    }
};

class Food {
public:
    int x, y;

    void Generate(int width, int height) {
        x = rand() % width;
        y = rand() % height;
    }
};

class GameBoard {
public:
    const int width = 20;
    const int height = 20;
    int score;
    bool gameOver;

    GameBoard() {
        score = 0;
        gameOver = false;
    }

    void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void Draw(Snake& snake, Food& food) {
        system("cls");
        SetColor(12); // Green color for the borders
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0){
                    SetColor(12);
                    cout << "#";
                }
                if (i == snake.head->y && j == snake.head->x) {
                    SetColor(2); // Green color for the snake's head
                    cout << "0";
                } else if (i == food.y && j == food.x) {
                    SetColor(9); // Yellow color for the food
                    cout << "F";
                } else {
                    bool print = false;
                    Node* current = snake.head->next;
                    while (current != nullptr) {
                        if (current->x == j && current->y == i) {
                            SetColor(10); // Green color for the snake's body
                            cout << "u";
                            print = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (!print) {
                        SetColor(7); // Default console color
                        cout << " ";
                    }
                }

                if (j == width - 1){
                    SetColor(12);
                    cout << "#";
                }
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
        {   
            SetColor(12);
            cout << "#";
        }
        cout << endl;
        SetColor(8); // White color for the score text
        cout << "Score: " << score << endl;
    }
};

int main() {
    char choice;
    int slp;
    cout << "Enter Khelne ki speed : ";
    cin >> slp;
    
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
                case 'a':
                    snake.dir = {-1, 0};
                    break;
                case 'd':
                    snake.dir = {1, 0};
                    break;
                case 'w':
                    snake.dir = {0, -1};
                    break;
                case 's':
                    snake.dir = {0, 1};
                    break;
                case 'x':
                    game.gameOver = true;
                    break;
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

            Sleep(slp);
        }
        cout << "Game Over! Final Score: " << game.score << endl;
        cout << "Press 'R' to restart or 'Q' to quit: ";
        cin >> choice;
    } while (choice == 'R' || choice == 'r');
    system("pause");
    return 0;
}
