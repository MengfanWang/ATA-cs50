import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: ./caesar k")
        return (1)
    else:
        key = int(sys.argv[1])
        print("plaintext: ", end="")
        text = cs50.get_string()
        print("ciphertext: ", end="")
        for c in text:
            if c.isalpha() and c.isupper():
                position = (ord(c) - 65 + key) % 26
                print(chr(position + 65), end="")
            elif c.isalpha and c.islower():
                position = (ord(c) - 97 + key) % 26
                print(chr(position + 97), end="")
            else:
                print(c, end="")
        print()
        return (0)

if __name__ == "__main__":
    main()

    
