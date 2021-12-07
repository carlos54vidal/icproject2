# icproject2

Estrutura do Projecto:

Raiz (executáveis, ficheiros de dados, relatório final e "readme")

                     |
                     |
                     |_______ Sources (ficheiros de código)
                     
                     |           |
                     |           |
                     |           |_______ Dependencies (librarias "externas")
                     
                     |
                     |
                     |_______ Documentação (Doxygen, referêencias bibliográficas, etc)


TRABALHO

Parte A

Ex1_A - Implementa uma classe BitStream para ler bits de um ficheiro e/ou escrever bits para um ficheiro.
  Programa: BitStream.cpp/.h

Ex2_A - Implementa um programa simples para testar a classe BitStream.

Ex3_A - Implementa um codificador entrópico ("lossless") usando códigos de Golomb.
  Programa: Golomb.cpp/.h

Ex4_A - Implementa um programa simples para testar a classe Golomb.

Parte B

Ex1_B - Desenvolve um codec de audio preditivo, explorando as redundâncias de canal e de freqência, usando códigos de Golomb.

Ex2_B - Inclui uma opção no codificador para calcular o histográma obtido depios da predição e o valor da entropia.

Ex3_B - Inclui uma opção para codificador "lossy", baseado em quantificação residual.

Parte C

Ex1_C - Desenvolve um codificador "lossless" baseado nos preditores lineares JPEG-LS ou 7 JPEG.

EX2_C - Extender o codificador "lossless" do Ex1_C, de forma a permitir codificação "lossy".

Parte D

Relatório

//-------------------------------------------------------------------------------------------------------//

REFERÊNCIAS:

Quantidade de informação, quantificação e codificação: http://intranet.deei.fct.ualg.pt/FTel/html/node7_ct.html

Sistema Multimédia - Amostragem de Imagens (slides): http://sweet.ua.pt/jnvieira/sm/docs/Aulas/Modulo3-Amostragem%20Imagem.pdf

Sistemas Multimédia - Codificação  (slides): http://sweet.ua.pt/jnvieira/sm/docs/Aulas/Modulo5-Codifica%C3%A7%C3%A3o.pdf

Bit Manipulation: http://www.goldsborough.me/bits/c++/low-level/problems/2015/10/11/23-52-02-bit_manipulation/

Bit Operations: http://www2.lawrence.edu/fast/GREGGJ/CMSC270/bitOperations.html
                https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
