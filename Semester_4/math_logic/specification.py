import sys
from itertools import combinations
# ==================================================
# | Magma               | any                      |
# | Semigroup           | associativity            |
# | Monoid              | semigroup + with neutral |
# | Group               | Monoid + inverse element |
# | Commutative monoid  | Monoid + commutativity   |
# | Abelian group       | Group + commutativity    |
# ==================================================


def check_association(c):
    n = len(c)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                if c[c[i][j]][k] != c[i][c[j][k]]:
                    return False
    return True


def find_neutral(c):
    for i in range(len(c)):
        flag = True
        for j in range(len(c)):
            if c[i][j] != j or c[j][i] != j:
                flag = False
                break
        if flag:
            return True, i
    return False, None


def check_inversed(c, neutral):
    print(neutral)
    for i in range(len(c)):
        inv_exist = False
        for j in range(len(c)):
            if c[i][j] == neutral and c[j][i] == neutral:
                inv_exist = True
                break
        if not inv_exist:
            return False
    return True


def check_commutativity(c):
    for i in range(len(c)):
        for j in range(len(c)):
            if c[j][i] != c[i][j]:
                return False
    return True


if __name__ == '__main__':
    if len(sys.argv) == 2:
        f = open(sys.argv[1], 'r')
    else:
        f = open('test', 'r')
    cayley_table = [[int(x) for x in line.split(' ')] for line in f.readlines()]

    if not check_association(cayley_table):
        print("Magma")
        exit(0)
    is_neutral, n = find_neutral(cayley_table)
    if not is_neutral:
        print("Semigroup")
        exit(0)
    inversed = check_inversed(cayley_table, n)
    commutativity = check_commutativity(cayley_table)
    print()
    if inversed:
        if commutativity:
            print("Abelian group ")
        else:
            print("Group")
    elif commutativity:
        print("Commutative monoid")
    else:
        print("Monoid")
