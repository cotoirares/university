def solution(S):
    cnt = 0
    for i in range(0, 10):
        for j in range(0, 10):
            for k in range(0, 10):
                for m in range(0, 10):
                    if i + j + k + m == S:
                        cnt += 1
    return cnt

def main():
    S = int(input())
    print(solution(S))

if __name__ == "__main__":
    main()