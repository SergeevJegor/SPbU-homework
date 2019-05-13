import pycosat
import sys


def encode(i, j, v):
    # Variable cannot be 0 (due to lib docs)
    return 81 * i + 9 * j + v + 1


def decode(val):
    return (val - 1) // 81, (val - 1) // 9 % 9, (val - 1) % 9


def solve(field):
    clauses = sudoku_clauses()
    # Add field's clauses:
    for i in range(9):
        for j in range(9):
            v = field[i][j]
            if v:
                clauses.append([encode(i, j, v - 1)])
    # Find SAT solution with pycosat lib:
    result = pycosat.solve(clauses)
    if result == 'UNSAT' or result == 'UNKNOWN':
        return []
    result = [x for x in result if x > 0]
    # print(result)
    # Refactor result to matrix:
    res_matrix = [[0 for i in range(9)] for j in range(9)]
    for ans in result:
        i, j, val = decode(ans)
        res_matrix[i][j] = val + 1
    return res_matrix


def sudoku_clauses():
    clauses = []
    for i in range(9):
        for j in range(9):
            # Any cell should be a digit:
            clauses.append([encode(i, j, k) for k in range(9)])
            # Any digit should be in any column:
            clauses.append([encode(i, k, j) for k in range(9)])
            # Any digit should be in any line:
            clauses.append([encode(k, i, j) for k in range(9)])
            for k1 in range(9):
                for k2 in range(k1 + 1, 9):
                    # NOT(x1 AND x2) == NOT x1 OR NOT x2
                    # Cell cannot have duplicated values:
                    clauses.append([-encode(i, j, k1), -encode(i, j, k2)])
                    # Line cannot have duplicated values:
                    clauses.append([-encode(i, k1, j), -encode(i, k2, j)])
                    # Column cannot have duplicated values:
                    clauses.append([-encode(k1, i, j), -encode(k2, i, j)])

    # Block cannot have duplicated values:
    for x in range(3):
        for y in range(3):
            for k1 in range(9):
                i1 = x * 3 + k1 // 3
                j1 = y * 3 + k1 % 3
                # Any digit should be in any block:
                clauses.append([encode(i1, j1, v) for v in range(9)])
                for k2 in range(k1 + 1, 9):
                    i2 = x * 3 + k2 // 3
                    j2 = y * 3 + k2 % 3
                    for v in range(9):
                        # NOT(x1 AND x2) == NOT x1 OR NOT x2
                        clauses.append([-encode(i1, j1, v), -encode(i2, j2, v)])
    return clauses


def format_input(name):
    lines = open(name, "r").read().split('\n')
    return [[int(x) if x != '.' else 0 for x in line] for line in lines]


def format_output(field):
    ans = ''
    for i in range(9):
        for j in range(9):
            ans = ans + str(field[i][j])
        if i < 8:
            ans = ans + '\n'
    return ans


if __name__ == '__main__':
    # answer = solve(format_input('test1'))
    if len(sys.argv) == 2:
        name = sys.argv[1]
    else:
        name = 'test1'
    answer = solve(format_input(sys.argv[1]))
    if answer:
        print(format_output(answer))
    else:
        print('Can\'t solve ')

