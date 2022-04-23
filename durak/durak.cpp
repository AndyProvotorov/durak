#include <iostream>
#include "header.h"

using namespace std;

int main()
{
	// инициализация игровой колоды
	Koloda kol = Koloda();
		// отображение начальной колоды
		//kol.Show("Koloda");
	// перетасовка карт
	kol.Tos();
		// отображение перетасованой колоды
		//kol.Show("Koloda");

	// инициализация пустой игровой колоды игрока
	Koloda Player = Koloda(0);
	// инициализация пустой игровой колоды компьютера 1
	Koloda Computer1 = Koloda(0);
	// инициализация пустой игровой колоды компьютера 2
	Koloda Computer2 = Koloda(0);
	// инициализация пустой игровой колоды - карты на столе
	Koloda Desk = Koloda(0);

	int hod = 0;	// чей ход
					// 0  - игрока
					// 1 - компьютер 1
					// 2 - компьютер 2

	// первая раздача карт из колоды до 6 шт
	TakeToSix(kol, Player);
	TakeToSix(kol, Computer1);
	TakeToSix(kol, Computer2);

	// начальное состояние карт
	ShowAll(kol,Player,Computer1,Computer2,Desk);

	// приветсвтие
	cout << "\n\t\t\tWelcome to game DURAK!\n\n";
	cout << "Cards are drowing...\n";
	// определение козыря - масть последней карты в колоде
	int Kozir = kol.Koz(); 
	cout << "Let's play\n";

	int choise, choiseC1, choiseC2, a, b, rez;
	int Arr[36];
	int number;

	// основной цикл, завершение игры когда в колоде нет карт у двух изтрех нигроков нет карт
//	while ((0==kol.CardsLost)&&((0==Player.CardsLost+Computer1.CardsLost)||
//		(0 == Player.CardsLost + Computer1.CardsLost)||(0 == Computer2.CardsLost + Computer1.CardsLost)))
	{
		// выбор хода
		switch (hod)
		{
		// ход игрока
		case 0: 
			// показать колоду игрока
			Player.Show("You");
			// предложить диалог хода
			choise = Move(Player);
			choiseC2 = 1; // количество ходов Компьютера2, в начале не равно 0, чтобы заходило в цикл
			while ((choise != 0)&& (choiseC2 != 0))
			{
				// исключить карту из колоды игрока
				Player.Take(a, b, choise);
				// добавить карту к картам на столе
				Desk.Give(a, b, 36);

				// отобразить ход
				Message("You move ", a, b);
				// компьютер 1 пытается отбиться
				rez = Computer1.CompOtb(a, b, Kozir);
				if (rez != 0)
				{
					// исключить карту из колоды игрока
					Computer1.Take(a, b, rez);
					// добавить карту к картам на столе
					Desk.Give(a, b, 36);
					// компьютер отбился
					Message("Computer1 beats: ", a, b);
				}
				// компьютер не может отбиться
				else
				{
					// подкидывает компьютер 2
					// проверяем есть ли что подкинуть
					number = ProvMove(Desk, Computer2, Arr);
					// если нашел, то подкидывает
					if (number != 0)
					{
						cout << "Computer1 taked cards\n";
						// отображаеи карту которую подкидывает
						Message("Computer2 flip a card: ", Computer2.cards[Arr[0]-1][0], Computer2.cards[Arr[0]-1][1]);
						// забираем из колоды Компьютера 2
						// исключить карту из колоды игрока
						Computer2.Take(a, b, Arr[0]);
						// кладем в колоду компьютера 1
						Computer1.Give(a, b, 36);
						number = ProvMove(Desk, Computer2, Arr);
					}
					// забирает всё со стола
					int temp = Desk.CardsLost;
					for (int i = 0; i < temp; i++)
					{
						// исключить карту с игрового стола
						Desk.Take(a, b, 1);
						// кладем в колоду компьютера 1
						Computer1.Give(a, b, 36);
					}
					// переход хода к Компьютеру2
					hod = 2;
					// очистка доски
					Desk = Koloda(0);
					// добор карт до 6 кому нужно
					TakeToSix(kol, Player);
					TakeToSix(kol, Computer2);
					break;
				}
				// карты на столе
				Desk.ShowDesk();
				// показать колоду игрока
				Player.Show("You");
				// предложить диалог хода
				choise = NextMove(Desk, Player);
				
				// если ходов нет то ходит Компьютер2
				if (0 == choise)
				{
					choiseC2 = ProvMove(Desk, Computer2, Arr);
					// если есть ходы
					while (choiseC2 != 0)
					{
						// исключить карту из колоды игрока
						Computer2.Take(a, b, Arr[0]);
						// добавить карту к картам на столе
						Desk.Give(a, b, 36);
						// отобразить ход
						Message("Computer2 move ", a, b);
						// компьютер 1 пытается отбиться
						rez = Computer1.CompOtb(a, b, Kozir);
						if (rez != 0)
						{
							// исключить карту из колоды игрока
							Computer1.Take(a, b, rez);
							// добавить карту к картам на столе
							Desk.Give(a, b, 36);
							// компьютер отбился
							Message("Computer1 beats: ", a, b);
							// карты на столе
							Desk.ShowDesk();
							choiseC2 = ProvMove(Desk, Computer2, Arr);
						}
						// компьютер не может отбиться
						else
						{
							cout << "Computer1 taked cards\n";
							// забирает всё со стола
							int temp = Desk.CardsLost;
							for (int i = 0; i < temp; i++)
							{
								// исключить карту с игрового стола
								Desk.Take(a, b, 1);
								// кладем в колоду компьютера 1
								Computer1.Give(a, b, 36);
							}
							// переход хода к Компьютеру2
							hod = 2;
							// очистка доски
							Desk = Koloda(0);
							// добор карт до 6 кому нужно
							TakeToSix(kol, Player);
							TakeToSix(kol, Computer2);
							break;
						}
					}

				}
			}
			// компьютер1 отбился (если не отбился ход переходит компьютеру2 выше)
			if (hod != 2)
			{
				cout << "Computer1 beats ok\n";
				// переход хода к Компьютеру1
				hod = 1;
				// очистка доски
				Desk = Koloda(0);
				// добор карт до 6 кому нужно
				TakeToSix(kol, Player);
				TakeToSix(kol, Computer1);
				TakeToSix(kol, Computer2);
			}
			break;
		// ход компьютера 1
		case 1: break;
		// ход компьютера 2
		case 2: break;
		}

	}

	// состояние карт
//	ShowAll(kol, Player, Computer1, Computer2, Desk);

	return 0;
}

