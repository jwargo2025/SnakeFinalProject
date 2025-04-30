#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;

class Snake {
    private:
        COORD position;
        int snakeLen;
        char direction;

    public:
        Snake(COORD startPos);
        void changeDirection(char newDirection);
        void move();
        COORD getPosition();
        bool eatFruit(COORD fruitPos);
};

Snake::Snake(COORD startPos) {
    position = startPos;
    snakeLen = 1;
    direction = ' ';
}

void Snake::changeDirection(char newDirection) {
    direction = newDirection;
}

void Snake::move() {
    if (direction == 's') {
        position.Y += 1;
    }
    else if (direction == 'a') {
        position.X -= 1;
    }
    else if (direction == 'w') {
        position.Y -= 1;
    }
    else if (direction == 'd') {
        position.X += 1;
    }
}

COORD Snake::getPosition() {
    return position;
}

bool Snake::eatFruit(COORD fruitPos) {
    if (fruitPos.X == position.X && fruitPos.Y == position.Y) {
        return true;
    }
    else {
        return false;
    }
}

class Fruit {
    private:
        COORD fruitPos;

    public:
        Fruit();
        void spawnFruit();
        COORD getFruitPos();
};

Fruit::Fruit() {
    spawnFruit();
}

void Fruit::spawnFruit() {
    fruitPos.X = rand() % WIDTH;
    fruitPos.Y = rand() % HEIGHT;
}

COORD Fruit::getFruitPos() {
    return fruitPos;
}

Snake snake({WIDTH / 2, HEIGHT / 2});
Fruit fruit();

void board() {
    COORD snakePosition = snake.getPosition();

    for (int i = 0; i < HEIGHT; ++i) {
        cout << "#";
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1) {
                cout << "#";
            }
            else if (i == snakePosition.Y && j == snakePosition.X) {
                cout << "0";
            }
            else {
                cout << " ";
            }
        }
        cout << "#" << endl;
    }

}

int main()
{
    while (true) {
        board();

        if (_kbhit()) {
            char newDirection = _getch();
            snake.changeDirection(newDirection);
        }

        snake.move();

        if (snake.eatFruit(fruit.getFruitPos())) {
            fruit.spawnFruit();
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }

    return 0;
}
