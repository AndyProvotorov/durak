const int CARDSOUT = 6;     // ���������� ���� � ������� ������ �� �����
const int CARDSTOS = 200;   // ���������� ����� ��� ����������� ����
const int CARDSNUMBER = 9;   // ���������� ���� ����� �����

class Koloda
{
private:
public:
	// �����
	// 11 - �����, 12 - ����, 13 - ������, 14 - ���
	// 1 - �����, 2 - �����, 3 - ������, 4 - ����
	int cards[CARDSNUMBER * 4][2];
	int CardsLost;
	Koloda();
	Koloda(int x);
	// ��������� ������
	void Tos();
	// ���������� ���������� (� ��������� ��������� ���� � ������) ������
	void Show(const char kolname[]);
	//����� ����� �� ������
	void Take(int& v, int& m, int number);
	//�������� ����� � ����� ������
	void Give(int v, int m, int number);
	// ����������� � ����������� ������ - ����� ��������� ����� � ������
	int Koz();
	// ���������� ������ �� ������ � �����������
	void Sort();
	// �������� �������� ��������: ���������� 0,���� �� ����� �������, ��� ����� ����� ������� ������
	int CompOtb(int v, int m, int k);
	// ����������� ���� �� �����
	void ShowDesk(void);
};

// ����� ����� �� ������ ���� �� ����� 6 ��� �� ��������� ������
void TakeToSix(Koloda& k, Koloda& p);

// ������ ������ ����� ��� ������� ����
int Move(Koloda& k);

// ������ ������ ����� ��� ���������� ���� � ��������� ���������
int NextMove(Koloda& d, Koloda& k);

// �������� ����������� ����: ���� ����� ��� �� �����, ���������� 0,���� ���, ��� ������ ������ ����������
int ProvMove(Koloda& d, Koloda& k, int mas[]);

// ����������� ����� ������ �����
void ShowMast(int z);
// ����������� ���� ����� ������ �����
void ShowVes(int z);

// ����������� ����� �����
void ShowOne(int v, int m);

// ��������� ��� ��� ��� �����
void Message(const char str[], int v, int m);

// ����������� ��������� ���� ���� � ����, ����������
void ShowAll(Koloda k1, Koloda k2, Koloda k3, Koloda k4, Koloda k5);
