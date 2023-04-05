#include <vector>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <pthread.h>


int WindowxSize = 1000, WindowySize = 1000;
bool keyheld1 = false, keyheld2 = false, keyheld3 = false, keyheld4 = false, keyheld5 = false, keyheld6 = false, keyheld7 = false , keyheld8 = false;
struct arguments
{
	Sprite* sprite;
	Sprite** objs;
	int game_size;
	int points;

	arguments()
	{
		points = 0;
		game_size = 10;
		objs = NULL;
		sprite = NULL;
	}
};


int random_number()
{
	srand(time(0));
	int num = rand() % 99;
	num += 10;
	num *= 9;
	num = 1369 / num;
	num %= 25;
	if(num < 10)
		num += 15;
	return num;
}

bool chek_collision(Sprite* p1, Sprite* obj)
{
	int sizex = 20, sizey = 20;
	if ((int)obj->getPosition().x + sizex >= (int)p1->getPosition().x 
			&& (int)p1->getPosition().x + sizex >= (int)obj->getPosition().x 
			&& (int)obj->getPosition().y + sizey >= (int)p1->getPosition().y 
			&& (int)p1->getPosition().y + sizey >= (int)obj->getPosition().y)
	{
		obj->setPosition(-99,-99);
		return true;
	}
	return false;
}

bool Key_Press(arguments* args)
{
	Sprite* obj = args->sprite;
	Sprite** objs = args->objs;

	if(Keyboard::isKeyPressed(Keyboard::Right) && (obj->getPosition().x + 40 < WindowxSize))
	{	
		if(keyheld1 == false)
		{
			keyheld1 = true;	
			if(obj->getPosition().x + 40 < WindowxSize)
			{
				obj->setPosition( obj->getPosition().x + 40, obj->getPosition().y);
			}
		}
	}
	else keyheld1 = false;

	if(Keyboard::isKeyPressed(Keyboard::Up) && obj->getPosition().y > 0)
	{
		if (keyheld2 == false)
		{
			keyheld2 = true;
			obj->setPosition(obj->getPosition().x, obj->getPosition().y - 40);
		}	
	}
	else keyheld2 = false;
	
	if(Keyboard::isKeyPressed(Keyboard::Left) && obj->getPosition().x > 0)
	{
		if(keyheld3 == false)
		{
			keyheld3 = true;
			obj->setPosition(obj->getPosition().x - 40, obj->getPosition().y);
		}
	}
	else keyheld3 = false;
	
	if(Keyboard::isKeyPressed(Keyboard::Down) && (obj->getPosition().y + 40 < WindowySize))
	{
		if(keyheld4 == false)
		{
			keyheld4 = true;
			if(obj->getPosition().y + 40 < WindowySize)
			{
				obj->setPosition(obj->getPosition().x , obj->getPosition().y + 40);
			}
		}
	}
	else keyheld4 = false;

	for (int i = 0; i < args->game_size; i++) 
	{
		for (int j = 0; j < args->game_size; j++) 
		{
			if(chek_collision(obj,&args->objs[i][j]))
				return true;
		}
	}
	return false;
}

bool Key_Press1(arguments* args)
{
	Sprite* obj = args->sprite;
	if(Keyboard::isKeyPressed(Keyboard::D) && (obj->getPosition().x + 40 < WindowxSize))
	{
		if(keyheld5 == false)
		{
			keyheld5 = true;
			if(obj->getPosition().x + 40 < WindowxSize)
			{
				obj->setPosition( obj->getPosition().x + 40, obj->getPosition().y);
			}
		}
	}
	else keyheld5 = false;

	if(Keyboard::isKeyPressed(Keyboard::W) && obj->getPosition().y > 0)
	{
		if (keyheld6 == false)
		{
			keyheld6 = true;
			obj->setPosition(obj->getPosition().x, obj->getPosition().y - 40);
		}	
	}
	else keyheld6 = false;
	
	if(Keyboard::isKeyPressed(Keyboard::A) && obj->getPosition().x > 0)
	{
		if(keyheld7 == false)
		{
			keyheld7 = true;
			obj->setPosition(obj->getPosition().x - 40, obj->getPosition().y);
		}
	}
	else keyheld7 = false;
	
	if(Keyboard::isKeyPressed(Keyboard::S) && (obj->getPosition().y + 40 < WindowySize))
	{
		if(keyheld8 == false)
		{
			keyheld8 = true;
			if(obj->getPosition().y + 40 < WindowySize)
			{
				obj->setPosition(obj->getPosition().x , obj->getPosition().y + 40);
			}
		}
	}
	else keyheld8 = false;

	for (int i = 0; i < args->game_size; i++) 
	{
		for (int j = 0; j < args->game_size; j++) 
		{
			if(chek_collision(obj,&args->objs[i][j]))
				return true;
		}
	}
	return false;
}

void Draw_Grid(VertexArray* gridLines, int game_size)
{
	// Define grid properties
		float cellSize = 40.0f;
		int numCellsX = game_size;
		int numCellsY = game_size;

		for (int x = 0; x <= numCellsX; x++)
		{
			float xPos = x * cellSize;
			gridLines->append(Vertex(Vector2f(xPos, 0), Color::Black));
			gridLines->append(Vertex(Vector2f(xPos, numCellsY * cellSize), Color::Black));
		}
		for (int y = 0; y <= numCellsY; y++)
		{
			float yPos = y * cellSize;
			gridLines->append(Vertex(Vector2f(0, yPos), Color::Black));
			gridLines->append(Vertex(Vector2f(numCellsX * cellSize, yPos), Color::Black));
		}
}

