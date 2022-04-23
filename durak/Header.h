const int CARDSOUT = 6;     // количества карт в рядудля вывода на экран
const int CARDSTOS = 200;   // количество шагов при перетасовке карт
const int CARDSNUMBER = 9;   // количество карт одной масти

class Koloda
{
private:
public:
	// карты
	// 11 - валет, 12 - дама, 13 - король, 14 - туз
	// 1 - черва, 2 - бубна, 3 - креста, 4 - пика
	int cards[CARDSNUMBER * 4][2];
	int CardsLost;
	Koloda();
	Koloda(int x);
	// тосование колоды
	void Tos();
	// отображние оставшейся (с проверкой колчества карт в колоде) колоды
	void Show(const char kolname[]);
	//взять карту из колоды
	void Take(int& v, int& m, int number);
	//добавить карту в конец колоды
	void Give(int v, int m, int number);
	// определение и отображение козыря - масть последней карты в колоде
	int Koz();
	// сортировка колоды по мастям и старшинству
	void Sort();
	// компьтер пытается отбиться: возвращает 0,если не может отбится, или номер карты которой бьется
	int CompOtb(int v, int m, int k);
	// отображение карт на столе
	void ShowDesk(void);
};

// брать карты из колоды пока не будет 6 или не закочится колода
void TakeToSix(Koloda& k, Koloda& p);

// диалог выбора карты для первого хода
int Move(Koloda& k);

// диалог выбора карты для следующего хода с проверкой вариантов
int NextMove(Koloda& d, Koloda& k);

// проверка возможности хода: есть карты как на столе, возвращает 0,если нет, или индекс первой подходящей
int ProvMove(Koloda& d, Koloda& k, int mas[]);

// отображение масти вместо цифры
void ShowMast(int z);
// отображение веса карты вместо цифры
void ShowVes(int z);

// отображение одной карты
void ShowOne(int v, int m);

// сообщение про ход или отбой
void Message(const char str[], int v, int m);

// отображение состояние всех карт у всех, отладочная
void ShowAll(Koloda k1, Koloda k2, Koloda k3, Koloda k4, Koloda k5);
