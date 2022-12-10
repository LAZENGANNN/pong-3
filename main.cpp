#include "settings.h"
using namespace sf;

int main()
{
	srand(time(nullptr));
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);

	//создание объектов игры
	//ракетки
	RectangleShape leftBat, rightBat;
	leftBat.setSize(batSize);
	rightBat.setSize(batSize);
	leftBat.setFillColor(leftBatColor);
	rightBat.setFillColor(rightBatColor);
	leftBat.setPosition(batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	rightBat.setPosition(WINDOW_WIDTH - batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	float leftBatSpeedY = 0.f;
	float rightBatSpeedY = 0.f;
	//шарик
	CircleShape ball(ballRadius);
	ball.setFillColor(ballColor);
	ball.setPosition((WINDOW_WIDTH - 2 * ballRadius) / 2,
		(WINDOW_HEIGHT - 2 * ballRadius) / 2);

	float arr_speed[]{ -5.f, -4.f, -3.f, -2.f, -1.f, 1.f, 2.f, 3.f, 4.f, 5.f};
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
	index = rand() % 10;
	float ball_speedy = arr_speed[index];
	float midleftx = ball.getPosition().x;
	float midlefty = ball.getPosition().y + ballRadius;

	//счёт
	int leftPlayerScore = 0;
	int rightPlayerScore = 0;
	Font font;
	font.loadFromFile("DS-Digital Normal.ttf");

	Text leftPlayerScoreText;
	leftPlayerScoreText.setString(std::to_string(leftPlayerScore));//передать строкy для отображения
	leftPlayerScoreText.setFont(font);
	leftPlayerScoreText.setCharacterSize(40);
	leftPlayerScoreText.setPosition((WINDOW_WIDTH / 2)-batOffset, 0);

	Text rightPlayerScoreText;
	rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
	rightPlayerScoreText.setFont(font);
	rightPlayerScoreText.setCharacterSize(40);
	rightPlayerScoreText.setPosition((WINDOW_WIDTH/2) + batOffset, 0);


	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//1 Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
		//2 Обновление объектов
		//шарик
		ball.move(ball_speedx, ball_speedy);
		if (leftBat.getPosition().x <= ball.getPosition().x && ball.getPosition().x <= leftBat.getPosition().x + batWidth && leftBat.getPosition().y <= (ball.getPosition().y + ballRadius) <= leftBat.getPosition().y + batHeight) {
			ball_speedx = -ball_speedx;
		}
		if (rightBat.getPosition().x <= (ball.getPosition().x + ballRadius) && ball.getPosition().x <= rightBat.getPosition().x && rightBat.getPosition().y <= (ball.getPosition().y + ballRadius) && (ball.getPosition().y + ballRadius) <= rightBat.getPosition().y) {
			ball_speedx = -ball_speedx;
		}

		if (ball.getPosition().x <= 0)
		{
			rightPlayerScore += 1;
			rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
			ball_speedx = -ball_speedx;
		}
		if (ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius)) 
		{
			leftPlayerScore += 1;
			leftPlayerScoreText.setString(std::to_string(leftPlayerScore));
			ball_speedx = -ball_speedx;
		}


		if (ball.getPosition().y <= 0 || (ball.getPosition().y >= (WINDOW_HEIGHT - 2 * ballRadius))) {

			ball_speedy = -ball_speedy;
		}


		//проверка клавиш
		//левая 
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			leftBatSpeedY = -batSpeed;;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			leftBatSpeedY = batSpeed;
		}
		leftBat.move(0, leftBatSpeedY);
		leftBatSpeedY = 0.f;
		if (leftBat.getPosition().y >= WINDOW_HEIGHT - batHeight) {
			leftBat.setPosition(batOffset, WINDOW_HEIGHT - batHeight);
		}
		if (leftBat.getPosition().y <= 0) {
			leftBat.setPosition(batOffset, 0);
		}




		//правая
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rightBatSpeedY = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rightBatSpeedY = batSpeed;
		}
		rightBat.move(0, rightBatSpeedY);
		rightBatSpeedY = 0.f;
		if (rightBat.getPosition().y >= WINDOW_HEIGHT - batHeight) {
			rightBat.setPosition(WINDOW_WIDTH - batOffset, WINDOW_HEIGHT - batHeight);
		}
		if (rightBat.getPosition().y <= 0) {
			rightBat.setPosition(WINDOW_WIDTH - batOffset, 0);
		}
		
	



		//3 Отрисовка окна
		//3.1 Очистка окна
		window.clear();
		//3.2 Отрисовка объектов (В ПАМЯТИ!)
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		window.draw(leftPlayerScoreText);
		window.draw(rightPlayerScoreText);
		//3.3 вывод на экран
		window.display();
	}
	return 0;
}