# PIM Mecatrônica - Grupo 2

Projeto Integrado Multidisciplinar com o robô bípede Otto DIY e prototipagem de retroescavadeira articulada.  
**Disciplina:** Informática Aplicada | **Docente:** Prof. Dr. Robson Marinho da Silva | **Instituição:** UNEB — Engenharia Civil

## 👥 Integrantes
- Juliana Almeida
- Luan Pereira
- Marcelo Custódio

---

## 🤖 Fase 1: Montagem, programação e modelagem do Otto

Montagem do robô Otto DIY com Arduino Nano, shield de expansão, 4 servomotores SG90, sensor ultrassônico HC-SR04 e buzzer, com estrutura impressa em 3D.

### Estrutura de Arquivos (Fase 1)
- `fase-1/relatorios/`: relatórios técnicos `AV1_P1` a `AV1_P4` (montagem, ligações, calibração e testes, modelagem da dança).
- `fase-1/codigo/`: código `OttoS_BLE.ino` gravado no robô (Arduino Nano), com controle por Bluetooth e três funções novas: valsa (Rede de Petri), corrida de obstáculos e inspetor com sensor ultrassônico (estados, alerta sonoro e botão virtual por proximidade).
- `fase-1/danca/`: Rede de Petri da *"Valsa do Otto"* (arquivo HPSim).
- `fase-1/aplicacao-na-engenharia/`: Rede de Petri do *Sistema de Vigilância Otto* (mapeamento, vigilância e alerta).

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

### 📑 Estrutura da Documentação

| Arquivo | Tópico | Descrição do conteúdo |
| :--- | :--- | :--- |
| 📄 `topico_2_proposta.pdf` | **2. Proposta do Projeto** | Problema na Engenharia Civil, objetivos, solução mecânica (PLA, tirantes de aço inox Ø1,5 mm, juntas, giro da torre e caçamba em V), modelagem preliminar no Fusion 360 e funcionalidades esperadas. |
| 📄 `topico_3_arquitetura.pdf` | **3. Arquitetura Mecatrônica** | Componentes e materiais (Arduino Nano, servos MG995/SG90, sensor HC-SR04, eixos M3 e buchas de latão), diagrama de blocos e integração entre mecânica, eletrônica, controle e segurança. |
| 🔷 `Rede_Petri_Retroescavadeira.hps` e `rede_petri_retroescavadeira.jpeg` | **4. Modelagem inicial** | Rede de Petri do ciclo da retroescavadeira (arquivo HPSim e imagem). O diagrama funcional encontra-se detalhado no tópico 3. |
| 📄 `topico_5_viabilidade.pdf` | **5. Viabilidade do Projeto** | Justificativa dos materiais (PLA, aço inox M3, servos MG995/SG90, Arduino), recursos disponíveis no INOVAMECH, tempo estimado de impressão 3D (18 a 22 horas), ciclo PIM de execução e ações preventivas (capacitores de 470 µF e lubrificação com PTFE). |

---

### 🛠️ Tecnologias e Ferramentas Utilizadas

- **CAD / Prototipagem:** Autodesk Fusion 360
- **Manufatura Aditiva:** Impressão 3D FDM (PLA)
- **Controle e Processamento:** Arduino Nano (C/C++, `Servo.h`)
- **Atuadores e Sensores:** Servomotores MG995 e SG90, sensor ultrassônico HC-SR04
- **Modelagem:** HPSim e CPN Tools (Redes de Petri)

---

## 📐 Modelagem com Redes de Petri — Projeto Retroescavadeira

Documentação técnica das modelagens, formulação matricial e simulações computacionais desenvolvidas para o ciclo operacional do braço mecânico articulado (retroescavadeira).

### Estrutura de Arquivos do Repositório
- `rede_petri.py` — Script em Python (NumPy) para cálculo das matrizes e simulação de evolução das marcações ($M_0$ a $M_5$).
- `Rede Petri _Retro.hps` — Modelagem da Rede de Petri Lugar-Transição no software **HPSim**.
- `Rede Petri_Escavadeira_Final_colorida.cpn` — Modelagem da Rede de Petri Colorida no software **CPN Tools**.

---

### Etapa 1: Rede de Petri Lugar-Transição e Álgebra Linear (HPSim + Python)

