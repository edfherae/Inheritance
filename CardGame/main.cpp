#include <iostream>
using namespace std;
#define tab "\t"

class Card
{
protected:
	unsigned int mana;
public:
	unsigned int get_mana()const { return mana; }
	void set_mana(int mana) { this->mana = mana; }
};
class Unit : public Card
{
	unsigned int strength;
	unsigned int health;
public:
	unsigned int get_strength()const { return strength; }
	unsigned int get_health()const { return health; }
	void set_strength(int strength) { this->strength = strength; }
	void set_health(int health) { this->health = health; }
	
};
class Champion : public Unit
{

};
class Spell : public Card
{

};
class PlaceOfPower : public Card
{

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