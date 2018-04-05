#include<iostream>
#include<ctime>
#include<Windows.h>
#include<string>
using namespace std;

void addCard(int amount);
void discardCard(int cardPlace, bool allCards);

int areasLeft = 5;
int section = 1;
int cardsInHand[100] = {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
int cardsInDeck[20] = {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
bool gameOver = false;
bool bossBattleActive = false;
bool matchOver = false;
int healthLeft = 0;
int maxHealth = 0;
int enemyHealth = 0;
int maxEnemyHealth = 0;
int mana = 0;
int classChosen = 0;
int sheild = 0;

int getCardCost(int cardID) {
	switch (cardID) {
	case 0:
		return 1;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 2;
		break;
	case 4:
		return 1;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 2;
		break;
	case 7:
		return 2;
		break;
	case 8:
		return 1;
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 1;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return 3;
		break;
	case 13:
		return 1;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return 1;
		break;
	default:
		return 1;
		break;
	}
}

void performCardAction(int cardID) {
	switch (cardID) {
	case 0:
		enemyHealth -= 5;
		mana--;
		break;
	case 1:
		sheild += 3;
		mana--;
		break;
	case 2:
		discardCard(1, true);
		addCard(5);
		mana--;
		break;
	case 3:
		sheild += 2;
		addCard(1);
		mana -= 2;
		break;
	case 4:
		enemyHealth -= 6;
		addCard(1);
		mana--;
		break;
	case 5:
		healthLeft += 4;
		if (healthLeft > maxHealth) {
			healthLeft = maxHealth;
		}
		break;
	case 6:
		enemyHealth -= sheild;
		sheild = 0;
		mana -= 2;
		break;
	case 7:
		enemyHealth -= 8;
		mana -= 2;
		break;
	case 8:
		addCard(1);
		mana--;
		break;
	case 9:
		enemyHealth -= 5;
		sheild += 5;
		mana--;
		break;
	case 10:
		healthLeft -= 5;
		mana++;
		break;
	case 11:
		enemyHealth -= 15;
		mana -= 3;
		break;
	case 12:
		sheild += 15;
		mana -= 3;
		break;
	case 13:
		sheild += 5;
		mana--;
		break;
	case 14:
		healthLeft -= 15;
		mana += 2;
		break;
	case 15:
		addCard(3);
		mana--;
		break;
	default:
		enemyHealth -= 5;
		mana--;
		break;
	}
}

void addCard(int amount) {
	srand(time(0));
	for (int j = 0; j < amount; j++) {
		for (int i = 0; i < 20; i++) {
			if (cardsInHand[i] == 0) {
					int cardNumber = 0;
					int cards[20];
					int arrayNumbers[20];
					for (int h = 0; h < 20; h++) {
						if (cardsInDeck[h] != 0) {
							arrayNumbers[cardNumber] = h;
							cards[cardNumber] = cardsInDeck[h];
							cardNumber++;
						}
					}
					if (cardNumber != 0) {
						int selectedNumber = rand() % cardNumber;
						cardsInHand[i] = cards[selectedNumber];
						cardsInDeck[arrayNumbers[selectedNumber]] = 0;
					}
					break;
			}
		}
	}
}

void discardCard(int cardPlace, bool allCards) {
	if (allCards == false) {
		for (int i = 0; i < 20; i++) {
			if (cardsInDeck[i] == 0) {
				cardsInDeck[i] = cardsInHand[cardPlace];
				break;
			}
		}
		cardsInHand[cardPlace] = 0;
	} else {
		for (int i = 0; i < 20; i++) {
			if (cardsInHand[i] != 0) {
				for (int j = 0; j < 20; j++) {
					if (cardsInDeck[j] == 0) {
						cardsInDeck[j] = cardsInHand[i];
						break;
					}
				}
			}
		cardsInHand[i] = 0;
		}
	}
}

string getCardName(int cardID) {
	switch (cardID) {
	case 0:
		return "Strike: 5 damage, 1 mana.";
		break;
	case 1:
		return "Defend: 3 sheild, 1 mana.";
		break;
	case 2:
		return "Gamble: discard all cards in deck, draw 5 new cards, 1 mana.";
		break;
	case 3:
		return "Shrug it off: 2 sheild, draw a card, 2 mana";
		break;
	case 4:
		return "Techquince: 6 damage, 1 mana.";
		break;
	case 5:
		return "Bandage: get 4 health back, 0 mana.";
		break;
	case 6:
		return "On the offensive: do damage, the amount of damage is the amount of sheild you have, remove all of your sheild, 2 mana.";
		break;
	case 7:
		return "Bash: 8 damage, 2 mana.";
		break;
	case 8:
		return "Regain: Draw a card, 1 mana.";
		break;
	case 9:
		return "Iron wave: 5 damage, get 5 sheild, 1 mana.";
		break;
	case 10:
		return "Sacrifice: lose 5 health, get 1 mana, 0 mana.";
		break;
	case 11:
		return "Bludgeon: 15 damage, 3 mana.";
		break;
	case 12:
		return "Unbreakable: get 15 block, 3 mana.";
		break;
	case 13:
		return "Backflip: get 5 block, 1 mana.";
		break;
	case 14:
		return "Blood loss: Lose 15 health, get 2 mana, 0 mana.";
		break;
	case 15:
		return "Power up: draw 3 cards, 1 mana.";
		break;
	default:
		return "Strike: 5 damage, 1 mana.";
		break;
	}
}

void fight() {
	system("cls");
	srand(time(0));
	if (bossBattleActive == true) {
		enemyHealth = section * 40;
	} else {
		enemyHealth = (section * 5) + rand() % (section * 10);
	}
	int op;
	while (enemyHealth > 0 && healthLeft > 0) {
		bool playerTurnEnded = false;
		discardCard(1, true);
		
		if (classChosen == 3) {
			addCard(6);
		} else {
			addCard(5);
		}
		if (classChosen == 2) {
			mana = 4;
		} else {
			mana = 3;
		}
		cout << "Your turn!" << endl;
		sheild = 0;
		while (playerTurnEnded == false) {
			int cardCounter = 1;
			int cardsCurrentlyInHand[20];
			int cardIds[20];
			cout << endl;
			cout << "Your health: " << healthLeft << endl;
			cout << "Your sheild: " << sheild << endl;
			cout << "Enemy health: " << enemyHealth << endl;
			cout << "Mana: " << mana << endl;
			cout << endl;
			for (int i = 0; i < 20; i++) {
				if (cardsInHand[i] != 0) {
					cardsCurrentlyInHand[cardCounter] = cardsInHand[i];
					cardIds[cardCounter] = i;
					cout << cardCounter << ": " << getCardName(cardsInHand[i] - 1) << endl;
					cardCounter++;
				} 
			}
			cout << endl;
			cout << "Type " << cardCounter << " to end your turn." << endl;
			cin >> op;
			if (op == cardCounter) {
				playerTurnEnded = true;
			} else if (op > 0 && op < cardCounter) {
				if (cardsCurrentlyInHand[op - 1] != 0) {
					if (mana >= getCardCost(cardsCurrentlyInHand[op - 1])) {
						cout << cardsCurrentlyInHand[op - 1] - 1 << endl;
						performCardAction(cardsCurrentlyInHand[op] - 1);
						discardCard(cardIds[op], false);
						if (enemyHealth <= 0) {
							playerTurnEnded = true;
						}
					}
				}
			}
			system("cls");	
		}
		if (enemyHealth <= 0) {
			
		} else {
			srand(time(0));
			int damageToDo = ((section * 1) + rand() % (section * 3)) - sheild;
			if (damageToDo < 0) {
				damageToDo = 0;
			}
			healthLeft -= damageToDo;
			cout << "You took " << damageToDo << " damage!" << endl;
		}
	}
	system("cls");
	if (enemyHealth <= 0) {
		discardCard(1, true);
		healthLeft = maxHealth;
		bossBattleActive = false;
		cout << "Victory!" << endl;
		cout << "Do you want a new card? Press 1 for yes, anything else will give you extra health." << endl;
		string select;
		cin >> select;
		if (select == "1") {
			system("cls");
			cout << "Loading cards..." << endl;
			int cardID[3];
			for (int i = 0; i < 3; i++) {
				srand(time(0));
				cardID[i] = 1 + rand() % 20;
				Sleep(1000);
			}
			system("cls");
			cout << "Select the card you want to add:" << endl;
			for (int i = 0; i < 3; i++) {
				cout << i + 1 << ": " << getCardName(cardID[i] - 1) << endl;
			}
			cout << "Anything else to cancel card selection." << endl;
			string selection;
			int selectedCard;
			cin >> selection;
			system("cls");
			if (selection == "1") {
				selectedCard = 0;
			}
			else if (selection == "2") {
				selectedCard = 1;
			}
			else if (selection == "3") {
				selectedCard = 2;
			}
			else {
				selectedCard = 3;
			}
			if (selectedCard < 3) {
				bool gotNewCard = false;
				for (int i = 0; i < 20; i++) {
					if (cardsInDeck[i] == 0) {
						cardsInDeck[i] = cardID[selectedCard];
						gotNewCard = true;
						break;
					}
				}
				if (gotNewCard == false) {
					cout << "Your current deck is full! Would you like to discard a card? 1: yes, anything else: no" << endl;
					cin >> selection;
					system("cls");
					if (selection == "1") {
						cout << "Select the card you want to discard:" << endl;
						for (int i = 0; i < 20; i++) {
							cout << i + 1 << ": " << getCardName(cardsInDeck[i] - 1) << endl;
						}
						int selectedCardToRemove = 0;
						cin >> selectedCardToRemove;
						system("cls");
						cardsInDeck[selectedCardToRemove - 1] = cardID[selectedCard] + 1;
					}
				}
			}
		} else {
			system("cls");
			cout << "Max health increased!" << endl;
			maxHealth += 2;
			healthLeft = maxHealth;
		}
	} else {
		cout << "Game over!" << endl;
		cout << "You made it to section " << section << "!" << endl;
		cout << "Press any key to continue..." << endl;
		int wait;
		cin >> wait;
		exit(0);
	}
	system("cls");
	areasLeft--;
	cout << "Fights left: " << areasLeft << endl;
	if (areasLeft == 1) {
		cout << "WARNING: BOSS BATTLE INCOMING!" << endl;
		bossBattleActive = true;
	}
	else if (areasLeft < 1) {
		areasLeft = 5;
		section++;
		cout << "Section cleared!" << endl;
	}
	cout << "Press anything to continue..." << endl;
	string wait;
	cin >> wait;
	fight();
}

int main() {
	int op;
	cout << "Select your class:" << endl;
	cout << "1: Warrior: Starting health: 30, starting amount of cards in deck: 5, no special effects." << endl;
	cout << "2: Mage: Starting health: 15, starting amount of cards in deck: 6, gets a extra point at the start of each turn." << endl;
	cout << "3: Gambler: Starting health: 20, starting amount of cards in deck: 8, draw a card after the end of your turn." << endl;
	cin >> op;
	switch (op) {
	case 1:
		classChosen = 1;
		maxHealth = 30;
		cardsInDeck[0] = 1;
		cardsInDeck[1] = 1;
		cardsInDeck[2] = 1;
		cardsInDeck[3] = 2;
		cardsInDeck[4] = 2;
		break;
	case 2:
		classChosen = 2;
		maxHealth = 15;
		cardsInDeck[0] = 1;
		cardsInDeck[1] = 1;
		cardsInDeck[2] = 1;
		cardsInDeck[3] = 2;
		cardsInDeck[4] = 2;
		cardsInDeck[5] = 2;
		break;
	case 3:
		classChosen = 3;
		maxHealth = 20;
		cardsInDeck[0] = 1;
		cardsInDeck[1] = 1;
		cardsInDeck[2] = 1;
		cardsInDeck[3] = 2;
		cardsInDeck[4] = 2;
		cardsInDeck[5] = 2;
		cardsInDeck[6] = 3;
		cardsInDeck[7] = 3;
		break;
	default:
		classChosen = 1;
		maxHealth = 60;
		cardsInDeck[0] = 1;
		cardsInDeck[1] = 1;
		cardsInDeck[2] = 1;
		cardsInDeck[3] = 2;
		cardsInDeck[4] = 2;
		break;
	}
	healthLeft = maxHealth;
	fight();
}