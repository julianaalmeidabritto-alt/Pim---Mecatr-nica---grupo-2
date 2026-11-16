# PIM Mecatrônica - Grupo 2

Projeto Integrado Multidisciplinar com o robô bípede Otto DIY e prototipagem de retroescavadeira articulada.  
**Disciplina:** Informática Aplicada | **Docente:** Prof. Dr. Robson Marinho da Silva | **Instituição:** UNEB — Engenharia Civil

## 👥 Integrantes
- Juliana Almeida
- Luan Pereira
- Marcelo Custódio

---

## 📑 Índice
- [Fase 1: Robô Otto DIY](#-fase-1-montagem-programação-e-modelagem-do-otto)
- [Fase 2: Retroescavadeira 4-DoF](#-fase-2-proposta-do-projeto-mecatrônico-retroescavadeira)
- [Modelagem com Redes de Petri](#-modelagem-com-redes-de-petri--projeto-retroescavadeira)
  - [Etapa 1: HPSim e Python](#etapa-1-rede-de-petri-lugar-transição-e-álgebra-linear-hpsim--python)
  - [Etapa 2: CPN Tools](#etapa-2-rede-de-petri-colorida-cpn-tools)

---

## 🤖 Fase 1: Montagem, programação e modelagem do Otto

Montagem do robô Otto DIY com Arduino Nano, shield de expansão, 4 servomotores SG90, sensor ultrassônico HC-SR04 e buzzer, com estrutura impressa em 3D.

### Estrutura de Arquivos (`fase-1/`)
- `fase-1/relatorios/`: relatórios técnicos `AV1_P1` a `AV1_P4` (montagem, ligações, calibração e testes, modelagem da dança).
- `fase-1/codigo/`: código `OttoS_BLE.ino` gravado no robô (Arduino Nano), com controle por Bluetooth e três funções novas: valsa (Rede de Petri), corrida de obstáculos e inspetor com sensor ultrassônico (estados, alerta sonoro e botão virtual por proximidade).
- `fase-1/Rede petri danca/`: Rede de Petri da *"Valsa do Otto"* (arquivo HPSim).
- `fase-1/Rede petri aplicacao na engenharia/`: Rede de Petri do *Sistema de Vigilância Otto* (mapeamento, vigilância e alerta).

### Vídeos dos Testes
- [Vídeo 1 — Teste de movimentação e sensores](https://drive.google.com/file/d/1ZWeRxMEs-itds_s8hMKcQkS-vprJxjhR/view)
- [Vídeo 2 — Execução das rotinas e modos de operação](https://drive.google.com/file/d/1HO5cToMnC6fx4-v974Nx6B1jUZ8hcoKo/view)

---

## 🚜 Fase 2: Proposta do Projeto Mecatrônico (Retroescavadeira)

### 📋 Visão Geral da Fase 2

Este repositório contém a documentação técnica da **Fase 2 do Projeto de Prototipagem para Inovação Mecatrônica (PIM - AV2_P1)**.

O projeto consiste na concepção e no detalhamento de uma **Retroescavadeira Mecatrônica Articulada de 4 Graus de Liberdade (4-DoF)**, voltada à automação, à precisão geométrica e à redução de riscos operacionais na Engenharia Civil. Todas as peças estruturais serão novas, projetadas e impressas em 3D no **INOVAMECH**.

**Ciclo de operação:** recebe a ordem de coleta, coleta o material, leva ao local de descarga, deposita e aguarda a próxima ordem.

---

### 📑 Estrutura da Documentação (`fase-2/documentos/`)

| Arquivo | Tópico | Descrição do conteúdo |
| :--- | :--- | :--- |
| 📄 `Proposta do Projeto (Tópico 2) (1).pdf` | **2. Proposta do Projeto** | Problema na Engenharia Civil, objetivos, solução mecânica (PLA, tirantes de aço inox Ø1,5 mm, juntas, giro da torre e caçamba em V), modelagem preliminar no Fusion 360 e funcionalidades esperadas. |
| 📄 `Arquitetura Mecatrônica do Sistema (Tópico 3)...pdf` | **3. Arquitetura Mecatrônica** | Componentes e materiais (Arduino Nano, servos MG995/SG90, sensor HC-SR04, eixos M3 e buchas de latão), diagrama de blocos e integração entre mecânica, eletrônica, controle e segurança. |
| 🔷 `Rede_Petri_Retroescavadeira.hps` | **4. Modelagem inicial** | Rede de Petri do ciclo da retroescavadeira (arquivo HPSim na pasta `simulacoes`). O diagrama funcional encontra-se detalhado no tópico 3. |
| 📄 `Viabilidade do Projeto (Tópico 5).pdf` | **5. Viabilidade do Projeto** | Justificativa dos materiais (PLA, aço inox M3, servos MG995/SG90, Arduino), recursos disponíveis no INOVAMECH, tempo estimado de impressão 3D (18 a 22 horas), ciclo PIM de execução e ações preventivas (capacitores de 470 µF e lubrificação com PTFE). |

---

### 🛠️ Tecnologias e Ferramentas Utilizadas

- **CAD / Prototipagem:** Autodesk Fusion 360
- **Manufatura Aditiva:** Impressão 3D FDM (PLA)
- **Controle e Processamento:** Arduino Nano (C/C++, `Servo.h`)
- **Atuadores e Sensores:** Servomotores MG995 e SG90, sensor ultrassônico HC-SR04
- **Modelagem e Simulação:** HPSim, CPN Tools e Python (NumPy)

---

## 📐 Modelagem com Redes de Petri — Projeto Retroescavadeira

Documentação técnica das modelagens, formulação matricial e simulações computacionais desenvolvidas para o ciclo operacional do braço mecânico articulado (retroescavadeira).

### Estrutura de Arquivos (`fase-2/`)
- 📄 `fase-2/documentos/Relatório Técnico - Redes de Petri .pdf` — Relatório técnico completo contendo a formulação matemática, modelagem no HPSim, simulação em Python e modelagem de alto nível no CPN Tools.
- 🐍 `fase-2/codigo-python/rede_petri.py` — Script em Python (NumPy) para cálculo das matrizes e simulação da evolução das marcações (`M0` a `M5`).
- 🖼️ `fase-2/codigo-python/rede_petri.re..png` — Captura da saída de execução no terminal validando as matrizes `Pre`, `Post`, `C` e a evolução das marcações.
- 🔷 `fase-2/simulacoes/Rede Petri _Retro.hps` — Modelagem da Rede de Petri Lugar-Transição no software **HPSim**.
- 🎨 `fase-2/simulacoes/Rede Petri_Escavadeira_Final_colorida.cpn` — Modelagem da Rede de Petri Colorida no software **CPN Tools**.

---

### Etapa 1: Rede de Petri Lugar-Transição e Álgebra Linear (HPSim + Python)

Rede composta por **6 lugares** (`P1` a `P6`) e **5 transições** (`T1` a `T5`) representando o ciclo contínuo e reversível da retroescavadeira (livre de *deadlocks*):
- **Lugares:** `P1_Início`, `P2_Pós_Braço`, `P3_Escavar`, `P4_Girar Torre`, `P5_Despejar`, `P6_FIM`.
- **Transições:** `T1_Posicionar`, `T2_Transição(Decisão)` (paralelismo), `T3_Sincronização`, `T4_Finalizar`, `T5_Aguardando` (retorno cíclico).

#### Matrizes de Entrada (`Pre`), Saída (`Post`) e Incidência (`C = Post - Pre`)

| Lugar | `Pre` (`T1` ... `T5`) | `Post` (`T1` ... `T5`) | `C = Post - Pre` (`T1` ... `T5`) |
| :--- | :---: | :---: | :---: |
| **P1 (Início)** | `[1, 0, 0, 0, 0]` | `[0, 0, 0, 0, 1]` | `[-1,  0,  0,  0,  1]` |
| **P2 (Pós_Braço)** | `[0, 1, 0, 0, 0]` | `[1, 0, 0, 0, 0]` | `[ 1, -1,  0,  0,  0]` |
| **P3 (Escavar)** | `[0, 0, 1, 0, 0]` | `[0, 1, 0, 0, 0]` | `[ 0,  1, -1,  0,  0]` |
| **P4 (Girar Torre)** | `[0, 0, 1, 0, 0]` | `[0, 1, 0, 0, 0]` | `[ 0,  1, -1,  0,  0]` |
| **P5 (Despejar)** | `[0, 0, 0, 1, 0]` | `[0, 0, 1, 0, 0]` | `[ 0,  0,  1, -1,  0]` |
| **P6 (FIM)** | `[0, 0, 0, 0, 1]` | `[0, 0, 0, 1, 0]` | `[ 0,  0,  0,  1, -1]` |

#### Evolução das Marcações (`M_k = M_{k-1} + C * sigma_k`)
- **M<sub>0</sub>:** `[1, 0, 0, 0, 0, 0]` — Habilitada: `['T1']`
- **M<sub>1</sub> (após T1):** `[0, 1, 0, 0, 0, 0]` — Habilitada: `['T2']`
- **M<sub>2</sub> (após T2):** `[0, 0, 1, 1, 0, 0]` — Habilitada: `['T3']` *(execução paralela em P3 e P4)*
- **M<sub>3</sub> (após T3):** `[0, 0, 0, 0, 1, 0]` — Habilitada: `['T4']` *(sincronização concluída)*
- **M<sub>4</sub> (após T4):** `[0, 0, 0, 0, 0, 1]` — Habilitada: `['T5']`
- **M<sub>5</sub> (após T5):** `[1, 0, 0, 0, 0, 0]` — Habilitada: `['T1']` *(retorno cíclico à marcação inicial)*

#### Execução e Validação em Python

```bash
pip install numpy
python fase-2/codigo-python/rede_petri.py
```

<details>
<summary><strong>📄 Ver código-fonte completo de <code>rede_petri.py</code></strong></summary>

```python
import numpy as np

LUGARES = ["P1", "P2", "P3", "P4", "P5", "P6"]
TRANSICOES = ["T1", "T2", "T3", "T4", "T5"]

# Pre: o que cada transição consome (linhas = lugares, colunas = transições)
Pre = np.array([
    [1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1]
])

# Post: o que cada transição produz
Post = np.array([
    [0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0]
])

# Matriz de incidência
C = Post - Pre

# Marcação inicial: 1 ficha em P1
M = np.array([[1], [0], [0], [0], [0], [0]])

print("Matriz Pre:\n", Pre)
print("Matriz Post:\n", Post)
print("Matriz de incidência C:\n", C)
print("M0:", M.ravel().tolist())


def habilitadas(M):
    return [t for j, t in enumerate(TRANSICOES) if np.all(M >= Pre[:, j:j+1])]


print("Habilitadas em M0:", habilitadas(M))

# Simulação de um ciclo completo
for k, t in enumerate(["T1", "T2", "T3", "T4", "T5"], start=1):
    j = TRANSICOES.index(t)
    if not np.all(M >= Pre[:, j:j+1]):
        raise ValueError(f"{t} não está habilitada")
    sigma = np.zeros((5, 1), dtype=int)
    sigma[j, 0] = 1
    M = M + C @ sigma
    print(f"M{k} após {t}:", M.ravel().tolist(), "| habilitadas:", habilitadas(M))
```

</details>

#### Saída da Simulação Computacional

![Saída da execução do script rede_petri.py](fase-2/codigo-python/rede_petri.re..png)

---

### Etapa 2: Rede de Petri Colorida (CPN Tools)

Modelagem de alto nível com rastreamento de atuadores, etapas intermediárias de comutação (`B>D Troca Atuador` e `C>D Troca Atuador`) e temporização das operações.

#### Declarações Globais (CPN ML)

```sml
(* Colorsets *)
colset ETAPA = with INICIO | POS_BRACO | ESCAVAR | GIRAR_TORRE | DESPEJAR | FIM;
colset ATU = with NSA | CIL_LANCA | CIL_BRACO | CIL_CONCHA | MOTOR_GIRO;
colset LISTA_ATU = list ATU;
colset RETRO_OP = product STRING * ETAPA * LISTA_ATU * INT * INT;

(* Variáveis *)
var id : STRING;
var etapa : ETAPA;
var atu_list : LISTA_ATU;
var dur, t, durE, tE, durG, tG : INT;

(* Função de Sincronização *)
fun maxTime(tE, durE, tG, durG) = Int.max(tE + durE, tG + durG);
```

#### Fluxo Temporal da Ficha (`"C1"`)

1. **Início (`INICIO`):**
   - Marcação inicial: `1` `("C1", INICIO, [NSA], 0, 0)`
2. **Transição `A` — Posicionamento (`A: POS_BRAÇO`):**
   - Saída: `("C1", POS_BRACO, [CIL_LANCA, CIL_BRACO], 3, 0)` *(duração: 3 u.t. a partir de t = 0)*
3. **Transição `>B>C` — Execução Paralela (`B` e `C`):**
   - **B (`B: ESCAVAR`):** `("C1", ESCAVAR, [CIL_BRACO, CIL_CONCHA], 5, 3)` *(duração: 5 u.t., término em t = 8 u.t.)*
   - **C (`C: GIRAR TORRE`):** `("C1", GIRAR_TORRE, [MOTOR_GIRO], 4, 3)` *(duração: 4 u.t., término em t = 7 u.t.)*
4. **Transições `B>D` e `C>D` — Troca de Atuadores:**
   - **Lugar `B>D Troca Atuador`:** `("C1", ESCAVAR, [CIL_CONCHA], 5, 3)`
   - **Lugar `C>D Troca Atuador`:** `("C1", GIRAR_TORRE, [CIL_CONCHA], 4, 3)`
5. **Transição `>D` — Sincronização Temporal (`DESPEJAR`):**
   - Cálculo: `maxTime(3, 5, 3, 4) = Int.max(8, 7) = 8`
   - Saída: `("C1", DESPEJAR, [CIL_CONCHA], 2, 8)` *(início em t = 8 u.t., duração: 2 u.t.)*
6. **Transição `>Fim` — Encerramento (`FIM`):**
   - Saída: `("C1", FIM, [NSA], 0, 10)` *(tempo total do ciclo: 10 u.t.)*
