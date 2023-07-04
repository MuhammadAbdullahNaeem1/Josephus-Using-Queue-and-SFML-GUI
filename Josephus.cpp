#include<SFML\Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<Windows.h>
using namespace std;
using namespace sf;


template<class T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node()
	{
		data = 0;
		next = NULL;
	}
	Node(T val)
	{
		data = val;
		next = NULL;
	}
};
template<class T>
class Circularqueue
{
private:
	int size;
	Node<T>* front;
	Node<T>* rear;
public:
	Circularqueue()
	{
		size = 0;
		front = nullptr;
		rear = nullptr;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	void enqueue(T val)
	{
		Node<T>* temp = new Node<T>;
		temp->data = val;
		if (front == nullptr) //inserting first element
		{
			temp->next = front;
			front = temp;
			rear = temp;
			size++;
		}
		else
		{
			rear->next = temp;
			rear = temp;
			rear->next = front;
			size++;
		}
	}
	void dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue underflow!\n";
		}
		else
		{
			Node<T>* temp = front;
			front = front->next;
			rear->next = front;
			delete temp;
			size--;
		}
	}
	int Size()
	{
		return size;
	}
	T Front()
	{
		if (isEmpty())
		{
			cout << "Queue underflow\n";
		}
		else
		{
			return front->data;
		}
	}
	T Rear()
	{
		if (isEmpty())
		{
			cout << "Queue underflow\n";
		}
		else
		{
			return rear->data;
		}
	}
	void display_queue()
	{
		cout << endl;
		Node<T>* current = front;
		while (current->next != front)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << current->data;
		cout << endl;

	}
	void next()
	{
		front = front->next;
		rear = rear->next;
	}
};



int main()
{
	int num, k;
	cout << "Enter the number of persons: ";
	cin >> num;
	cout << "Enter the number of persons you want to skip: ";
	cin >> k;
	Circularqueue<int> q;
	for (int i = 0; i < num; i++)
	{
		q.enqueue(i + 1);
	}

	
	RenderWindow window(VideoMode(1920, 1080), "Sfml", Style::Default);  //setting background
	Texture background;
	if (!background.loadFromFile("roshi.jpg"))
	{
		cout << "Error loading background\n";
	}

	Sprite back;
	back.setTexture(background);

	Texture character;                                       // loading character
	if (!character.loadFromFile("goku.png"))
	{
		cout << "Error loading character\n";
	}
	Sprite* charc = new Sprite[num];

	Texture death;
	if (!death.loadFromFile("rip.png"))                      //loading death character
	{
		cout << "Error loading death character\n";
	}

	SoundBuffer buffer;                                     //loading sound
	if (!buffer.loadFromFile("s2.wav"))
	{
		cout << "Error loading sound\n";
	}
	Sound sound;
	sound.setBuffer(buffer);



	Font font;
	font.loadFromFile("texgyreadventor-regular.otf");
	Text* text = new Text[num];
	for (int i = 0; i < num; i++)
	{
		text[i].setFont(font);
		text[i].setString(to_string(i + 1));
		text[i].setFillColor(Color::Cyan);
	}
	bool flag = 0;
	CircleShape circle;
	circle.setRadius(450);
	circle.setFillColor(Color::Transparent);
	circle.setOutlineColor(Color::Transparent);
	circle.setOutlineThickness(5);
	circle.setPosition(550, 45);
	circle.setPointCount(num);
	for (int i = 0; i < num; i++)
	{
		charc[i].setTexture(character);
		charc[i].setPosition(circle.getPoint(i).x + 450, circle.getPoint(i).y);
		text[i].setPosition(circle.getPoint(i).x + 510, circle.getPoint(i).y +50);
	}

	window.setKeyRepeatEnabled(0);
	while (window.isOpen())
	{
		Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				window.close();
			}
			if (ev.type == Event::KeyPressed)
			{
				if (ev.key.code == Keyboard::Enter && q.Size() != 1)
				{
					cout << "Enter key pressed!" << endl;
					flag = 1;
				}
			}


		}


		if (q.Size() != 1 && flag == 1)
		{
			sound.play();
			for (int i = 0; i < k; i++)
			{
				q.next();
			}
			bool flag2 = true;
			int x = q.Front();
			
			q.dequeue();
		
			if(q.Size() !=1)
			cout << q.Front() << " ";
			if (q.Size() == 1) {
				cout << q.Front() << " " << "is the survivor ";
				
			}
			
			charc[x - 1].setTexture(death);
			flag = 0;
		}
		window.clear();
		window.draw(back);
		window.draw(circle);
		for (int i = 0; i < num; i++)
		{
			window.draw(charc[i]);
			window.draw(text[i]);
		}
		//window.draw(charc);
		window.display();
	}

	system("pause>0");
	return 0;
}