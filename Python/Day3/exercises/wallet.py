# wallet.py


class InsufficientAmount(Exception):
    def __init__(self, balance, message="You do not have enough money") -> None:
        self.balance = balance
        self.message = message
        super().__init__(self.message)


class Wallet:
    """Models a physical wallet. You can't have negative money"""

    def __init__(self, initial_amount: int = 0):
        self.balance: int = initial_amount

    def spend_cash(self, amount: int) -> None:
        if self.balance > amount:
            self.balance -= amount
        else:
            raise InsufficientAmount(self.balance)
        

    def add_cash(self, amount: int) -> None:
        self.balance += amount

    def __str__(self) -> str:
        return f"{self.balance}"

    def __repr__(self) -> str:
        return f"Wallet(balance={self.balance})"
