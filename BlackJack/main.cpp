#include <iostream>
using namespace std;
#define tab "\t"

enum tCard
{
	tTwo = 2, tThree, tFour, tFive, tSix = 6, tSeven, tEight, tNine, tTen,
	tJack = 10, tQueen = 10, tKing= 10, tAce
};

//string Suites[4] = { "hearts" , "diamonds", "clubs", "spades" };

bool is_in(string suit, const string* Suites)
{
	for (int i = 0; i < 4; i++)
	{
		if (suit == Suites[i])return true;
	}
	return false;
}

class Card
{
protected:
	tCard value;
public:
	Card(tCard value)
	{
		set_value(value);
	}
	~Card() {}

	tCard get_value()const { return value; }
	void set_value(tCard value) { this->value = value; }
};

class Player
{
	Card* cards_on_hands;
public:
	Player(unsigned int nexus_health = 20, unsigned int mana = 0, unsigned int spell_mana = 0, bool attack_token = false)
	{
		
	}

};

int main()
{
	setlocale(LC_ALL, "");

}