def compute(n:int):
    print((n * (5 ** (n ** (1//5))) - n) // (5 ** (n ** (1//5)) * 4))

if __name__ == "__main__":
    n = input()
    compute(int(n))

