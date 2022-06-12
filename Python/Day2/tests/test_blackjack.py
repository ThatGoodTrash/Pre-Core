from ..exercises.blackjack import Deck, Card, Hand


def test_card():
    card_one = Card("5", "♣")
    assert card_one.value == 5
    assert card_one.suit == "♣"

    card_two = Card("A", "♣")
    assert card_two.value == 11
    assert card_two.suit == "♣"
    assert str(card_two) == "A♣"


def test_deck():
    deck = Deck()
    assert len(deck) == 52

    for value in ["2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"]:
        for suit in ["♠", "♦", "♣", "♥"]:
            assert Card(value, suit) in deck

    _ = deck.deal_card()
    assert len(deck) == 51


def test_hand():
    hand = Hand()
    card_one = Card("5", "♣")
    hand.add_card(card_one)

    card_two = Card("A", "♣")
    hand.add_card(card_two)

    assert len(hand) == 2
    assert hand.score() == 16


def test_blackjack_two_cards():
    hand = Hand()
    card_one = Card("J", "♣")
    hand.add_card(card_one)

    card_two = Card("A", "♣")
    hand.add_card(card_two)

    assert len(hand) == 2
    assert hand.score() == 21

    assert hand.has_blackjack()


def test_ace_works_both_ways():
    hand = Hand()
    card_one = Card("10", "♣")
    hand.add_card(card_one)

    card_two = Card("A", "♣")
    hand.add_card(card_two)

    card_three = Card("10", "♠")
    hand.add_card(card_three)

    assert len(hand) == 3
    assert hand.score() == 21
