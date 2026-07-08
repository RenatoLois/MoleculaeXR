# Construindo uma esfera a partir de polígonos

Recentemente estive desenvolvendo uma engine para um projeto experimental de realidade aumentada. A princípio usaria apenas figuras básicas para desenhar objetos na tela. Já tendo criado uma classe para cubos, eu necessitava desenhar esferas também, além de outras formas geométricas.

Pesquisando um pouco no LearnOpenGL e em outras fontes, é fácil encontrar snippets com a criação de vetores contendo os vértices. Porém, qual seria o sentido de criar uma engine apenas copiando e colando a matemática pronta? Se o objetivo é entender o que acontece por baixo dos panos, é necessário compreender a construção desses modelos.

Escrevo este artigo para documentar a lógica por trás da solução que encontrei. Se alguns trechos parecerem complexos demais à primeira vista, não se preocupe: o texto demonstra apenas a versão final refinada, ignorando os milhares de caminhos incorretos que testei antes de chegar até aqui.

---

## Aproximação de uma esfera

Primeiro pesquisei como uma pseudo-esfera é construída. Encontrei algo parecido com a seguinte imagem:

![imagem do jogo](<Pasted image 20260619173532.png>)

Essa é uma das formas de aproximar uma esfera partindo de outras figuras geométricas. Esse modelo é conhecido como **UV Sphere**.

Existem outros modelos interessantes que valem a pena serem pesquisados, como a **Ico Sphere**, que é construída a partir de um icosaedro.

A ideia da UV Sphere é dividir o polígono por várias linhas horizontais, criando uma aproximação cada vez melhor de uma esfera.

Para facilitar o entendimento, vamos analisar primeiro em 2D.

---

## Construção em 2D

Inicialmente, consideramos que os dois vértices fixos representam os polos norte e sul do círculo de centro `A`. Esses pontos serão `D` e `B`, respectivamente. Pense nisso como uma esfera vista no plano `XY`.

![círculo inicial](<Pasted image 20260619180346.png>)

Em seguida, completamos um hexágono inscrito:

![hexágono](<Pasted image 20260619182405.png>)

Agora temos pontos suficientes para definir duas retas paralelas:

![retas paralelas](<Pasted image 20260619182515.png>)

A partir disso podemos adicionar mais linhas paralelas, dividindo as áreas de forma que os segmentos que conectam os novos pontos de interseção aos pontos adjacentes previamente definidos na circunferência possuam o mesmo módulo.

![divisão](<Pasted image 20260619183306.png>)

Depois recalculamos os vértices:

![vértices recalculados](<Pasted image 20260619182702.png>)

---

# O que precisamos encontrar?

É necessário encontrar uma forma de descobrir as coordenadas X e Y de cada vértice do polígono obtido. Posteriormente cuidaremos da coordenada Z para torná-lo possível de manipular em 3D, transformando isso de fato em uma esfera.

# Analisando os níveis

Podemos definir a construção por níveis:

- **Nível 1:** hexágono (com duas linhas cortando)
- **Nível 2:** dodecágono (com cinco linhas cortando)
- **Níveis seguintes:** continuam dobrando a quantidade de divisões

A quantidade de lados segue a expressão:

$$
lados(n)=2\cdot lados(n-1)+1
$$

onde `n` representa o nível.

---
## Brincando com as propriedades

Nosso principal objetivo aqui é obter os vértices da esfera. Como eu disse anteriormente, estou construindo uma engine e abstraí o conceito de vértice em uma classe. Ela contém um vetor para as coordenadas de posição (X, Y, Z), um vetor para as componentes do vetor normal (X, Y, Z) e um último vetor para as coordenadas de textura (U, V), estruturada da seguinte maneira:

```cpp
Vertex::Vertex(
  glm::vec3 position,
  glm::vec3 normal,
  glm::vec2 tex
)
```

Mais à frente, precisaremos extrair o ângulo dos triângulos internos ou **ângulo central**, se você quiser parecer mais formal, para podermos trabalhar com trigonometria.

Mas, para chegar lá, precisamos primeiro resolver um problema: até agora, só temos a quantidade de lados com base no nível anterior.

Vamos tentar nos entreter com a aritmética até encontrar uma forma de saber a quantidade de lados de um nível de maneira direta, sem termos que recorrer à recursão. 

Adicionando 1 em ambos os lados da fórmula que tinhamos:
$$
lados(n)+1=2\cdot lados(n-1)+2
$$
Agrupando:
$$
lados(n)+1=2(lados(n-1)+1)
$$
Agora definimos:
$$
m(k)=lados(k)+1
$$
Logo:
$$
m(k-1)=lados(k-1)+1
$$

Substituindo:
$$
m(k)=2m(k-1)
$$
---

