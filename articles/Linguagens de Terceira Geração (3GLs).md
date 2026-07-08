
**Instituto Superior de Educação do Rio de Janeiro**

**Kathelley Vieira Rodrigues - 14**  
**Renato Lóis Marcondes da Silva - 22**

## I. Introdução e Contexto Histórico das 3GLs

### Definição da 3a Geração, salto de produtividade, paradigma vs. geração

As linguagens de 3ª geração foram projetadas de forma a serem facilmente compreendidas por seres humanos. Sua forma de desenvolvimento em relação à modos mais antigos tais quais linguagem de máquina, ou assembly, se diferencia num nível de produtividade bem maior devido sua forma de produção mais legível e prática.

Os primeiros computadores de grande porte tinham poucos recursos. Por exemplo, 128 KB de memória era o auge da época, nos melhores do início da década de 60: IBM 7090 ou um IBM 7094. Em sua maioria, utilizavam linguagem de montagem para operar essas máquinas, devido à necessidade crítica de economia de memória e poder computacional.

Com o passar do tempo e o avanço do desenvolvimento tecnológico. Linguagens de mais alto nível como COBOL e Fortran se destacaram e passaram a ser muito utilizadas, tomando lugar do assembly. Todavia quando foi lançado o PDP-1 (primeiro computador comercial), que usa um tamanho de palavra de 18 bits e possui 4096 palavras como memória principal padrão (equivalente em tamanho de bit a 9216 bytes de oito bits , mas em tamanho de caractere a 12388 bytes, já que o sistema divide uma palavra de 18 bits em três caracteres de seis bits), o retorno da linguagem de montagem veio a tona. Entretanto, à medida que a aquisição de maior poder computacional era conquistada, processadores e memórias ficaram mais potentes, as linguagens de alto nível se tornaram mais predominantes.

A linguagem de montagem ainda pode ser utilizada principalmente em serviços embarcados, porém os computadores pessoais de hoje são programados em C, CPlusPlus, Java e outros por causa da grande quantidade de memória disponível e a enorme capacidade de processamento.

A motivação dessa mudança se dá pelo aumento de produtividade, legibilidade e praticidade de produção. Os paradigmas imperativos das primeiras linguagens da terceira geração se sobressaíam do assembly pela legibilidade, estruturas condicionais e loops se faziam ótimas novidades na vida do programador da máquina. Em seguida, linguagens tais como Lisp e C foram bastante utilizadas devido seus paradigmas funcionais. A estruturalização do código em funções prometia uma segurança lógica maior em relação aos antigos GO TO. Enquanto as mais novas linguagens como CPlusPlus, Java e Python se diferenciam devido ao uso de programação orientada a objetos. Conceitos como encapsulamento, herança e outros garantem uma maior reusabilidade e prevenção de erros.

Essas novidades se originaram principalmente pela necessidade de alternativa aos famigerados erros de ponteiros, memory leaks e outros pontos importantes que afetam diretamente o cotidiano do profissional da área. Soluções como garbage collector (em java e python) e ownership (rust) são exemplos de inovações modernas em relação a esses problemas. E continua encaminhando na direção de abstrair mais ainda conceitos básicos, otimizando o tempo de desenvolvimento e produção, enquanto o poder computacional tende a aumentar.

## II. Análise Detalhada das 3GLs Mais Famosas

### ➔ C (O Alicerce)

#### Surgimento e Criador

A linguagem C surgiu no início da década de 1970, sendo desenvolvida por Dennis Ritchie, nos Estados Unidos. Ela foi criada a partir da necessidade de uma linguagem mais eficiente e portátil para o desenvolvimento do sistema operacional UNIX, que até então era escrito em Assembly. O primeiro compilador de C foi implementado em 1972, e a linguagem rapidamente se consolidou como uma das mais importantes da história da computação.

#### Eficácia e Onde é Usada

C é amplamente utilizada em:

- **Sistemas Operacionais**: o kernel do Unix (e, posteriormente, o Linux) foi escrito em C, bem como partes significativas do Windows e do macOS.
- **Sistemas Embarcados**: utilizada em microcontroladores, firmwares e dispositivos eletrônicos devido ao seu controle direto sobre o hardware.
- **Drivers e Compiladores**: por ser próxima da máquina, é ideal para a criação de drivers de dispositivos e compiladores de outras linguagens.

Além disso, muitas linguagens modernas, como C++, C#, Java, Objective-C e até Python (cujo interpretador é escrito em C), foram influenciadas ou construídas sobre suas bases, consolidando C como o verdadeiro alicerce da programação moderna.

#### Característica Chave

A principal característica da linguagem C é estar muito próxima do hardware, permitindo manipulação direta de memória, ponteiros e recursos do sistema. Isso garante altíssimo desempenho, mas também exige do programador um controle rigoroso, já que erros como vazamentos de memória ou acessos indevidos podem ocorrer com facilidade. Apesar de ser estrutural (ou seja, baseada em funções e blocos de código), C não é orientada a objetos, o que a torna menos adequada para projetos que exigem encapsulamento e reutilização extensiva de código.

### ➔ C++ (A Extensão Orientada a Objetos)

