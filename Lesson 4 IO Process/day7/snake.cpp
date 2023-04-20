#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAP_WIDTH = 30;    // 游戏地图宽度
const int MAP_HEIGHT = 20;   // 游戏地图高度
const int SNAKE_INIT_LEN = 4;  // 蛇的初始长度
const int INIT_SPEED = 200;  // 初始速度
const char WALL_CHAR = '#';  // 墙壁字符
const char SNAKE_CHAR = 'O'; // 蛇身字符
const char FOOD_CHAR = '$';  // 食物字符
const char BLANK_CHAR = ' '; // 空白字符

int map[MAP_HEIGHT][MAP_WIDTH] = {0}; // 地图二维数组，0表示空白，1表示墙壁，2表示蛇身，3表示食物
int score = 0;  // 得分
int speed = INIT_SPEED; // 当前速度
int direction = 1;  // 蛇运动方向，1表示上，2表示下，3表示左，4表示右

struct Position {
    int x, y;
};

class Snake {
public:
    Snake(int len) {
        length = len;
        for (int i = 0; i < length; ++i) {
            body[i].x = MAP_WIDTH/2;
            body[i].y = MAP_HEIGHT/2 + i;
        }
        map[body[0].y][body[0].x] = 2;
        for (int i = 1; i < length - 1; ++i) {
            map[body[i].y][body[i].x] = 2;
        }
    }

    void move() {
        // 根据方向移动蛇头
        switch (direction) {
            case 1:
                head.y--;
                break;
            case 2:
                head.y++;
                break;
            case 3:
                head.x--;
                break;
            case 4:
                head.x++;
                break;
        }

        // 判断是否吃到食物
        if (head.x == food.x && head.y == food.y) {
            length++;
            score += 10;
            generate_food();
        }
        else {
            map[tail.y][tail.x] = 0;
            for (int i = length-1; i >= 1; --i) {
                body[i] = body[i-1];
            }
        }

        // 更新蛇身位置
        body[0] = head;
        for (int i = 0; i < length; ++i) {
            map[body[i].y][body[i].x] = 2;
        }

        // 更新蛇尾位置
        tail = body[length-1];
    }

    void change_direction(int d) {
        if ((d == 1 && direction == 2)
            || (d == 2 && direction == 1)
            || (d == 3 && direction == 4)
            || (d == 4 && direction == 3)) {
            return;
        }
        direction = d;
    }

    bool check_dead() {
        if (head.x < 0 || head.x >= MAP_WIDTH
            || head.y < 0 || head.y >= MAP_HEIGHT
            || map[head.y][head.x] == 1
            || map[head.y][head.x] == 2) {
            return true;
        }
        return false;
    }

    void generate_food() {
        srand(time(0));
        do {
            food.x = rand() % MAP_WIDTH;
            food.y = rand() % MAP_HEIGHT;
        } while (map[food.y][food.x] != 0);
        map[food.y][food.x] = 3;
    }

public:
    Position head;
    Position tail;
    Position body[MAP_HEIGHT * MAP_WIDTH];
    int length;
    Position food;
};

void init_map() {
    // 设置墙壁
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (i == 0 || i == MAP_HEIGHT-1 || j == 0 || j == MAP_WIDTH-1) {
                map[i][j] = 1;
            }
        }
    }
}
    //
