from typing import List, Optional
import random


class Card:
    def __init__(self, value, suit) -> None:
        self.face = value
        face_cards = {"A": 11, "J": 10, "Q": 10, "K": 10}
        if value in face_cards:
            self.value = face_cards[value]
        else:
            self.value = int(value)

        self.suit = suit

    def __str__(self) -> str:
        return self.face + self.suit


class Deck:
    def __init__(self) -> None:
        self.deck = []
        for value in ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]:
            for suit in ["♠", "♦", "♣", "♥"]:
                self.deck.append(str(Card(value, suit)))
        
        
    
    def deal_card(self):
        dealt = random.choice(self.deck)
        self.deck.remove(dealt)
    
    def __len__(self):
        return len(self.deck)
    
    def __iter__(self):
        return iter(self.deck)
    
    def __contains__(self, card):
        self.card = card
        for card in self.deck:
            return self.deck.__contains__(card)


    
    


class Hand:
    def __init__(
        self, cards: Optional[List[Card]] = None, dealer=False, interactive=False
    ):
        self.cards = cards
        self.hand = []
        self.total = 0

    def add_card(self, card:Card):
        self.total += card.value
        self.hand.append(card)

    def score(self):
        for card in self.hand:
            if card.value == 11 and self.total > 21:
                self.total -= 10
        
        if self.total > 21:
            print("Bust")
         
        
        return self.total
    
    def has_blackjack(self):
        if self.total == 21:
            return self.total
    
    def __len__(self):
        return len(self.hand)

class Game:
    def __init__(self, num_players=1):
        pass


def main():
    print("Welcome to blackjack!")
    deck = Deck()
    print(len(deck))
    deck.deal_card()
    print(len(deck))



if __name__ == "__main__":
    main()