#### Surgimento e Criador

A linguagem C++ surgiu no início da década de 1980, desenvolvida por Bjarne Stroustrup. Stroustrup buscava unir a eficiência e o controle do C com novos conceitos de abstração e modularidade, inspirados em linguagens como Simula (considerada a primeira linguagem orientada a objetos). A primeira versão oficial, chamada “C with Classes”, surgiu em 1983, evoluindo até adotar o nome C++ — o “++” representa o operador de incremento em C, simbolizando a ideia de uma melhoria ou evolução da linguagem original.

#### Eficácia e Onde é Usada

O C++ é amplamente reconhecido por sua combinação de desempenho e flexibilidade. Ele mantém a velocidade e o acesso direto ao hardware do C, mas adiciona recursos avançados de programação orientada a objetos (POO), abstração de dados e programação genérica (com templates).

Por isso, é amplamente utilizado em áreas que exigem alto desempenho e controle de recursos, como:

- **Desenvolvimento de Jogos**: motores gráficos e físicos, como Unreal Engine, são baseados em C++ pela necessidade de desempenho em tempo real.
- **Sistemas Financeiros e de Trading**: onde a velocidade de execução e a baixa latência são cruciais para processar grandes volumes de dados em frações de segundo.
- **Sistemas Operacionais, Navegadores e Softwares Complexos**: componentes do Windows, do macOS, do Chrome e de programas como Photoshop são desenvolvidos parcialmente em C++.

Além disso, o C++ é muito valorizado na indústria de ciência da computação, robótica e simulações de alta performance, sendo uma linguagem essencial para aplicações que precisam equilibrar eficiência e complexidade estrutural.

#### Característica Chave

A principal característica do C++ é ser uma extensão do C que incorpora o paradigma de Programação Orientada a Objetos (POO). Isso permite trabalhar com classes, herança, polimorfismo e encapsulamento, facilitando a criação de sistemas grandes e modulares.

### ➔ Java (A Plataforma Portável)

#### Surgimento e Criador

A linguagem Java surgiu em meados da década de 1990, desenvolvida por James Gosling e sua equipe na empresa Sun Microsystems. O projeto teve início em 1991 sob o nome “Green Project”, com o objetivo inicial de criar uma linguagem para dispositivos eletrônicos inteligentes e televisões interativas. Entretanto, com o crescimento da internet, o Java foi adaptado para o desenvolvimento multiplataforma, tornando-se oficialmente lançado em 1995. Desde então, destacou-se como uma das linguagens mais utilizadas no mundo, especialmente em ambientes corporativos e acadêmicos.

#### Eficácia e Onde é Usada

A grande força do Java é sua portabilidade — o código compilado em Java é convertido em bytecode, executado pela Java Virtual Machine (JVM), o que permite que um mesmo programa rode em qualquer sistema operacional que tenha a JVM instalada. Essa filosofia é resumida no famoso lema: *“Write Once, Run Anywhere”* (Escreva uma vez, execute em qualquer lugar).

O Java é amplamente utilizado em:

- **Sistemas Corporativos e Backend**: frameworks como Spring e Jakarta EE (antigo Java EE) são bases para grandes sistemas empresariais, bancos e serviços online.
- **Aplicações Android**: até hoje, o Android SDK utiliza o Java (ou linguagens compatíveis com a JVM, como Kotlin) para o desenvolvimento de aplicativos móveis.
- **Grandes Sistemas Distribuídos**: tecnologias de Big Data (como Hadoop e Spark) e sistemas multiplataforma de alta escalabilidade são frequentemente desenvolvidos em Java.

#### Característica Chave

A principal característica do Java é a portabilidade proporcionada pela Máquina Virtual Java (JVM), que atua como uma camada intermediária entre o código e o hardware. Assim, o mesmo programa pode ser executado em diferentes sistemas operacionais sem modificações. Além disso, o Java é uma linguagem de tipagem forte e estática, o que significa que os tipos de dados são verificados durante a compilação, reduzindo erros de execução. Também conta com coleta automática de lixo (garbage collection), eliminando a necessidade de gerenciamento manual de memória — um avanço importante em relação ao C e ao C++. Sua robustez, segurança e independência de plataforma fazem do Java uma das linguagens mais confiáveis e duradouras na área da engenharia de software.

### ➔ Python (A Produtividade e Legibilidade)

#### Surgimento e Criador

A linguagem Python surgiu no início da década de 1990, criada por Guido van Rossum nos Países Baixos (Holanda). O desenvolvimento começou em 1989, durante o período em que van Rossum trabalhava no CWI (Centrum Wiskunde & Informatica), e a primeira versão pública foi lançada em 1991. O objetivo principal de Guido era criar uma linguagem fácil de aprender e usar, que mantivesse o poder das linguagens mais complexas, mas com uma sintaxe simples e clara, próxima da linguagem humana. O nome “Python” foi inspirado no grupo humorístico britânico Monty Python, refletindo o espírito leve e acessível da linguagem.

#### Eficácia e Onde é Usada

