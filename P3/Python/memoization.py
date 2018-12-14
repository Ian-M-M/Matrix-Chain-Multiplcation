import sys

mem = dict()
inf = sys.maxint
mat = list

"""
    init => funcion que inicializa el dictionary
"""


def init(p):

    n = len(p)
    global mat
    mat = p

    for i in range(1, n):
        for j in range(1, n):

            key = str(i) + "," + str(j)
            # En la 'diagonal' colocamos 0
            if i == j: mem.update({key: 0})
            # El resto lo llenamos del valor maximo del integer
            else: mem.update({key: inf})


"""
    clean => funcion que vacia el dictionary
"""


def clean():
    mem.clear()


"""
    MatrixChainOrder => funcion que contiene el algoritmo de memoization
"""


def MatrixChainOrder(i, j):
    # Creamos la key del dictionary
    key = str(i) + "," + str(j)
    # Comprobamos si ya hemos calculado el valor para dicha key
    if mem[key] < inf: return mem[key]
    else:
        # Calculamos el valor de la key
        for k in range(i, j):

            q = MatrixChainOrder(i, k) + MatrixChainOrder(k + 1, j) + mat[i - 1] * mat[k] * mat[j]

            if q < mem[key]: mem[key] = q

    return mem[key]
