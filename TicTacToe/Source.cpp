#include <SFML/Graphics.hpp>
#include <vector>

struct mouseFunc {
	mouseFunc(bool isPressed,int pos) : isPressed(isPressed), pos(pos){
	}
	bool isPressed;
	int pos;

};

using namespace sf;

//function prototypes
void drawLines(RenderWindow &window);
Vector2f returnPos(int i);
mouseFunc checkMouseInput(Mouse mouse, RenderWindow &window);
int checkWin(std::vector<int> cells);



int main() {
	
	RenderWindow window;
	window.create(VideoMode(600, 600), "TicTacToe");

	Event event;
	Mouse mouse;
	
	//load textures
	Texture t1, t2, win1, win2;
	Sprite s1, s2, winC,winK;

	//cross
	t1.loadFromFile("sprites/cross.png");
	s1.setTexture(t1);

	//circle
	t2.loadFromFile("sprites/circle.png");
	s2.setTexture(t2);

	win1.loadFromFile("sprites/crossWins.png");
	win2.loadFromFile("sprites/circleWins.png");

	winC.setTexture(win1);
	winK.setTexture(win2);
	//arrays n stuff
	// 0 -empty, 1 - cross, 2- circle
	std::vector<int> cells = { 0,0,0,0,0,0,0,0,0 };

	bool crossTurn = true;
	bool winDisplay = false;
	int winner = 0;
	//Game loop
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				cells.clear();
				cells = { 0,0,0,0,0,0,0,0,0 };
				winDisplay = false;
				crossTurn = true;
			}
		}

		winner = checkWin(cells);

		if (winner == 0) {
			mouseFunc temp = checkMouseInput(mouse, window);
			if (temp.isPressed == true) {
				if (cells[temp.pos] == 0) {
					if (crossTurn) {
						cells[temp.pos] = 1;
						crossTurn = false;
					}
					else if (!crossTurn) {
						cells[temp.pos] = 2;
						crossTurn = true;
					}
				}
			}
		}
		
		window.clear(Color::White);
		//----------------------------------
		drawLines(window);
		//draw in accordance with the array
		for (std::size_t i = 0; i < cells.size(); ++i) {
			if (cells[i] == 1) {
				s1.setPosition(returnPos((int)i));
				window.draw(s1);
			}
			if (cells[i] == 2) {
				s2.setPosition(returnPos((int)i));
				window.draw(s2);
			}

		}
		if (winner == 1) {
			winC.setPosition(150, 150);
			window.draw(winC);
		}
		else if (winner == 2) {
			winK.setPosition(150, 150);
			window.draw(winK);
		}
		//----------------------------------
		window.display();

	}

	return 0;
}

void drawLines(RenderWindow &window) {
	//set
	RectangleShape line(Vector2f(600.f, 2.5f));
	line.setFillColor(Color::Black);

	//draw
	line.setRotation(0.f);
	line.setPosition(0.f, 200.f);
	window.draw(line);

	line.setPosition(0.f, 400.f);
	window.draw(line);

	line.setRotation(90.f);
	line.setPosition(200.f, 0.f);
	window.draw(line);

	line.setPosition(400.f, 0.f);
	window.draw(line);

}

Vector2f returnPos(int i) {
	//do it the stupid way
	if (i == 0) return Vector2f(20.f, 20.f);
	if (i == 1) return Vector2f(220.f, 20.f);
	if (i == 2) return Vector2f(420.f, 20.f); 
	if (i == 3) return Vector2f(20.f, 220.f);
	if (i == 4) return Vector2f(220.f, 220.f);
	if (i == 5) return Vector2f(420.f, 220.f);
	if (i == 6) return Vector2f(20.f, 420.f);
	if (i == 7) return Vector2f(220.f, 420.f);
	if (i == 8) return Vector2f(420.f, 420.f);
}

mouseFunc checkMouseInput(Mouse mouse,RenderWindow &window) {
	//brute force way again
	mouseFunc m(false, 0);

	if (mouse.isButtonPressed(Mouse::Left)) {
		//top row
		if (mouse.getPosition(window).y < 200) {
			if (mouse.getPosition(window).x < 200) {
				m.isPressed = true; m.pos = 0;
			}
			if (mouse.getPosition(window).x > 200 && mouse.getPosition(window).x < 400) {
				m.isPressed = true; m.pos = 1;
			}
			if(mouse.getPosition(window).x > 400){
				m.isPressed = true; m.pos = 2;
			}
		}
		//middle row
		if (mouse.getPosition().y > 200 && mouse.getPosition().y < 400) {
		if (mouse.getPosition(window).x < 200) {
				m.isPressed = true; m.pos = 3;
			}
			if (mouse.getPosition(window).x > 200 && mouse.getPosition(window).x < 400) {
				m.isPressed = true; m.pos = 4;
			}
			if(mouse.getPosition(window).x > 400){
				m.isPressed = true; m.pos = 5;
			}
		}
		//bottom row
		if (mouse.getPosition().y > 400) {
		if (mouse.getPosition(window).x < 200) {
				m.isPressed = true; m.pos = 6;
			}
			if (mouse.getPosition(window).x > 200 && mouse.getPosition(window).x < 400) {
				m.isPressed = true; m.pos = 7;
			}
			if(mouse.getPosition(window).x > 400){
				m.isPressed = true; m.pos = 8;
			}

		}
	}
	return m;
}

int checkWin(std::vector<int> cells) {
	for (int i = 1; i <= 2; i++) {
		//check for all combinations
		if (cells[0] == i && cells[1] == i && cells[2] == i) {
			return i;
		}
		if (cells[3] == i && cells[4] == i && cells[5] == i) {
			return i;
		}
		if (cells[6] == i && cells[7] == i && cells[8] == i) {
			return i;
		}
		if (cells[0] == i && cells[3] == i && cells[6] == i) {
			return i;
		}
		if (cells[1] == i && cells[4] == i && cells[7] == i) {
			return i;
		}
		if (cells[2] == i && cells[5] == i && cells[8] == i) {
			return i;
		}
		if (cells[0] == i && cells[5] == i && cells[8] == i) {
			return i;
		}
		if (cells[3] == i && cells[5] == i && cells[6] == i) {
			return i;
		}

	}
	return 0;
}