import sys

mem = dict()
inf = sys.maxint
mat = list


def init(p):

    n = len(p)
    global mat
    mat = p

    for i in range(1, n):
        for j in range(1, n):

            key = str(i) + "," + str(j)

            if i == j: mem.update({key: 0})
            else: mem.update({key: inf})


def clean():
    mem.clear()


def MatrixChainOrder(i, j):

    key = str(i) + "," + str(j)

    if mem[key] < inf: return mem[key]
    else:
        for k in range(i, j):

            q = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + mat[i - 1] * mat[k] * mat[j]

            if q < mem[key]: mem[key] = q

    return mem[key]
