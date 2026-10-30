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

# PIM - Fase 2: Proposta do Projeto Mecatrônico (Retroescavadeira)

**Disciplina:** Informática Aplicada  
**Docente:** Prof. Robson Marinho  
**Colegiado:** Engenharia Civil - Departamento de Ciências Exatas e da Terra I (DCET I)  
**Instituição:** Universidade do Estado da Bahia (UNEB)  
**Equipe:** Juliana Almeida, Luan Pereira e Marcelo Custódio  
**Laboratório:** INOVAMECH  

---

## 📋 Visão Geral da Fase 2

Este repositório contém a documentação técnica da **Fase 2 do Projeto de Prototipagem para Inovação Mecatrônica (PIM - AV2_P1)**.

O projeto consiste na concepção e no detalhamento de uma **Retroescavadeira Mecatrônica Articulada de 4 Graus de Liberdade (4-DoF)**, voltada à automação, à precisão geométrica e à redução de riscos operacionais na Engenharia Civil. Todas as peças estruturais serão novas, projetadas e impressas em 3D no INOVAMECH.

**Ciclo de operação:** recebe a ordem de coleta, coleta o material, leva ao local de descarga, deposita e aguarda a próxima ordem.

---

## 📑 Estrutura da Documentação

| Arquivo | Tópico | Descrição do conteúdo |
| :--- | :--- | :--- |
| 📄 `topico_2_proposta.pdf` | **2. Proposta do Projeto** | Problema na Engenharia Civil, objetivos, solução mecânica (PLA, tirantes de aço inox Ø1,5 mm, juntas, giro da torre e caçamba em V), modelagem preliminar no Fusion 360 e funcionalidades esperadas. |
| 📄 `topico_3_arquitetura.pdf` | **3. Arquitetura Mecatrônica** | Componentes e materiais (Arduino Nano, servos MG995/SG90, sensor HC-SR04, eixos M3 e buchas de latão), diagrama de blocos e integração entre mecânica, eletrônica, controle e segurança. |
| 🔷 `Rede_Petri_Retroescavadeira.hps` e `rede_petri_retroescavadeira.jpeg` | **4. Modelagem inicial** | Rede de Petri do ciclo da retroescavadeira (arquivo HPSim e imagem). O diagrama funcional está no tópico 3. |
| 📄 `topico_5_viabilidade.pdf` | **5. Viabilidade do Projeto** | Justificativa dos materiais (PLA, aço inox M3, servos MG995/SG90, Arduino), recursos disponíveis no INOVAMECH, tempo estimado de impressão 3D (18 a 22 horas), ciclo PIM de execução e ações preventivas (capacitores de 470 µF e lubrificação com PTFE). |

---

## 🛠️ Tecnologias e Ferramentas Utilizadas

* **CAD / Prototipagem:** Autodesk Fusion 360
* **Manufatura Aditiva:** Impressão 3D FDM (PLA)
* **Controle e Processamento:** Arduino Nano (C/C++, `Servo.h`)
* **Atuadores e Sensores:** Servomotores MG995 e SG90, sensor ultrassônico HC-SR04
* **Modelagem:** HPSim (Redes de Petri)