Rede composta por **6 lugares** ($P_1$ a $P_6$) e **5 transições** ($T_1$ a $T_5$) representando o ciclo contínuo da retroescavadeira:
- **Lugares:** `P1_Início`, `P2_Pós_Braço`, `P3_Escavar`, `P4_Girar Torre`, `P5_Despejar`, `P6_FIM`.
- **Transições:** `T1_Posicionar`, `T2_Transição(Decisão)` (paralelismo), `T3_Sincronização`, `T4_Finalizar`, `T5_Aguardando` (retorno cíclico).

#### Matrizes de Entrada ($Pre$), Saída ($Post$) e Incidência ($C = Post - Pre$)

| Lugar | $Pre$ ($T_1 \dots T_5$) | $Post$ ($T_1 \dots T_5$) | $C = Post - Pre$ ($T_1 \dots T_5$) |
| :--- | :---: | :---: | :---: |
| **P1 (Início)** | `[1, 0, 0, 0, 0]` | `[0, 0, 0, 0, 1]` | `[-1,  0,  0,  0,  1]` |
| **P2 (Pós_Braço)** | `[0, 1, 0, 0, 0]` | `[1, 0, 0, 0, 0]` | `[ 1, -1,  0,  0,  0]` |
| **P3 (Escavar)** | `[0, 0, 1, 0, 0]` | `[0, 1, 0, 0, 0]` | `[ 0,  1, -1,  0,  0]` |
| **P4 (Girar Torre)** | `[0, 0, 1, 0, 0]` | `[0, 1, 0, 0, 0]` | `[ 0,  1, -1,  0,  0]` |
| **P5 (Despejar)** | `[0, 0, 0, 1, 0]` | `[0, 0, 1, 0, 0]` | `[ 0,  0,  1, -1,  0]` |
| **P6 (FIM)** | `[0, 0, 0, 0, 1]` | `[0, 0, 0, 1, 0]` | `[ 0,  0,  0,  1, -1]` |

#### Evolução das Marcações ($M_k = M_{k-1} + C \cdot \sigma_k$)
- **$M_0$:** `[1, 0, 0, 0, 0, 0]` — Habilitada: `['T1']`
- **$M_1$ (após $T_1$):** `[0, 1, 0, 0, 0, 0]` — Habilitada: `['T2']`
- **$M_2$ (após $T_2$):** `[0, 0, 1, 1, 0, 0]` — Habilitada: `['T3']` *(execução paralela em $P_3$ e $P_4$)*
- **$M_3$ (após $T_3$):** `[0, 0, 0, 0, 1, 0]` — Habilitada: `['T4']` *(sincronização concluída)*
- **$M_4$ (após $T_4$):** `[0, 0, 0, 0, 0, 1]` — Habilitada: `['T5']`
- **$M_5$ (após $T_5$):** `[1, 0, 0, 0, 0, 0]` — Habilitada: `['T1']` *(retorno cíclico à marcação inicial)*

#### Como executar o script Python

```bash
pip install numpy
python rede_petri.py
```

<details>
<summary><strong>📄 Ver código-fonte completo de <code>rede_petri.py</code></strong></summary>

