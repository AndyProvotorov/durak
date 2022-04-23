#include <iostream>
#include "header.h"
#include <stdlib.h>

using namespace std;

// конструктор - инициализация колоды
Koloda::Koloda()
{
	for (int i=0; i< CARDSNUMBER; i++)
		for (int j=0; j<4; j++)
			{
			cards[i+j*CARDSNUMBER][0] = i + 6;
			cards[i+j*CARDSNUMBER][1] = j + 1;
			}
	CardsLost = CARDSNUMBER*4;
}

// конструктор - инициализация колоды игрока
Koloda::Koloda(int x)
{
	CardsLost = x;
}

// тосование колоды
void Koloda::Tos()
{
	// добавить таймер для настоящего рандома !!!
	int x, y, z;
	for (int i = 0; i < CARDSTOS; i++)
	{
		x = rand() % (CARDSNUMBER*4); // выбираем 1 из 36 карта
		y = rand() % (CARDSNUMBER*4); // выбираем 1 из 36 карта
		// меняем вес карт
		z = cards[x][0];
		cards[x][0] = cards[y][0];
		cards[y][0] = z;
		// меняем масть
		z = cards[x][1];
		cards[x][1] = cards[y][1];
		cards[y][1] = z;
	}
}

// отображние оставшейся (с проверкой колчества карт в колоде) колоды
void Koloda::Show(const char kolname[])
{
	cout << kolname << " have " << CardsLost << " cards:\n";

	for (int i = 0; i < CardsLost; i++)
	{
		ShowVes(cards[i][0]);
		ShowMast(cards[i][1]);
		cout << "(" << i + 1 << ")";
		if ((i+1) % CARDSOUT == 0)
			cout << endl;    // вывод по 6(константа CARDSOUT) карт
	}
	cout << endl;
}

//взять карту из колоды
void Koloda::Take(int& v, int& m, int number)
{
	v = cards[number-1][0];
	m = cards[number-1][1];
	for (int i = number-1; i < CardsLost-1; i++)
	{
		cards[i][0] = cards[i + 1][0];
		cards[i][1] = cards[i + 1][1];
	}
	CardsLost--;
}

//добавить карту в колоду
void Koloda::Give(int v, int m, int number)
{
	if (CardsLost < number)
	{
		cards[CardsLost][0] = v;
		cards[CardsLost][1] = m;
		CardsLost++;
	}
}

// определение козыря - масть последней карты в колоде
int Koloda::Koz()
{
	cout << "Kozir is ";
	ShowMast(cards[0][1]);
	cout << endl;
	return cards[0][1];
}

// сортировка колоды по мастям и старшинству
void Koloda::Sort()
{
	// добавить перенос козыря в конец 
	int z;
	for (int i=0; i<CardsLost; i++)
		for (int j = 0; j < CardsLost-1; j++)
			// если масть боольше то меняем, если масть равна и вес больше то меняем
			if ((cards[j][1]> cards[j+1][1])|| ((cards[j][1] == cards[j + 1][1])&& (cards[j][0] > cards[j + 1][0])))
				{
				// меняем вес карт
				z = cards[j][0];
				cards[j][0] = cards[j+1][0];
				cards[j+1][0] = z;
				// меняем масть
				z = cards[j][1];
				cards[j][1] = cards[j + 1][1];
				cards[j + 1][1] = z;
				}
}

// компьтер пытается отбиться: возвращает 0,если не может отбится, или номер карты которой бьется
int Koloda::CompOtb(int v, int m, int k)
{
	// попытка отбится тойже мастью
	for (int i = 0; i < CardsLost; i++)
		if ((cards[i][1] == m) && (cards[i][0] > v))
			return i+1;
	// попытка отбится козырем
	// проверка что ход не козырем
	if (m == k)
		return 0;
	for (int i = 0; i < CardsLost; i++)
		if (cards[i][1] == k)
			return i+1;
	return 0;
}

