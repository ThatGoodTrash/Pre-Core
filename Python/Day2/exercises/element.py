class Element:
    def __init__(self, name:str, symbol:str, number:int) -> None:
        self.name = name
        self.symbol = symbol
        self.number = number

    def dump(self):
        print(self.name + " : " + self.symbol + " : " + str(self.number))


h = Element("Hydrogen", "H", 1)

h.dump()
