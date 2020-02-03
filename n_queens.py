from jutge import read
'''
N-queens
'''

class Board:
    def __init__(self, N):
        self.N = N
        self.Chess = dict()

        for row in range(N):
            self.Chess[row] = N*[0]

    def __str__(self):
        for k in self.Chess:
            print(str(self.Chess[k]))

    def free(self, row, col):
        for i in range(row):
            if self.Chess[i][col]:
                return False
        for j in range(col):
            if self.Chess[row][j]:
                return False
        for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
            if self.Chess[i][j]: return False
        for i, j in zip(range(row, -1, -1), range(col, self.N)):
            if self.Chess[i][j]: return False
        return True

    def put_q(self, row, col):
        self.Chess[row][col] = 1

    def remove_Q(self, row, col):
        self.Chess[row][col] = 0

def attempt(row, board, size):
    if row == size:
        board.draw() #This function has not been implemented yet.
    else:
        for column in range(size):
            if board.free(row, column):
                board.put_q(row, column) #put the queen
                attempt(row+1, board, size) #skipping the current row, to move down in the tree
                board.remove_Q(row, column) #remove the queen because we are doing the for loop by column, so it will keep tracking all possibilities

def attempt2(row, board, size):
    if row == size: #same queens than rows
        return True ##if I get to the end return true
    else:
        for column in range(size): #check all columns
            if board.free(row, column):
                board.put_q(row, column)
                s = attempt2(row + 1, board, size) #value that returns true (row = size)
                if s:
                    return True
                else:
                    board.remove_Q(row, column)
        return False #non of the branches found a solution


print('How many queens? ')
N = read(int)
board = Board(N)
print("The empty chess board: \n")
board.__str__()
print()
attempt2(0, board, N)
print()
print("One solution of the N-Queen: \n ")
board.__str__()
