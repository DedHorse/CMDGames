#include<iostream>
#include<vector>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

const int width = 30;
const int height = 15;

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

class snake{
	private:
		int dir = 2; //0 = up, 1 = down, 2 = left, 3 = right
		std::vector<std::vector<int>> snek = {{30/2, 15/2}, {30/2+1, 15/2}, {30/2+2, 15/2}};  //initial coordinates of snake
		int foodX = 30/2 - 5;
		int foodY = 15/2;
	public:
		int score = 0;
		bool dead = false;
		
		void draw(){
			system("cls");
			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					if(y == 0 || y == height-1 || x == 0 || x == width-1)
					{
						std::cout << '#';
					}
					else if(snakeOnThatPosition(x, y))
					{
						std::cout << 'D';
					}
					else if(x == foodX && y ==foodY)
					{
						std::cout << 'X';
					}
					else
					{
						std::cout << ' ';
					}
				}
				std::cout << "\n";
			}
			std::cout << "SCORE: " << score;
		}
		
		void takeInput(){
			if (_kbhit())
    		{
				int c;
        		switch((c = getch()))
				{
        			case KEY_UP:
            			dir = 0;
            			break;
            		case KEY_DOWN:
            			dir = 1;
						break;
        			case KEY_LEFT:
            			dir = 2;
            			break;
        			case KEY_RIGHT:
            			dir = 3;
            			break;
        			default:
            			break;
        			}
        		fflush(stdin);
			}
		}
		
		void move(){ //logic to move the snake according to input
			std::vector<int> tmp;
			switch(dir)
			{
				case 0:
					tmp = {snek[0][0], snek[0][1]-1};
					snek.insert(snek.begin(), tmp);
					snek.pop_back();
					break;
				case 3:
					tmp = {snek[0][0]+1, snek[0][1]};
					snek.insert(snek.begin(), tmp);
					snek.pop_back();
					break;
				case 1:
					tmp = {snek[0][0], snek[0][1]+1};
					snek.insert(snek.begin(), tmp);
					snek.pop_back();
					break;
				case 2:
					tmp = {snek[0][0]-1, snek[0][1]};
					snek.insert(snek.begin(), tmp);
					snek.pop_back();
					break;
			}
		}
		
		bool snakeOnThatPosition(int x, int y){ //function meant for helping draw the snake
			for(int i = 0; i < snek.size(); i++)
			{
				if(snek[i][0] == x && snek[i][1] == y)
				{
					return true;
				}
			}
			return false;
		}
		
		void checkIfDead(){
			if(snek[0][0] == 0 || snek[0][0] == width - 1 || snek[0][1] == 0 || snek[0][1] == height - 1 || ateTail())
			{
				dead = true;
			}
		}
		
		bool ateTail()
		{
			for(int i = 1; i < snek.size(); i++)
			{
				if(snek[0][0] == snek[i][0] && snek[0][1] == snek[i][1])
				{
					return true;		
				}
			}
			return false;
		}
		
		void ifOnFoodEnlarge(){
			if(snek[0][0] == foodX && snek[0][1] == foodY)
			{
				do 
				{
        			foodX = rand() % (width - 2) + 1;
        			foodY = rand() % (height - 2) + 1;

    			} while (foodX == 0 || foodX == height-1 || foodY == 0 || foodY == width-1);

				snek.push_back({snek[0][0], snek[0][1]});
				score++;
			}
		}

};

void dedsleep(int ms) {
   clock_t timeUntil;
   timeUntil = clock() + ms * CLOCKS_PER_SEC/1000;
   while (clock() < timeUntil); 
}

int main()
{
	snake Snake;
	std::cout << "Press any key to start!";
	while(!Snake.dead)
	{
		Snake.checkIfDead();
		Snake.ifOnFoodEnlarge();
		Snake.takeInput();
		Snake.move();
		Snake.draw();
		dedsleep(100);
	}
	system("cls");
	std::cout << "YOU DIED\n" << "Your score: " << Snake.score << "\n";
	return 0;
}

