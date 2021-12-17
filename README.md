
# icproject2

#### Estrutura do Projecto:


          
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

##### Parte A [^2] [^3] [^4] [^5] [^6]

- [ ] Ex1_A - Implementa uma classe BitStream para ler bits de um ficheiro e/ou escrever bits para um ficheiro.

Na leitura do ficheiro binário utilizamos o metodo *file.read (memblock, size)* do ifstream [^1]:.

    Programa: BitStream.cpp/.h

- [ ] Ex2_A - Implementa um programa simples para testar a classe BitStream.

- [ ] Ex3_A - Implementa um codificador entrópico ("lossless") usando códigos de Golomb.

    Programa: Golomb.cpp/.h

- [ ] Ex4_A - Implementa um programa simples para testar a classe Golomb.

##### Parte B

- [ ] Ex1_B - Desenvolve um codec de audio preditivo, explorando as redundâncias de canal e de frequência, usando códigos de Golomb.

- [ ] Ex2_B - Inclui uma opção no codificador para calcular o histográma obtido depios da predição e o valor da entropia.

- [ ] Ex3_B - Inclui uma opção para codificador "lossy", baseado em quantificação residual.

##### Parte C

- [ ] Ex1_C - Desenvolve um codificador "lossless" baseado nos preditores lineares JPEG-LS ou 7 JPEG.

- [ ] EX2_C - Extender o codificador "lossless" do Ex1_C, de forma a permitir codificação "lossy".

##### Parte D

- [ ] Relatório

//-------------------------------------------------------------------------------------------------------//

REFERÊNCIAS:


[^1]: Quantidade de informação, quantificação e codificação: http://intranet.deei.fct.ualg.pt/FTel/html/node7_ct.html

[^2]: Sistema Multimédia - Amostragem de Imagens (slides): http://sweet.ua.pt/jnvieira/sm/docs/Aulas/Modulo3-Amostragem%20Imagem.pdf

[^3]: Sistemas Multimédia - Codificação  (slides): http://sweet.ua.pt/jnvieira/sm/docs/Aulas/Modulo5-Codifica%C3%A7%C3%A3o.pdf

[^4]: LOSSLESS AUDIO DATA COMPRESSION, by Kan Zhao, 2007: https://scholar.acadiau.ca/islandora/object/theses:126/datastream/PDF/file.pdf

[^5]: Bit Manipulation: http://www.goldsborough.me/bits/c++/low-level/problems/2015/10/11/23-52-02-bit_manipulation/

[^6]: Bit Operations:

          http://www2.lawrence.edu/fast/GREGGJ/CMSC270/bitOperations.html
          https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
          

[^7]: File Streams em C++ com ficheiros binários:

          https://www.cplusplus.com/doc/tutorial/files/   (ir à seção "Binary files")
          https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
          https://courses.cs.vt.edu/cs2604/fall02/binio.html