void* player1(void* args)
{
	arguments* player = (arguments*)args;
	if(Key_Press(player))
	{
		player->points++;
	}
	pthread_exit((void*)player);
}

void* player2(void* args)
{
	arguments* player = (arguments*)args;
	if(Key_Press1(player))
	{
		player->points++;
	}
	pthread_exit((void*)player);
}

int main()
{
	string name1, name2;
	cout<<"Enter player 1 name: ";
	cin>>name1;
	cout<<"Enter player 2 name: ";
	cin>>name2;

	pthread_t thread1, thread2;
	int totalObjects = 0;

	int game_size = random_number();
	cout << game_size << endl;

	Texture texture,texturee;
	if(!texture.loadFromFile("sprit.png"))
	{
		cout<<"\nImage not loaded\n";
		return 0;
	}

	if(!texturee.loadFromFile("sprite2.png"))
	{
		cout<<"\nImage not loaded\n";
		return 0;
	}


	Sprite** objs = new Sprite*[game_size];
	for(int i = 0; i < game_size ; i++)
	{
		objs[i] = new Sprite[game_size];
	}

	Texture objTexture,objTexture1;

	if(!objTexture.loadFromFile("obj.png"))
	{
		cout<<"\nImage loading error obj.png\n";
		return 0;
	}

	if(!objTexture1.loadFromFile("obj1.png"))
	{
		cout<<"\nImage loading error obj1.png\n";
		return 0;
	}

	for (int i = 0; i < game_size; i++) 
	{
		if(i % 3 == 0)
		{
			for (int j = 0; j < game_size; j++) 
			{
				if(i==0 && j==0)
					continue;

					if (i % 2 == 0 && j % 2 == 0) 
					{
						objs[i][j].setTexture(objTexture);
						objs[i][j].setScale(0.1,0.1);
						objs[i][j].setPosition(40.f*i,40.f*j);
						totalObjects++;
					}
					else if(i % 2 == 1 && j % 2 == 1)
					{
						objs[i][j].setTexture(objTexture1);
						objs[i][j].setScale(0.1,0.1);
						objs[i][j].setPosition(40.f*i,40.f*j);
						totalObjects++;
					}
			}
		}
	}

	cout<<"Total Objects are: "<<totalObjects<<endl;
	Vector2f check_collision(0,0);
	WindowxSize = game_size * 40;
	WindowySize = game_size * 40;
	cout << WindowxSize << " x " << WindowySize << endl;
	RenderWindow window(VideoMode(WindowxSize, WindowySize + 150), "Thread Ripper");
	window.setFramerateLimit(60);

	Sprite p1;
	p1.setTexture(texture);
	p1.setScale(0.2,0.2);
	p1.setPosition(40,40);

	Sprite p2;
	p2.setTexture(texturee);
	p2.setScale(0.2,0.2);
	p2.setPosition(80, 80);

	// Create grid lines
	VertexArray gridLines(Lines);
	arguments* obj = new arguments;
	arguments* obj1 = new arguments;

	obj->game_size = game_size;
	obj->objs = objs;
	obj->sprite = &p1;

	obj1->objs = objs;
	obj1->game_size = game_size;
	obj1->sprite = &p2;
	void* ret1;
	void* ret2;

	arguments* retrn1, *retrn2;

	name1 += " ";
	name2 += " ";

	Font font;
    Text text1, text2;
    if(!font.loadFromFile("Lato.ttf"))
        return 0;

    text1.setFont(font);
    text1.setString(name1);
    text1.setFillColor(Color::Red);
	text1.setPosition(0, WindowySize + 100);

    text2.setFont(font);
    text2.setString(name2);
    text2.setFillColor(Color::Green);
	text2.setPosition(WindowxSize - 150, WindowySize + 100);
	string points1,points2;

	while (window.isOpen())
	{	
		Draw_Grid(&gridLines, game_size);
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
				window.close();
		    }
		}
		points1.clear();
		points2.clear();
		window.clear(Color::Black);
		window.draw(gridLines);

		pthread_create(&thread1, NULL, player1,(void*)obj);
		pthread_join(thread1, &ret1);
		retrn1 = (arguments*)(ret1);

		pthread_create(&thread2, NULL, player2, (void*)obj1);
		pthread_join(thread2, &ret2);
		retrn2 = (arguments*)(ret2);
		
		points1 += name1;
		points1 += to_string(retrn1->points);
		points2 += name2;
		points2 += to_string(retrn2->points);

		text1.setString(points1);
		text2.setString(points2);

		window.draw(text1);
		window.draw(text2);
		window.draw(p1);
		window.draw(p2);

		for (int i = 0; i < game_size; i++) 
		{
			for (int j = 0; j < game_size; j++) 
			{
				if(objs[i][j].getPosition() != check_collision);
				{
					window.draw(objs[i][j]);
				}
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Escape) || (retrn1->points + retrn2->points == totalObjects))
		{	
			cout<<"The points for " <<name1<<" are: "<<retrn1->points<<endl;
			cout<<"The points for "<<name2 <<" are: " <<retrn2->points<<endl;
			if(retrn1->points > retrn2->points)
				cout<<name1 << "is the Winner\n";
			else if(retrn2->points > retrn1->points)
				cout<<name2 << "is the Winner\n";
			else cout<<"\nMatch Draw\n";
			cout<<"\nWohooo FireWorks pew pew\n";
			return 0;
		}

		window.display();
	}

	return 0;
}
