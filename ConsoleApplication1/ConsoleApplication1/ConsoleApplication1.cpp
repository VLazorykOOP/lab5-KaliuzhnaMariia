// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <stdexcept>
using namespace std;

class Card {
public:
    enum Suit { Hearts, Diamonds, Clubs, Spades };
    enum Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

    Card(Suit s, Rank r) : suit_(s), rank_(r) {}

    Suit getSuit() const { return suit_; }
    Rank getRank() const { return rank_; }

    friend ostream& operator<<(ostream& os, const Card& card) {
        string ranks[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
        string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
        os << ranks[card.getRank()] << " of " << suits[card.getSuit()];
        return os;
    }
protected:
    Suit suit_;
    Rank rank_;
};

class Deck {
public:
    Deck(bool shuffle = true) {
        for (int s = Card::Hearts; s <= Card::Spades; s++) {
            for (int r = Card::Ace; r <= Card::King; r++) {
                cards_.push_back(Card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r)));
            }
        }
        if (shuffle) {
            shuffle_();
        }
    }
    void shuffle_() {
        random_device rd;
        mt19937 rng(rd());
        shuffle(cards_.begin(), cards_.end(), rng);
    }
    Card draw() {
        if (cards_.empty()) {
            throw runtime_error("Deck is empty");
        }
        Card c = cards_.back();
        cards_.pop_back();
        return c;
    }

    void returnCardsToDeck(const Card& c1, const Card& c2, const Card& c3) {
        cards_.push_back(c1);
        cards_.push_back(c2);
        cards_.push_back(c3);
    }

    void returnMediumCardToDeck(const Card& c2) {
        cards_.push_back(c2);
    }

    size_t size() const {
        return cards_.size();
    }
protected:
    vector<Card> cards_;
};

class Solitaire : public Deck {
public:
    Solitaire(bool shuffle = true) : Deck(true) {
        if (shuffle) {
            shuffle_();
        }
    }
    void play() {
        if (cards_.empty()) {
            return;
        }
        while (cards_.size() >= 3) {
            bool is_discarded = false;
            int iterator = 0;
            for (auto it = cards_.begin(); it != cards_.end() - 2; it++) {
                Card c1 = *it;
                Card c2 = *(it + 1);
                Card c3 = *(it + 2);
                cout << "Cards drawn: " << cardToString(c1) << ", " << cardToString(c2) << ", " << cardToString(c3) << endl;
                if (isTwoExtremesSameColor(c1, c3)) {
                    cout << "Discarding " << cardToString(c1) << " and " << cardToString(c3) << endl;
                    it = cards_.erase(it);
                    it = cards_.erase(it + 1);
                    is_discarded = true;
                    iterator++;
                    cout << "iterator " << iterator << endl;
                    break;
                }
                else {
                    returnCardsToDeck(c1, c2, c3);
                    iterator++;
                    cout << "iterator " << iterator << endl;
                    if (it != cards_.end()) it++; else break;
                }
                if (it + 2 != cards_.end()) {
                    it++;
                }
                /*cout << "iterator " << iterator << endl;*/
                cout << "size: " << size_t() << endl;
            }
 /*           cout << "size: " << size_t() << endl;*/
        }
    }
protected:
    bool isTwoExtremesSameColor(const Card& c1, const Card& c3) {
        if ((c1.getSuit() == Card::Hearts || c1.getSuit() == Card::Diamonds) &&
            (c3.getSuit() == Card::Hearts || c3.getSuit() == Card::Diamonds)) {
            return true;
        }
        if ((c1.getSuit() == Card::Clubs || c1.getSuit() == Card::Spades) &&
            (c3.getSuit() == Card::Clubs || c3.getSuit() == Card::Spades)) {
            return true;
        }
        return false;
    }
    string cardToString(const Card& c) {
        string s;
        switch (c.getRank()) {
        case Card::Ace: s = "Ace"; break;
        case Card::Two: s = "2"; break;
        case Card::Three: s = "3"; break;
        case Card::Four: s = "4"; break;
        case Card::Five: s = "5"; break;
        case Card::Six: s = "6"; break;
        case Card::Seven: s = "7"; break;
        case Card::Eight: s = "8"; break;
        case Card::Nine: s = "9"; break;
        case Card::Ten: s = "10"; break;
        case Card::Jack: s = "Jack"; break;
        case Card::Queen: s = "Queen"; break;
        case Card::King: s = "King"; break;
        }
        switch (c.getSuit()) {
        case Card::Clubs: s += " of Clubs"; break;
        case Card::Diamonds: s += " of Diamonds"; break;
        case Card::Hearts: s += " of Hearts"; break;
        case Card::Spades: s += " of Spades"; break;
        }
        return s;
    }
};

int main()
{
    std::cout << "Hello World!\n";
    Solitaire game;
    game.play();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
