"""
Hamiltonian Path

Author: Rares Cotoi, @ 912
"""
def hamiltonian_path(adj, N):
    dp = [[False for i in range(1 << N)]
          for j in range(N)]
    # dp[j][i] represents whether there exists a path in the subset or not represented by the mask i that visits
    # each and every vertex in i once and ends at vertex j
    for i in range(N):
        dp[i][1 << i] = True
    for i in range(1 << N):
        for j in range(N):
            if ((i & (1 << j)) != 0):
                for k in range(N):
                    if ((i & (1 << k)) != 0 and adj[k][j] == 1 and j != k and dp[k][i ^ (1 << j)]):
                        dp[j][i] = True
                        break

    for i in range(N):
        if (dp[i][(1 << N) - 1]):
            return True
    return False


def test_hamiltonian_path():
    assert hamiltonian_path([[0, 1, 0], [1, 0, 1], [0, 1, 0]], 3) == True
    assert hamiltonian_path([[0, 1, 0], [1, 0, 1], [0, 1, 0]], 3) == True
    assert hamiltonian_path([[0, 1, 1], [1, 0, 1], [1, 1, 0]], 3) == True
    assert hamiltonian_path([[0, 1, 1], [1, 0, 1], [1, 1, 0]], 3) == True
    assert hamiltonian_path([[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 1], [0, 1, 1, 0]], 4) == True
    assert hamiltonian_path([[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 1], [0, 1, 1, 0]], 4) == True
    assert hamiltonian_path([[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 1], [0, 1, 1, 0]], 4) == True
    assert hamiltonian_path([[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 1], [0, 1, 1, 0]], 4) == True

def main():
    test_hamiltonian_path()
    print("Tests passed")
    file_input = open("input.txt", "r")
    N = int(file_input.readline())
    adj = []
    for i in range(N):
        adj.append(list(map(int, file_input.readline().split())))
    if (hamiltonian_path(adj, N)):
        print("YES")
    else:
        print("NO")

main()