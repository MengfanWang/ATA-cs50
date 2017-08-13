import cs50
import sys

def main():
    if len(sys.argv) != 2 or not(sys.argv[1].isalpha()):
        print("Usage: ./vigenere k")
        return (1)
    else:
        key = sys.argv[1].upper()
        print("plaintext: ", end="")
        text = cs50.get_string()
        print("ciphertext: ", end="")
        i = 0
        for c in text:
            k = ord(key[i%len(key)]) - 65
            if c.isalpha() and c.isupper():
                position = (ord(c) - 65 + k) % 26
                print(chr(position + 65), end="")
                i += 1
            elif c.isalpha and c.islower():
                position = (ord(c) - 97 + k) % 26
                print(chr(position + 97), end="")
                i += 1
            else:
                print(c, end="")
        print()
        return (0)   
    
    
if __name__ == "__main__":
    main()