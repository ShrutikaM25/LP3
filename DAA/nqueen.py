
def check_columns(board, row, column):
    for i in range(row, -1, -1):
        if (board[i][column] == 1):
            return False
    return True


def check_diagonal(board, row, column):
    for i,j in zip(range(row, -1, -1), range(column, -1, -1)):
        if board[i][j] == 1:
            return False
        
    for i,j in zip(range(row, -1, -1), range(column, n)):
        if board[i][j] == 1:
            return False
    
    return True


def nqueenRec(board, row):
    if row == n:
        return True
    for i in range(n):
        if (check_columns(board, row, i) == True and check_diagonal(board, row, i) == True):
            board[row][i] = 1
            if nqueenRec(board, row+1) == True:
                return True
            board[row][i] = 0
    
    return False

def calculate_conflicts(column):
    conflicts = 0
    for i in range(len(column)):
        for j in range(i + 1, len(column)):
            if column[i] == column[j] or abs(column[i] - column[j]) == abs(i - j):
                conflicts += 1
    return conflicts

def nqueenBnbWithBound(board, row, column):
    global min_conflicts
    if row == n:
        conflicts = calculate_conflicts(column)
        if conflicts < min_conflicts:
            min_conflicts = conflicts
            for i in range(n):
                board[i][column[i]] = 1
            return True
        return False

    for i in range(n):
        if check_columns(board, row, i) and check_diagonal(board, row, i):
            column[row] = i
            board[row][i] = 1
            if nqueenBnbWithBound(board, row + 1, column):
                return True
            board[row][i] = 0
    return False

n = int(input("Enter the value of n: "))
board = [[0 for i in range(n)] for i in range(n)]

for row in board:
    print(row)

column = [-1] * n
min_conflicts = float('inf')
nqueenBnbWithBound(board, 0, column)

print('N Queen Problem: ')
for row in board:
    print(row)

# nqueenRec(board, 0)
# print('N Queen Problem: ')
# for row in board:
#     print(row)