// отображение карт на столе
void Koloda::ShowDesk(void)
{
  cout << "\nIn the desk now: \n";
  for (int i=0; i<CardsLost; i++)
  {
	  if (i % 2 == 0) // выводим нечетную карту
		  ShowOne(cards[i][0], cards[i][1]);
	  else // выводим четную, которой побита неетная
	  {
		  cout << " beats";
		  ShowOne(cards[i][0], cards[i][1]);
		  cout << endl;
	  }

  }
}

// отображение одной карты
void ShowOne(int v, int m)
{
	ShowVes(v);
	ShowMast(m);
}


// брать карты из колоды пока не будет 6 или не закочится колода + вызов сортировки
void TakeToSix(Koloda& k, Koloda& p)
{
	int a, b;
	while (k.CardsLost > 0 && p.CardsLost < 6)
	{
		k.Take(a, b, k.CardsLost);
		p.Give(a, b, 6);
	}
	p.Sort();
}

// диалог выбора карты для первого хода
int Move(Koloda& k)
{
	cout << "Etner number of card to move from 1 to " << k.CardsLost << ": ";
	int x;
	cin >> x;
	while ((x > k.CardsLost) || (x < 0))
	{
		cout << "Wrong input, try again: ";
		cin >> x;
	}
	return x;
}

// диалог выбора карты для следующего хода с проверкой вариантов
int NextMove(Koloda& d, Koloda& k)
{
	int Arr[36];
	// проверка возможности ходов
	int number = ProvMove(d, k, Arr);
	if (0 == number)
	{
		cout << "You have no turn\n";
		return 0;
	}
	cout << "Etner number of card to move:";
	for (int i = 0; i < number; i++)
		cout << Arr[i] << " ";
	cout << ", (or 0 for exit): ";
	int x;
	cin >> x;
	while ((x > k.CardsLost) || (x < 0))
	{
		cout << "Wrong input, try again: ";
		cin >> x;
	}
	// проверка возможности выбранного хода

	return x;
}

// проверка возможности хода: есть карты как на столе, возвращает 0, если нет, или количество подходящихи массив индексов подходящих
int ProvMove(Koloda& d1, Koloda& k1, int mas[])
{
	int n = 0;
	for (int i = 0; i < d1.CardsLost; i++)
		for (int j = 0; j < k1.CardsLost; j++)
			if (d1.cards[i][0] == k1.cards[j][0])
			{
				mas[n] = j+1;
				n++;
			}
	if (n != 0)
		return n;
	else
	    return 0;
}

// отображение масти вместо цифры
void ShowMast(int z)
{
	switch (z)
	{
	case 1: cout << "\3"; //символ черва
		break;
	case 2: cout << "\4"; //символ бубна
		break;
	case 3: cout << "\5"; //символ креста
		break;
	case 4: cout << "\6"; //символ пика
	}
}

// отображение веса карты вместо цифры
void ShowVes(int z)
{
	switch (z)
	{
	case 6: cout << "  6";
		break;
	case 7: cout << "  7";
		break;
	case 8: cout << "  8";
		break;
	case 9: cout << "  9";
		break;
	case 10: cout << " 10";
		break;
	case 11: cout << "  J";
		break;
	case 12: cout << "  Q";
		break;
	case 13: cout << "  K";
		break;
	case 14: cout << "  A";
	}
}

// сообщение про ход или отбой
void Message(const char str[], int v, int m)
{
	cout << str;
	ShowOne(v, m);
	cout << endl;
}
// отображение состояние всех карт у всех, отладочная
void ShowAll(Koloda k1, Koloda k2, Koloda k3, Koloda k4, Koloda k5)
{
	cout << "\n\n-------------------------------------\n";
	// показать колоду игрока
	k1.Show("Koloda");
	// показать колоду игрока
	k2.Show("Player");
	// показать колоду компьтера
	k3.Show("Computer1");
	// показать колоду компьтера
	k4.Show("Computer2");
	k5.ShowDesk();
	cout << "-------------------------------------\n\n";
}