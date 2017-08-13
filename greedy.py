import cs50

while True:
    print("O hai! How much change is owed?")
    change = cs50.get_float()
    if change > 0:
        break

change_cents = round(change*100)  
coins = 0
for i in (25, 10, 5, 1):
    coins = change_cents // i + coins
    change_cents = change_cents % i
    
print(coins)