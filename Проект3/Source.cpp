#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;


bool startGame() {
	srand(time(0));

	RenderWindow app(VideoMode(520, 450), "Arkanoid!"); //���� �������� 520 �� 450
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("block01.png");
	t2.loadFromFile("background.jpg");
	t3.loadFromFile("ball.png");
	t4.loadFromFile("paddle.png");

	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 440); //��������� ��������� ���������

	Sprite block[1000];

	int n = 0;
	int count = 50;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		} // ����� 10 �� 10

	float dx = 3, dy = 2;
	float x = 330, y = 300; //�������� � ��������� ��������� ����

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		x += dx;
		for (int i = 0; i < n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dx = -dx;
				count--;
			} 

		y += dy;
		for (int i = 0; i < n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dy = -dy;
			}

		if (x < 0 || x>520)  
			dx = -dx;
		if (y < 0)  
			dy = -dy;



		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{ return true; }//���� ��� ��� ������ �������, �� ������������� ����
		if (y > 450)
		{
			dx = 0;
			dy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Space) || (count ==0))
				return true;
			/*sf:: Font font;//����� 
			font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
			Text text("", font, 100);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
			
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

			text.setString("������� ������:");//������ ������ ������
			sf::Text text;

			// �������� �����
			text.setFont(font); // font ��� sf::Font

								// �������� ������������ ������
			text.setString("Hello world");

			// �������� ������ ��������
			text.setCharacterSize(24); // � ��������, � �� ������!

			

			// �������� ����� ������
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			
		app.draw(text);*/
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{ return false; }//���� ������, �� ������� �� ����


		if (Keyboard::isKeyPressed(Keyboard::Right)) 
			sPaddle.move(10, 0);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			sPaddle.move(-10, 0); //�������� ������ ���� + �������� ���������



		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) 
			dy = -(rand() % 5 + 2); //������������� ���� � ��������� (�������� �������� ��������)

		sBall.setPosition(x,y);

		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);

		app.display();
	}
};

	void gameRunning() 
	{//�-��� ������������� ���� , ���� ��� ����������
		if (startGame()) 
		{ 
			gameRunning(); 
		}////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
	}

int main()
{
	gameRunning();

	return 0;
}