```python
import numpy as np


def simular_rede_petri():
    # Definição dos rótulos dos Lugares (P1 a P6) e Transições (T1 a T5)
    lugares = [
        "P1 (Início)",
        "P2 (Pós_Braço)",
        "P3 (Escavar)",
        "P4 (Girar Torre)",
        "P5 (Despejar)",
        "P6 (FIM)",
    ]
    transicoes = ["T1", "T2", "T3", "T4", "T5"]

    # Matriz de Entrada (Pre): arcos de Lugares -> Transições (6x5)
    Pre = np.array([
        [1, 0, 0, 0, 0],  # P1
        [0, 1, 0, 0, 0],  # P2
        [0, 0, 1, 0, 0],  # P3
        [0, 0, 1, 0, 0],  # P4
        [0, 0, 0, 1, 0],  # P5
        [0, 0, 0, 0, 1],  # P6
    ])

    # Matriz de Saída (Post): arcos de Transições -> Lugares (6x5)
    Post = np.array([
        [0, 0, 0, 0, 1],  # P1
        [1, 0, 0, 0, 0],  # P2
        [0, 1, 0, 0, 0],  # P3
        [0, 1, 0, 0, 0],  # P4
        [0, 0, 1, 0, 0],  # P5
        [0, 0, 0, 1, 0],  # P6
    ])

    # Matriz de Incidência: C = Post - Pre
    C = Post - Pre

    print("=" * 60)
    print("MODELAGEM DE REDE DE PETRI - RETROESCAVADEIRA 4-DoF")
    print("=" * 60)
    print("\nMatriz de Entrada (Pre):\n", Pre)
    print("\nMatriz de Saída (Post):\n", Post)
    print("\nMatriz de Incidência (C = Post - Pre):\n", C)
    print("\n" + "=" * 60)
    print("SIMULAÇÃO DA EVOLUÇÃO DAS MARCAÇÕES (M0 a M5)")
    print("=" * 60)

    # Marcação Inicial M0: 1 ficha em P1 (Início)
    M = np.array([1, 0, 0, 0, 0, 0])

    def transicoes_habilitadas(marcacao):
        habilitadas = []
        for idx, t in enumerate(transicoes):
            # Uma transição está habilitada se M >= Pre[:, idx] para todos os lugares
            if np.all(marcacao >= Pre[:, idx]):
                habilitadas.append(t)
        return habilitadas

    # Exibe estado inicial M0
    print(f"\nM0 (Inicial): {M.tolist()} | Habilitada: {transicoes_habilitadas(M)}")

    # Sequência de disparos do ciclo completo: T1 -> T2 -> T3 -> T4 -> T5
    sequencia_disparos = ["T1", "T2", "T3", "T4", "T5"]

    for passo, t_nome in enumerate(sequencia_disparos, start=1):
        idx_t = transicoes.index(t_nome)

        # Vetor de disparo sigma_k (1 na posição da transição disparada, 0 nas demais)
        sigma = np.zeros(len(transicoes), dtype=int)
        sigma[idx_t] = 1

        # Verifica se o disparo é válido antes de executar
        if not np.all(M >= Pre[:, idx_t]):
            raise ValueError(f"Erro: Transição {t_nome} não está habilitada na marcação {M.tolist()}!")

        # Equação fundamental de estado: M_k = M_{k-1} + C * sigma_k
        M = M + C @ sigma

        # Identifica lugares ativos na marcação atual
        ativos = [lugares[i] for i, fichas in enumerate(M) if fichas > 0]

        print(
            f"M{passo} (após {t_nome}): {M.tolist()} "
            f"| Habilitada: {transicoes_habilitadas(M)} "
            f"| Ativo: {', '.join(ativos)}"
        )

    # Verificação de reversibilidade (retorno ao estado inicial M0)
    M0 = np.array([1, 0, 0, 0, 0, 0])
    if np.array_equal(M, M0):
        print("\n[OK] Propriedade verificada: Rede reversível e viva (retornou a M0).")


if __name__ == "__main__":
    simular_rede_petri()
```

</details>

---

### Etapa 2: Rede de Petri Colorida (CPN Tools)

Modelagem de alto nível com rastreamento de atuadores e temporização das operações.

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
   - Marcação: `1`("C1", INICIO, [NSA], 0, 0)`
2. **Posicionamento (`A: POS_BRACO`):**
   - Marcação: `("C1", POS_BRACO, [CIL_LANCA, CIL_BRACO], 3, 0)` *(duração: $3\text{ u.t.}$)*
3. **Execução Paralela (`B` e `C`):**
   - **B (`ESCAVAR`):** `("C1", ESCAVAR, [CIL_BRACO, CIL_CONCHA], 5, 3)` *(término em $t = 8\text{ u.t.}$)*
   - **C (`GIRAR_TORRE`):** `("C1", GIRAR_TORRE, [MOTOR_GIRO], 4, 3)` *(término em $t = 7\text{ u.t.}$)*
4. **Sincronização (`D` $\rightarrow$ `DESPEJAR`):**
   - Cálculo: `maxTime(3, 5, 3, 4) = 8`
   - Marcação: `("C1", DESPEJAR, [CIL_CONCHA], 2, 8)` *(duração: $2\text{ u.t.}$)*
5. **Encerramento (`Fim` $\rightarrow$ `FIM`):**
   - Marcação: `("C1", FIM, [NSA], 0, 10)` *(tempo total do ciclo: $10\text{ u.t.}$)*
