import cs50

def main():
    print("Number: ", end="")    
    cardNumber = cs50.get_float()
    printType(cardNumber)
    
def isValidCard(cardNumber):
    cNumber = cardNumber
    isOdd = True
    sum = 0
    while cNumber > 0:
        digit = cNumber % 10
        if isOdd:
            sum += digit;
        else:
            temp = digit*2
            if temp > 9:
                temp = 1 + temp%10
            sum += temp
        cNumber = cNumber // 10
        isOdd = not(isOdd)
    return (sum%10 == 0)
    
def printType(cardNumber):
    if isValidCard(cardNumber):
        while cardNumber > 100:
            cardNumber = cardNumber // 10
        if cardNumber == 34 or cardNumber == 37:
            print("AMEX")
        elif cardNumber >= 51 and cardNumber <= 55:
            print("MASTERCARD")
        elif cardNumber >= 40 and cardNumber <= 49:
            print("VISA")
        else:
            print("INVALIDCARDTYPE")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
