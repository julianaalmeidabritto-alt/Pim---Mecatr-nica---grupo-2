import numpy as np

LUGARES = ["P1","P2","P3","P4","P5","P6"]
TRANSICOES = ["T1","T2","T3","T4","T5"]

# Pre: o que cada transição consome (linhas = lugares, colunas = transições)
Pre = np.array([[1,0,0,0,0],
                [0,1,0,0,0],
                [0,0,1,0,0],
                [0,0,1,0,0],
                [0,0,0,1,0],
                [0,0,0,0,1]])

# Post: o que cada transição produz
Post = np.array([[0,0,0,0,1],
                 [1,0,0,0,0],
                 [0,1,0,0,0],
                 [0,1,0,0,0],
                 [0,0,1,0,0],
                 [0,0,0,1,0]])

# Matriz de incidência
C = Post - Pre

# Marcação inicial: 1 ficha em P1
M = np.array([[1],[0],[0],[0],[0],[0]])

print("Matriz Pre:\n", Pre)
print("Matriz Post:\n", Post)
print("Matriz de incidência C:\n", C)
print("M0:", M.ravel().tolist())

def habilitadas(M):
    return [t for j, t in enumerate(TRANSICOES)
            if np.all(M >= Pre[:, j:j+1])]

print("Habilitadas em M0:", habilitadas(M))

# Simulação de um ciclo completo
for k, t in enumerate(["T1","T2","T3","T4","T5"], start=1):
    j = TRANSICOES.index(t)
    if not np.all(M >= Pre[:, j:j+1]):
        raise ValueError(f"{t} não está habilitada")
    sigma = np.zeros((5,1), dtype=int)
    sigma[j,0] = 1
    M = M + C @ sigma
    print(f"M{k} após {t}:", M.ravel().tolist(),
          "| habilitadas:", habilitadas(M))
