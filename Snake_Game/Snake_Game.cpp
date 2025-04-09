#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h> // For Sleep() function
#include <conio.h>

class SnakeGame {
private:
    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score;
    std::vector<int> tailX, tailY;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    void Setup() {
        srand(time(nullptr)); // Seed random number generator
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        tailX.clear();
        tailY.clear();
    }

    void Draw() {
        system("cls"); // Use cls
        
        // Top wall
        for (int i = 0; i < width+2; i++)
            std::cout << "#";
        std::cout << std::endl;

        // Game area
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    std::cout << "#";
                
                // Snake head
                if (i == y && j == x)
                    std::cout << "O";
                
                // Fruit
                else if (i == fruitY && j == fruitX)
                    std::cout << "*";
                
                // Snake tail
                else {
                    bool printTail = false;
                    for (size_t k = 0; k < tailX.size(); k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            std::cout << "o";
                            printTail = true;
                            break;
                        }
                    }
                    
                    if (!printTail)
                        std::cout << " ";
                }
                
                if (j == width - 1)
                    std::cout << "#";
            }
            std::cout << std::endl;
        }

        // Bottom wall
        for (int i = 0; i < width+2; i++)
            std::cout << "#";
        std::cout << std::endl;

        // Score display
        std::cout << "Score: " << score << std::endl;
        std::cout << "Use WASD to move, X to quit" << std::endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    if (dir != RIGHT) dir = LEFT;
                    break;
                case 'd':
                    if (dir != LEFT) dir = RIGHT;
                    break;
                case 'w':
                    if (dir != DOWN) dir = UP;
                    break;
                case 's':
                    if (dir != UP) dir = DOWN;
                    break;
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }

    void Logic() {
        // Move tail segments
        if (!tailX.empty()) {
            tailX.insert(tailX.begin(), x);
            tailY.insert(tailY.begin(), y);
            
            // Remove last tail segment if not growing
            if (tailX.size() > static_cast<size_t>(score / 10)) {
                tailX.pop_back();
                tailY.pop_back();
            }
        }
        
        // Move snake head
        switch (dir) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }

        // Boundary collision - Game Over
        if (x >= width || x < 0 || y >= height || y < 0) {
            gameOver = true;
            return;
        }

        // Tail collision
        for (size_t i = 0; i < tailX.size(); i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        // Fruit eating
        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
    }

public:
    void Run() {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            
            Sleep(200); // Sleep for 200 milliseconds
        }
        std::cout << "Game Over! Final Score: " << score << std::endl;
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}