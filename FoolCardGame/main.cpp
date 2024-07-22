#include <iostream>
using namespace std;
#define tab "\t"

enum tCard
{
	tSix = 6, tSeven, tEight, tNine, tTen,
	tJack, tQueen, tKing, tAce
};

string Suites[4] = { "hearts" , "diamonds", "clubs", "spades" };

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
	string suit;
public:
	Card(tCard value, string suit) 
	{

	}
	tCard get_value()const { return value; }
	string get_suit()const { return suit; }
	void set_value(tCard value) { this->value = value; }
	void set_suit(string suit) { if(is_in(suit, Suites))this->suit = suit; }
};

class Player
{
	unsigned int nexus_health;
	unsigned int mana;
	unsigned int spell_mana;
	bool attack_token;
	Card* deck; //new Card[40];
	Card* cards_on_hands;
	Card* cards_on_table;
	Card* cards_in_action;
public:
	Player(unsigned int nexus_health = 20, unsigned int mana = 0, unsigned int spell_mana = 0, bool attack_token = false)
	{
		set_nexus_health(nexus_health);
	}
	unsigned int get_nexus_health()const { return nexus_health; }
	unsigned int get_mana()const { return mana; }
	unsigned int get_spell_mana()const { return spell_mana; }
	bool get_attack_tokenh()const { return attack_token; }
	const Card* get_deck()const { return deck; }
	const Card* get_cards_on_hands()const { return cards_on_hands; }
	const Card* get_cards_on_table()const { return cards_on_table; }
	const Card* get_cards_in_action()const { return cards_in_action; }

	void set_deck(Card* deck);
	Card* cards_on_hands;
	Card* cards_on_table;
	Card* cards_in_action;

	void set_nexus_health(unsigned int nexus_health) { this->nexus_health = nexus_health; }
	void set_mana(unsigned int mana) { this->mana = mana; }
	void set_spell_mana(unsigned int spell_mana) { this->spell_mana = spell_mana; }
	void set_attack_token(bool attack_token) { this->attack_token = attack_token; }

};

int main()
{
	setlocale(LC_ALL, "");

}