O Python é conhecido por sua versatilidade e produtividade, sendo uma das linguagens mais utilizadas no mundo moderno da computação. Sua sintaxe simples e suas bibliotecas poderosas o tornaram uma ferramenta essencial em diversas áreas:

- **Ciência de Dados e Análise Estatística**: com bibliotecas como NumPy, Pandas e Matplotlib, o Python é amplamente usado para processamento e visualização de dados.
- **Inteligência Artificial e Machine Learning**: frameworks como TensorFlow, Keras e PyTorch tornaram o Python a principal linguagem para o desenvolvimento de modelos de aprendizado de máquina e redes neurais.
- **Automação e Scripting**: muito utilizado para automatizar tarefas, manipular arquivos, gerenciar sistemas e integrar diferentes aplicações.
- **Desenvolvimento Web**: frameworks como Django e Flask permitem criar aplicações web de forma rápida, organizada e eficiente.

#### Característica Chave

As principais características do Python são a legibilidade e a simplicidade do código. Sua sintaxe é limpa e concisa, permitindo que programas complexos sejam escritos com poucas linhas, facilitando tanto o aprendizado quanto a manutenção de projetos. O Python utiliza tipagem dinâmica, o que significa que o tipo das variáveis é determinado em tempo de execução, proporcionando grande flexibilidade ao programador. Além disso, conta com uma vasta biblioteca padrão, que oferece módulos prontos para diversas tarefas — desde manipulação de arquivos até desenvolvimento de redes e interfaces gráficas.

## III. Comparação e Principais Diferenças (O Confronto)

### Quadro Comparativo de Diferenças

| Característica               | C                                                                           | C++                                                                                                           | Java                                                                       | Python                                                                                                                   |
| ---------------------------- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| **Ano de criação**           | 1972                                                                        | 1983                                                                                                          | 1995                                                                       | 1991                                                                                                                     |
| **Criador(es)**              | Dennis Ritchie                                                              | Bjarne Stroustrup                                                                                             | James Gosling                                                              | Guido van Rossum                                                                                                         |
| **Paradigma**                | Programação imperativa<br>Programação funcional                             | Programação imperativa<br>Programação funcional<br>Programação orientada a objetos<br>Programação genérica    | Programação orientada a objetos<br>Programação genérica                    | Programação imperativa<br>Programação funcional<br>Programação orientada a objetos (limitada)<br>Programação declarativa |
| **Controle de memória**      | Manual (ponteiros)                                                          | Manual (ponteiros)<br>Desalocação automática (*smart pointers*)                                               | Garbage Collector (baixo controle sobre a memória)                         | Garbage Collector (gerenciamento automático e simplificado)                                                              |
| **Modo de execução**         | Compilada                                                                   | Compilada                                                                                                     | Bytecode executado pela JVM (interpretação/JIT)                            | Bytecode interpretado (implementações como PyPy permitem JIT)                                                            |
| **Velocidade**               | Muito rápida                                                                | Muito rápida, ligeiramente inferior ao C puro                                                                 | Boa, especialmente com otimizações da JVM                                  | Inferior ao Java, priorizando produtividade                                                                              |
| **Tipagem**                  | Estática e fraca                                                            | Estática e fraca                                                                                              | Estática e forte                                                           | Dinâmica e forte                                                                                                         |
| **Gerenciamento de memória** | Manual                                                                      | Manual com opções automáticas                                                                                 | Automático (Garbage Collector)                                             | Automático (Garbage Collector)                                                                                           |
| **Portabilidade**            | Baixa (depende do compilador e sistema)                                     | Baixa (depende do compilador e sistema)                                                                       | Alta (JVM)                                                                 | Alta (interpretador)                                                                                                     |
| **Curva de aprendizado**     | Difícil                                                                     | Difícil                                                                                                       | Moderada                                                                   | Fácil                                                                                                                    |
| **Foco principal**           | Desenvolvimento de sistemas, sistemas embarcados, sistemas críticos e jogos | Desenvolvimento de sistemas, sistemas embarcados, jogos, robótica, simulações e computação de alto desempenho | Sistemas corporativos, backend, aplicações Android e sistemas distribuídos | Ciência de dados, inteligência artificial, automação, scripts e desenvolvimento web                                      |

---

### ➔ O Legado das 3GLs

As linguagens mais antigas como COBOL e Fortran seguem sendo utilizadas em poucos casos em que a preservação de um sistema legado se mantém necessário. Outras como C ainda são importantes para IOT e sistemas embarcados, necessários para desempenho crítico. Programas de baixo nível como drivers, kernel's, sistemas de boot, e API's Backends gráficas de monitores por exemplo necessitam de linguagens de baixo nível mais próximo de hardware necessitam de linguagens como assembly, c, zig (moderna) e outras.

### ➔ O Futuro

As linguagens mais modernas como Go, Rust e outras buscam trazer conceitos modernos como o aumento na produtividade e trazendo de volta o poder do baixo nível. Por exemplo Go trás o desempenho de linguagens de baixo nível em conjunto com tecnologias modernos como alto poder de controle em redes e multiprocessamento, juntamente com uma maior segurança de memória.

---

fontes: Wikipédia - site, Sistemas Operacionais Modernos 4° edição (Tanenbaum) - livro