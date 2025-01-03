#include <iostream>
#include <random>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 7;
const int HEIGHT = 10;

void printHappyNewYear() {
    string lines[] = {
        "  HH   HH      AAA      PPPPP   PPPPP   YY   YY         NN    NN  EEEEEEE  WW      WW      YYYY    EEEEEEE  AAA    RRRRR  ",
        "  HH   HH     A   A     PP   PP PP   PP  YY YY          NNN   NN  EE       WW      WW       YY     EE      A   A   RR   R ",
        "  HHHHHHH    AAAAAAA    PPPPP   PPPPP     YYY           NN N  NN  EEEEE    WW  WW  WW       YY     EEEEE   AAAAAAA RRRRR  ",
        "  HH   HH   AA     AA   PP      PP        YY            NN  N NN  EE       WW  WW  WW       YY     EE      AA   AA RR  RR ",
        "  HH   HH  AA       AA  PP      PP        YY            NN   NNN  EEEEEEE   WWW  WWW        YY     EEEEEEE AA   AA RR   RR"
    };

    for (const string& line : lines) {
        cout << line << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
	system("cls");
}

void output_world(char world[HEIGHT][WIDTH], char player, int playerX) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == HEIGHT - 1 && j == playerX) {
                cout << player;
            } else {
                cout << world[i][j];
            }
        }
        cout << endl;
    }
}

int main() {
    char world[HEIGHT][WIDTH];
    char player = 'P';
    char candy = 'C';
    int playerX = WIDTH / 2; 
    int candyX = -1, candyY = -1; 
    bool isLose = false;
    int score = 0;
    
	printHappyNewYear();
    int speed;
    cout << "Speed u want in milliseconds: ";
	cin >> speed;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            world[i][j] = '.';
        }
    }

    auto spawn_candy = [&]() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, WIDTH - 1);
        candyX = dis(gen);
        candyY = 0;
    };

    spawn_candy();

    while (!isLose) {
        
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i != HEIGHT - 1 || j != playerX) {
                    world[i][j] = '.';
                }
            }
        }

       
        if (candyY >= 0 && candyY < HEIGHT) {
            if (candyY == HEIGHT - 1 && candyX == playerX) {
                score++;
                spawn_candy();
            } else if (candyY == HEIGHT - 1) {
                isLose = true;
                break;
            } else {
                world[candyY][candyX] = candy;
                candyY++;
            }
        } else {
            spawn_candy();
        }

        
        system("cls");
        output_world(world, player, playerX);
        cout << "Score: " << score << endl;

        
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                ch = _getch();
                if (ch == 75 && playerX > 0) {
                    playerX--;
                } else if (ch == 77 && playerX < WIDTH - 1) {
                    playerX++;
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(speed));
    }

    system("cls");
    cout << "Game Over! Final Score: " << score << endl;
	cout << "Wanna play again? 1 for yes, other for no: ";
	int choice;
	cin >> choice;
	if (choice == 1) {
		main();
	}
    else {
        _getch();
    }
    return 0;
}
