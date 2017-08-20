import sys

#userInput = [8, 7, 1, 3, 4, 4, 9, 5, 6, 2]

def main():
    userInput = input("List of Numbers(1,2,3..): ")
    inputList = isValid(userInput)
    output = quickSort(inputList)
    print(output)

def isValid(userInput):
    iList = userInput.split(",")
    inputList = []
    for i in iList:
        if not i.isdigit():
            userInput = input("retry(1,2,3..): ")
            return isValid(userInput)
        else:
            inputList.append(int(i))
    return inputList
    
def quickSort(inputList):  
    if len(inputList) <= 1:
        return inputList
    index = len(inputList) // 2
    pivot = inputList[index]
    lessList = []
    moreList = []
    pivotList = []
    
    for i in inputList:
        if i < pivot:
            lessList.append(i)
        elif i > pivot:
            moreList.append(i)
        elif i == pivot:
            pivotList.append(i)   
    
    return quickSort(lessList) + pivotList + quickSort(moreList)
    
    
if __name__ == "__main__":
    main()