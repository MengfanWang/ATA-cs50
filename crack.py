import cs50
import crypt
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: ./crack hash\n")
        return(1)
        
    dictonary = []
    for i in range(65, 91):
        dictonary.append(chr(i))
        dictonary.append(chr(i+32))
    
    for i in dictonary:
        if sys.argv[1] == crypt.crypt(i, "50"):
            print(i)
            return(0)
        else:
            for j in dictonary:
                if sys.argv[1] == crypt.crypt(i+j, "50"):
                    print(i+j)
                    return(0)
                else:
                    for k in dictonary:
                        if sys.argv[1] == crypt.crypt(i+j+k, "50"):
                            print(i+j+k)
                            return(0)
                        else:
                            for l in dictonary:
                                if sys.argv[1] == crypt.crypt(i+j+k+l, "50"):
                                    print(i+j+k+l)
                                    return(0)

                                    
if __name__ == "__main__":
    main()