# PIM Mecatrônica - Grupo 2

Projeto Integrado Multidisciplinar com o robô bípede Otto DIY.
Disciplina: Informática Aplicada | Prof. Dr. Robson Marinho da Silva | UNEB, Engenharia Civil

## Integrantes
- Juliana Almeida
- Luan Pereira
- Marcelo Custódio

## Fase 1: Montagem, programação e modelagem do Otto

Montagem do robô Otto DIY com Arduino Nano, shield de expansão, 4 servomotores SG90, sensor ultrassônico HC-SR04 e buzzer, com estrutura impressa em 3D.

### Estrutura
- `fase-1/relatorios/`: relatórios técnicos AV1_P1 a AV1_P4 (montagem, ligações, calibração e testes, modelagem da dança)
- `fase-1/codigo/`: código `OttoS_BLE.ino` gravado no robô (Arduino Nano), com controle por Bluetooth e três funções novas: valsa (Rede de Petri), corrida de obstáculos e inspetor com sensor ultrassônico (estados, alerta sonoro e botão virtual por proximidade)
- `fase-1/danca/`: Rede de Petri da "Valsa do Otto" (arquivo HPSim)
- `fase-1/aplicacao-na-engenharia/`: Rede de Petri do Sistema de Vigilância Otto (mapeamento, vigilância e alerta)

### Vídeos dos testes
- Vídeo 1: https://drive.google.com/file/d/1ZWeRxMEs-itds_s8hMKcQkS-vprJxjhR/view
- Vídeo 2: https://drive.google.com/file/d/1HO5cToMnC6fx4-v974Nx6B1jUZ8hcoKo/view


# PIM — Fase 2: Proposta do Projeto Mecatrônico (Retroescavadeira)

**Disciplina:** Informática Aplicada  
**Docente:** Prof. Robson Marinho  
**Colegiado:** Engenharia Civil — Departamento de Ciências Exatas e da Terra I (DCET I)  
**Instituição:** Universidade do Estado da Bahia (UNEB)  
**Equipe:** Juliana Almeida, Luan Pereira e Marcelo Custódio  
**Laboratório:** INOVAMECH  

---

## 📋 Visão Geral da Fase 2

Este repositório contém a documentação técnica referente à **Fase 2 do Projeto de Prototipagem para Inovação Mecatrônica (PIM — AV2_P1)**. 

O projeto consiste na concepção e detalhamento de uma **Retroescavadeira Mecatrônica Articulada de 4 Graus de Liberdade (4-DoF)**, desenvolvida para automação, precisão geométrica e redução de riscos operacionais na Engenharia Civil.

---

## 📑 Estrutura da Documentação (Arquivos PDF)

A entrega da proposta foi dividida e organizada em três documentos técnicos individuais conforme as diretrizes da disciplina:

| Arquivo PDF | Tópico | Descrição do Conteúdo |
| :--- | :--- | :--- |
| 📄 `topico_2_proposta.pdf` | **2. Proposta do Projeto** | Descrição do problema na Engenharia Civil, objetivos, solução mecânica detalhada (PLA, tirantes Ø1.5mm, juntas e geometria da caçamba em V), pré-visualização CAD Fusion 360 e funcionalidades esperadas. |
| 📄 `topico_3_arquitetura.pdf` | **3. Arquitetura Mecatrônica** | Especificação dos componentes (Arduino Nano, servos SG90/MG995, sensor HC-SR04), diagrama de blocos do sistema e detalhamento da integração entre mecânica, eletrônica, controle e segurança. |
| 📄 `topico_5_viabilidade.pdf` | **5. Viabilidade do Projeto** | Justificativa técnica dos materiais, análise de esforço x limite elástico do PLA, tempo de manufatura aditiva (15–20h) e cronograma de execução no laboratório INOVAMECH. |


---

## 🛠️ Tecnologias e Ferramentas Utilizadas

* **CAD / Prototipagem:** Autodesk Fusion 360
* **Manufatura Aditiva:** Impressão 3D (Termoplástico PLA)
* **Controle e Processamento:** Arduino (C/C++ / `Servo.h`)
* **Atuadores e Sensores:** Servomotores SG90/MG995 e Sensor Ultrassônico HC-SR04