## Calculando os primeiros valores

Sabemos que:
$$
lados(1)=2
$$
Então:
$$
m(1)=lados(1)+1
$$
$$
m(1)=2+1=3
$$

Para o nível 2:

$$
lados(2)=5
$$

então:

$$
m(2)=lados(2)+1=6
$$

E pela recorrência:

$$
m(2)=2m(1)
$$

$$
m(2)=2\cdot3=6
$$


Para o nível 3:

$$
lados(3)=11
$$

logo:
$$
m(3)=12
$$
e:
$$
m(3)=2m(2)
$$
$$
m(3)=2\cdot2m(1)
$$
$$
m(3)=12
$$
Para o nível 4:
$$
lados(4)=23
$$
portanto:
$$
m(4)=24
$$
e:

$$
m(4)=2m(3)
$$
$$
m(4)=2\cdot2m(2)
$$
$$
m(4)=2\cdot2\cdot2m(1)
$$
$$
m(4)=24
$$

---

## Encontrando a fórmula geral

Percebemos o padrão:
$$
m(1)=3
$$
$$
m(2)=3\cdot2
$$
$$
m(3)=3\cdot2^2
$$
$$
m(4)=3\cdot2^3
$$
Portanto:
$$
m(n)=3\cdot2^{n-1}
$$
E como:
$$
m(n)=lados(n)+1
$$
temos:
$$
lados(n)+1=3\cdot2^{n-1}
$$
Finalmente:
$$
\boxed{lados(n)=3\cdot2^{n-1}-1}
$$
Com isso, podemos enfim descobrir o ângulo da abertura dos triângulos internos do polígono:
$$
\boxed{α_n=\frac{360}{lados(n)}}
$$

em radianos:
$$
\boxed{α_n=\frac{2\pi}{lados(n)}}
$$


Precisamos, em seguida, obter as coordenadas de cada ponto. Podemos usar o seno, conforme a imagem a seguir, focando no ponto E:

![coordenadas](<Pasted image 20260701112551.png>)

![zoom](<Pasted image 20260701113532.png>)

Note que o cateto oposto ao ângulo alpha, equivalente à coordenada Y do vértice E, é obtido por:
$$
Y = \sin(\alpha) \cdot \text{raio}
$$
E também o cateto adjacente ao ângulo alpha, equivalente à coordenada X do vértice E, é obtido por:

$$
X = \cos(\alpha) \cdot \text{raio}
$$


Primeiro, definimos um ponto de partida para o ângulo 0. Arbitrariamente escolhi o leste. A partir de agora, chamarei de equador a linha que corta o círculo no meio, paralela ao eixo X.

![leste](<Pasted image 20260701115138.png>)

Porém, há um notável problema aqui. Se quiséssemos definir a altura do ponto D, teríamos de calcular o seno de um ângulo que não se situa entre as retas definidas pelo centro do círculo e seus vértices. Isso ocorre apenas no primeiro nível, onde há um hexágono. De forma mais simples, note que o primeiro vértice se encontra na metade do ângulo total do início.

Nos níveis seguintes, o eixo X passará a intersectar dois outros vértices, de forma que esse ângulo sempre fique entre duas retas definidas por um vértice e o centro. De forma mais simples, nos níveis seguintes, o primeiro vértice sempre poderia ser o que se encontra na linha do equador, ou seja, com ângulo 0.

Convenhamos que, embora seja simples usar apenas seno e cosseno para os níveis posteriores, para o primeiro caso (o hexágono) isso não é viável, e como não queremos fazer gambiarras, não vamos criar um caso separado.

Um passo possível para o problema seria criar, de forma genérica, uma função que não assuma que o início é 0. Podemos então definir um ângulo de deslocamento G que, caso precise, seja configurado; caso contrário, seja zero.

$$
Y = \sin(\alpha + G) \cdot \text{raio}
$$
$$
X = \cos(\alpha + G) \cdot \text{raio}
$$

Pronto, encontramos uma solução.
- Para nível = 1; G = 30°
- Para nível > 1; G = 0°

É funcional. Mas cadê o principal? Cadê a elegância? Não aceito uma condicional, vamos melhorar isso. 

De que forma podemos iniciar de um mesmo ponto de partida? Que ponto é sempre fixo? Você pode afirmar que o norte e o sul são pontos fixos, e sim, está certo. Vamos usar o ponto norte, por preferência, não por regra.

![ângulo de deslocamento constante](<Pasted image 20260701120954.png>)

Temos então um ponto de partida B, presente em qualquer nível da futura esfera, que nos permite definir um ângulo de deslocamento constante de 90 graus para qualquer nível, ou em radianos:
$$
G = \pi / 2
$$
