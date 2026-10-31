#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
class Snake {
private:
	std::vector<sf::Vector2i> body;
	sf::Vector2i direction;
	bool grow = false;
public:
	Snake() {
		direction = { 1,0 };
		body.push_back({ 3,5 });
		body.push_back({ 4,5 });
		body.push_back({ 5,5 });

	}
	void setDirection(sf::Vector2i newDir) {
		direction = newDir;
	}
	sf::Vector2i getDirection() {
		return direction;
	}
	void grows() {
		grow = true;

	}
	void move() {
		sf::Vector2i newHead = body.back() + direction;
		body.push_back(newHead);
		if (!grow) {
			body.erase(body.begin());
		}
		else {
			grow = false;
		}



	}
	int getLenght() {
		return body.size();
	}
	bool сheckCollision() {
		if (body.size() <= 2) return false;
		sf::Vector2i head = body.back();
		for (int i = 0; i <= body.size() - 2; i++) {
			if (body[i] == head) {
				return true;
			}
		}
		return false;

	}
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < body.size(); i++) {
			sf::RectangleShape rect(sf::Vector2f(30.f, 30.f));
			rect.setFillColor(sf::Color::Blue);
			rect.setPosition(sf::Vector2f(body[i].x * 30.f, body[i].y * 30.f));

			window.draw(rect);
		}


	}
	sf::Vector2i getHeadPos() {
		return body.back();

	}

};
class Food {
private:
	sf::Vector2i possition;


public:
	void respawn() {
		possition.x = rand() % 20;
		possition.y = rand() % 20;



	}
	void draw(sf::RenderWindow& window) {
		sf::RectangleShape rect(sf::Vector2f(30.f, 30.f));
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(sf::Vector2f(possition.x * 30.f, possition.y * 30.f));
		window.draw(rect);



	}
	sf::Vector2i getPossition() {
		return possition;
	}
};
class Game {
private:
	sf::RenderWindow window;
	Snake snake;
	Food food;
	int score = 0;
	sf::Clock clock;
	bool isGameOver = false;
	bool isWin = false;
public:

	Game() : window(sf::VideoMode({ 600 , 600 }), "Snake"), score(0) {

		srand(time(0));
		food.respawn();
	}
	

	void run() {
		while (window.isOpen()) {
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();

				}
				if (isGameOver == true) {

					window.close();
				}
					if (isWin == true) {

						window.close();
					
				}


			}
			input();
			render();


			update();
		}

	}

	void input() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			if (snake.getDirection() != sf::Vector2i(0, 1))
				snake.setDirection({ 0, -1 });



		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			if (snake.getDirection() != sf::Vector2i(0, -1))
				snake.setDirection({ 0 , 1 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			if (snake.getDirection() != sf::Vector2i(1, 0))
				snake.setDirection({ -1 , 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			if (snake.getDirection() != sf::Vector2i(-1, 0))
				snake.setDirection({ 1, 0 });
		}

	}
	void update() {
		if (isGameOver) return;
		if (isWin) return;
		if (clock.getElapsedTime().asSeconds() > 0.23f) {
			snake.move();



			if (snake.getLenght() >= 400) {
				isWin = true;
				std::cout << "Win" << "Счет: " << score << "\n";
				return;
			}
			sf::Vector2i head = snake.getHeadPos();
			if (head.x < 0 || head.x >= 20 || head.y < 0 || head.y >= 20) {
				isGameOver = true;
				std::cout << "Game over" << "Счет: " << score << "\n";
				return;
			}
			if (snake.сheckCollision()) {
				isGameOver = true;
				std::cout << "Game over" << "Счет: " << score << "\n";
				return;
			}
			if (snake.getHeadPos() == food.getPossition()) {
				score++;
				food.respawn();
				snake.grows();

			}
			clock.restart();
		}


	}
	void render() {
		window.clear(sf::Color::Red);
		sf::RectangleShape cell({ 30.f , 30.f });
		cell.setFillColor(sf::Color::Black);
		cell.setOutlineThickness(1.f);
		cell.setOutlineColor(sf::Color::Yellow);
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				cell.setPosition({ x * 30.f, y * 30.f });
				cell.setFillColor(sf::Color::Green);
				window.draw(cell);
			}
		}

		snake.draw(window);
		food.draw(window);
		window.display();

	}
};


int main() {

	Game game;
	game.run();
	return 0;
}