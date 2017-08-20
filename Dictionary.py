#!/usr/bin/env python

class Node:
    def __init__(self):
        self.word = None
        self.nodes = {}
        
    def __insert__(self, word, wordVal):
        if len(word) == 0:
            self.word = wordVal;
            return;
        currentChar = word[0]
        if currentChar not in self.nodes:
            self.nodes[currentChar] = Node()
        word = word[1:]
        self.nodes[currentChar].__insert__(word, wordVal)
        
    def __searchPrefix__(self, prefix):
        if len(prefix) == 0:
            return self
        currentChar = prefix[0]
        if currentChar not in self.nodes:
            return None
        else:
            node = self.nodes[currentChar]
            return node.__searchPrefix__(prefix[1:])
    
    def __findWords__(self):
        words = []
        if self.word is not None:
            words.append(self.word)
        if self.nodes != {}:
            for i in self.nodes:
                words += self.nodes[i].__findWords__()
        return words
      
            
        
def main():
    
    userInput = input("Prefix to Search: ")
    prefix = isValid(userInput)
    
    root = Node()
    with open('./dictionary.txt', 'r+') as reader:
        for line in reader:
            line = line.rstrip('\n') 
            Node.__insert__(root, line, line)
    
    if root.__searchPrefix__(prefix) is None:
        print("not found")
        return 0
    node = root.__searchPrefix__(prefix)
    
    print(node.__findWords__()[:5])


def isValid(userInput):
    while not userInput.isalpha():
        userInput = input("retry: ")
    return userInput
    
if __name__ == "__main__":
    main()
    
    
