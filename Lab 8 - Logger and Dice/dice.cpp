// A dice game against the computer
// CS44001 Assignment 8 - Dice game
// Connor DeGeorge
// 3/16/20

#include <iostream>
#include <string>

using std::cout; using std::cin; using std::endl;
using std::string; using std::to_string;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
	Game() :playersCount_(0), movesCount_(0),
		playerWon_(noWinner) {}

	// template method
	void playGame(const int playersCount = 0) {
		playersCount_ = playersCount;
		movesCount_ = 0;

		initializeGame();

		for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
			makeMove(i);
			if (i == playersCount_ - 1)
				++movesCount_;
		}

		printWinner();
	}

	virtual ~Game() {}

protected:
	// primitive operations
	virtual void initializeGame() = 0;
	virtual void makeMove(int player) = 0;
	virtual void printWinner() = 0;
	virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
																// returns true if winner is decided
	static const int noWinner = -1;

	int playersCount_;
	int movesCount_;
	int playerWon_;
};

class Dice : public Game {
public:
	void initializeGame() { playersCount_ = numPlayers_; }
	void makeMove(int);
	void printWinner();

private:
	static const int numPlayers_ = 2;
	static const int maxMoves_ = 3;
	int highScore_[numPlayers_] = { 0, 0 };
	bool passed_[numPlayers_] = { false, false };
};

void Dice::makeMove(int player) {
	string msg, playerName, playerPos;

	// Determine if game is over
	if (movesCount_ == maxMoves_ || (passed_[0] && passed_[1])) {
		if (player == 0) {
			playerWon_ = highScore_[0] >= highScore_[1] ? 0 : 1; // If there is a tie, computer wins
			return;
		}
	}

	if (player == 0) {
		playerName = "Computer";
		playerPos = "computer's";
	}
	else {
		playerName = "You";
		playerPos = "your";
	}

	if (!passed_[player]) {
		// Roll dice
		cout << playerName << " rolled: ";

		int total = 0, index = 0;
		while (index < 5) {
			int r = (rand() % 7) + 1;
			cout << to_string(r) << " ";

			total += r;
			++index;
		}
		cout << "= " << to_string(total);

		if (total > highScore_[player]) // Assign new highscore
			highScore_[player] = total;
	}
	else {
		cout << playerName << " passed";
	}

	cout << ", " << playerPos << " highest score = " << to_string(highScore_[player]) << endl;

	if (player == 1 && movesCount_ < maxMoves_ - 1) { // Ask to pass is player is human
		cout << "Roll again? [y/n] ";

		char response;
		cin >> response;
		response = toupper(response);
		while (response != 'Y' && response != 'N') { // Ensure user uses y or n
			cout << "Invalid character. Roll again? [y/n] ";
			cin >> response;
			response = toupper(response);
		}

		if (response == 'N') passed_[1] = true;
	}
	else { // Determine to pass if player is computer
		int r = rand() % 2;
		passed_[0] = r == 0 ? true : false;
	}
}

void Dice::printWinner() {
	if (playerWon_ == 0)
		cout << "You lose" << endl;
	else
		cout << "You win" << endl;
}

int main() {
	Game* gp = new Dice;
	gp->playGame();
	delete gp;
}