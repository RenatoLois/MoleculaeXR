
Este artigo tem o objetivo de documentar a experiência que tive ao criar uma própria engine para um projeto de realidade aumentada com opengl do zero. O motivo? Aprender computação gráfica de verdade, na prática. Embora eu tenha um pequeno contato anteriormente, foi uma nova experiência completamente.

Um dos fatores que me levaram a essa decisão foi perceber a magnitude do que foi feito em jogos antigos. Pegue Shadow of the Colossus: imagine programar qualquer uma daquelas batalhas em assembly, para um processador bem mais obscuro do que seu x86 ou ARM (arquitetura que muitos nem se atrevem a chegar perto por medo de se aventurar no baixo nível). Dificilmente eu faria esse cenário com um ser gigante usando otimização de ponta, renderização em tempo real, ainda mais em código de máquina para uma arquitetura bizarra.

A seguir, documentarei a lógica para estruturar o meu projeto, que para mim foi a parte mais complicado, até mais do que implementar no código.

O código fonte contendo a implementação pode ser encontrado em: https://github.com/RenatoLois/MoleculaeXR


![imagem do jogo](<Pasted image 20260619173836.png>)

Me senti até mesmo pequeno por saber tão pouco (o que me ajudou a ver o quanto ainda tenho para aprender). Visto que esta é minha área de estudo atual, me pus no lugar de entender como isso funciona. Claro que ainda é muito mais fácil que escrever em assembly, mas na real o meio de escrita como um código de máquina ou então uma linguagem de alto nível como C (sim, C é de alto nível) não é o mais importante, e sim a lógica por trás, o fundamento, aí mora o conhecimento que passaram tanto tempo para construir.

![descrição](<Pasted image 20260519210732.png>)
## A jornada de aprendizado
Nos últimos anos eu tenho usado em especial C e C++, as quais eu mais usei para aprender sobre OpenGL e computação gráfica. Pesquisando um pouco encontrei o ótimo site [LearnOpenGL](https://learnopengl.com), onde aprendi a desenhar pela primeira vez um triângulo. Até aqui eu ja havia testado anteriormente. Depois de muito tempo lendo e relendo, percebi que só entendi depois que fui copiando e executando na prática.

Vi alguns tutoriais, alguns trechos de outros lugares, e fui me inspirando e criando meu código. Comecei em C, minha função que compilava os shaders já funcionava, queria continuar simplificando o código, não queria ficar configurando VBO manualmente a cada novo objeto. De início, o maior o problema foi encontrar uma estrutura, como raios se fazem um programa de renderização 3D? Obviamente não era fazendo mais de centenas de linhas de código para um pequeno polígono. 

Um tempo depois, migrei de C para C++. Não por moda. Em C, cada função precisava de um prefixo – `engine_shader_compile`, `engine_shader_bind`, `engine_buffer_create`... o código funcionava, mas os nomes ficavam gigantes e repetitivos. C++ me permitiu agrupar essas funções em classes: `shader.compile()`, `mesh.bind()`, além da grande vantagem de ponteiros inteligentes. O código ficou mais limpo porque a linguagem passou a organizar o que eu já tentava fazer na mão com prefixos, e eu não precisava ficar lidando com **type cast** de ponteiros do tipo `void*`, além de me preocupar menos em alguns casos de limpeza de memória usando `shared_ptr`.

Adivinha? não é tão simples construir uma arquitetura para uma engine quanto escolher se voce quer criar um backend usando MVC ou Clean Architecture. Procurei em diversos locais, fóruns e livros. Ou o exemplo era simples demais (com um template que parecia Hello World), ou era uma grande engine com milhares de linhas. não era tão viável copiar uma estrutura, eu tive que entender cada componente de uma engine e organizar de alguma forma que faça sentido para mim.

Primeiro separei o projeto em 3 pastas:
- `App`
- `Core`
- `Engine`

A pasta `App` gerencia qualquer lógica de modelo ou outro tipo de classe que utilize
a engine, aqui eu irei criar algumas classes para políedros. Inclusive, uma das partes mais interessantes de fazer foi implementar a criação de uma esfera, farei também um artigo sobre sua implementação.

A pasta `Core` é o núcleo do projeto. Ali estão códigos relacionados à janela, visão computacional, *logger* ou outra coisa que eu vá adicionar futuramente nesse sentido.

E por último a pasta `Engine` que cobre todo o quesito de renderização gráfica, abstraindo o OpenGL.

Neste artigo focaremos apenas na parte da renderização gráfica. O objetivo do artigo não é demonstrar a implementação, e sim mostrar um possível modelo de porjeto para se basear caso deseje fazer algo do tipo.

A primeira classe que devemos criar é o `Shader`. Os objetivos dessa classe é abstrair a compilação e linkagem dos shaders, além checar de erros de compilação e/ou linkagem. Também adicionei nessa mesma classe as funções necessárias para adicionar um uniform.

```cpp
class Shader {
public:
  GLuint programID;  // id do programa shader

  // construtor
  Shader(const char *vtxShaderFilepath, const char *frgShaderFilepath);

  // destrutor (libera memoria do shader)
  ~Shader();

  void set_uniform(const char* uniform_name, const int value);
  void set_uniform(const char* uniform_name, const float value);
  void set_uniform(const char* uniform_name, const glm::mat4& matrix);
  void set_uniform(const char* uniform_name, const glm::vec3& vector);
  void set_uniform(const char* uniform_name, const glm::vec4& vector);

  inline void use() {
    glUseProgram(this->programID);
  }
};
```

Outra classe base necessária é `Vertex`, a ideia aqui é poder juntar coordenadas de posição, normal e coordenadas de textura num só lugar:

```cpp
class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex;

  // construtor
  Vertex(
    glm::vec3 position,
    glm::vec3 normal,
    glm::vec2 tex = glm::vec2(0, 0)
  );
};
```

Podemos então definir uma nova classe `Mesh`. Ela serve para conter toda a geometria. Observe que ela não possui função para atualizar os dados. Os dados definidos serão constantes. Depois iremos ver como mudar a posição de algum objeto no programa.

```cpp
class Mesh {
private:
  unsigned int VAO, VBO, EBO;

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices = {});

  // destrutor
  ~Mesh();

  size_t get_indices_size() const;

  // inicializa o mesh
  void setup_mesh();

  // vincula o mesh
  void bind() const;
};
```

Em seguida, vamos criar uma classe `Texture`. No meu caso, eu apenas preciso de luzes e cores, e implementar uma classe para textura não seria tão útil. No entando, criei a classe textura pois é um elemento necessário para poder dizer que fiz um engine de fato e eu queria ter a experiência completa. Todavia, eu me contentei com texturas 2D e deixei de lado texturas 3D. Observe que eu faço uma sobrecarga de função para receber a imagem de classes do OpenCV, pois como estou visando um app de realidade aumentada, preciso renderizar o que vem da câmera no fundo da cena com OpenGL. A melhor forma de fazer isso é com uma textura 2D.

```cpp
// observação importante!
// não sei se é pela versão do OpenGL, mas as imagens ficam distorcidas
// caso seus tamanhos de altura e largura nao sejam potencia de dois (1, 2, 4, 8, 16, 32, 64, 128...)
// por isso no construtor, no load e no update tem a opcao de redimensionar a 
// imagem da altura e largura original para a potencia de dois mais proxima


class Texture {
public:
  unsigned int id;

  // construtor sem definir ainda a imagem ( usar this.load() posteriormente )
  // obs: nao usar update antes de load no caso de nao ter uma imagem ainda

  Texture() = default;

  // construtor definindo a imagem
  Texture(std:: string& texture_filepath, bool to_power_of_2);

  // destrutor (libera a memoria da textura)
  ~Texture();

  // carrega uma imagem para a textura pelo nome do local do arquivo
  void load(std::string& texture_filepath, bool to_power_of_2);

  // carrega uma imagem da camera do OpenCV
  void load(const cv::Mat& frame, bool to_power_of_2);

  // atualiza a imagem usada na textura
  void update(const cv::Mat& frame, bool to_power_of_2);
  
  // vincula a textura à unidade de textura do contexto
  void bind(int num);

  // desvincula a textura à unidade de textura do contexto
  void unbind();
};
```

Para mexer os objetos no mundo, precisaremos de matrizes de transformação, por isso preferi abstrair isso na classe `Transform`. Note que o atributo dirty serve apenas para não recalcular, a todo momento, a model_matrix:

```cpp
class Transform {
private:
	glm::vec3 position = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

  mutable glm::mat4 cached_model_matrix;
  mutable bool dirty = true;
	
public:
	Transform() = default;
	Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

	void set_position(const glm::vec3& position);

	void set_rotation(const glm::quat& rotation);

	void set_scale(const glm::vec3& rotation);

	glm::mat4 get_model_matrix() const;
};
```

Para luzes, eu decidi não mexer com sua posição, apenas com a matriz de sua transformação, eu abstrai da seguinte forma:

```cpp
class Light {
private:
    glm::vec3 translation;
    glm::vec3 color;
    float intensity;

public:
    Light();
    Light(glm::vec3 color, float intensity = 1.0f);
    
    void translate(const glm::vec3& translation);
    void translate(float x, float y, float z);
    void set_translation(const glm::vec3& translation);
    void set_translation(float x, float y, float z);
    void set_color(const glm::vec3& color);
    void set_color(float r, float g, float b);
    void set_intensity(float intensity);
    
    glm::vec3 get_translation_matrix() const;
    glm::vec3 get_color() const;
    float get_intensity() const;   
};
```

Criei em seguinda uma classe `Material`, ela serve para juntar num lugar só o que envolve o desenho dos vértices em geral. As classes `Shader`, `Texture`, a cor e o brilho serão abstraidos da seguinte forma :
- OBS 1: deixei comentado qualquer coisa relacionado à textura de `ambient`, vi que é possível adicionar isso porém não senti necessário)
- OBS 2: usei o atributo `use_texture` para adicionar a possibilidade de nem sempre ser utilizado uma textura.

```cpp
class Material {
private:
  std::shared_ptr<Shader> shader;
  std::shared_ptr<Texture> texture_diffuse = nullptr;
  std::shared_ptr<Texture> texture_specular = nullptr;
  //  std::shared_ptr<Texture> texture_ambient;
  glm::vec4 color = glm::vec4(1.0f);
  float shininess = 32.0f;
  bool use_texture = false;

public:
  Material() = default;

  Material(
    std::shared_ptr<Shader> shader = nullptr,
    glm::vec4 color = {0.8f, 0.8f, 0.8f, 1.0f},
    float shininess = 32,
    // std::shared_ptr<Texture> texture_ambient = nullptr,
    std::shared_ptr<Texture> texture_diffuse = nullptr,
    std::shared_ptr<Texture> texture_specular = nullptr
  );


  void apply() const;

  template<typename ...Args>
  void set_uniform(Args... args) {
    this->shader->set_uniform(std::forward<Args>(args)...);
  }

  void set_color(glm::vec4 color);
  void set_color(float r, float g, float b, float a);

  void set_diffuse(std::shared_ptr<Texture> tex);
  void set_specular(std::shared_ptr<Texture> tex);
  // void set_ambient(std::shared_ptr<Texture> tex);

  void set_use_texture(bool value);
};
```

O proximo a ser implementado, será a classe `Model`, ela serve como forma de juntar cada conjunto de `Mesh`'s com o respectivo `Material` e `Transform` responsáveis para a sua redenrização. Note que o `Model` possui uma `Transform` para cada `Mesh`, essa matriz de transformação define apenas a posição dentro do modelo, mas a posição da model no mundo é definido por uma outra matriz `Transform` que será aplicada para todos os componentes da `Model`.

Para isso, decidi antes criar uma struct, para armazenar os 3 itens em 1 só. Não é algo obrigatório, mas fiz para melhorar o entendimento do código também simplificar manutenção se precisar:

```cpp
struct ModelPiece {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  Transform transform;
};
```

```cpp
class Model {
private:
  std::vector<ModelPiece> model_pieces;

public:
  Model() = default;

  Model(const std::vector<ModelPiece>& model_pieces);

  // assumindo que o tamanho dos vectores sao iguais
  Model(const std::vector<std::shared_ptr<Mesh>>& meshs,
        const std::vector<std::shared_ptr<Material>>& materials,
        const std::vector<Transform>& transforms);

  const std::vector<ModelPiece>& get_model_pieces() const;
};
```

A classe `Entity` se trata justamente de uma `Model` com seu `Transform` que define a posição geral na cena.

```cpp
class Entity {
private:
  std::shared_ptr<Model> model;
  Transform transform;

public:
  Entity() = default;
  Entity(
    const std::shared_ptr<Model> model,
    const Transform& transform
  );

  void set_translation(glm::vec3 pos);
  void set_rotation(glm::quat rotation);
  void set_scale(glm::vec3 scale);

  std::shared_ptr<Model> get_model() const;
  glm::mat4 get_model_matrix() const;
};
```

Além desses, temos também que implementar a classe `Camera`, ela serve para definir a posição do mundo que está contida no campo de visão.

```cpp
class Camera {
private:
  mutable glm::mat4 cached_view_matrix;
  mutable glm::mat4 cached_projection_matrix;
  mutable bool dirty_view = true;
  mutable bool dirty_projection = true;

  glm::vec3 position;
  glm::vec3 front = {0, 0, -1};
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 world_up = {0, 1, 0};

  float yaw = -90.0f;
  float pitch =  0.0f;

  float zoom =  45.0f;
  float aspect = 4.0f / 3.0f;
  
  /* mexer nisso depois
  float moviment_speed =  2.5f;
  float mouse_sensitivity =  0.1f;
  */

  void update_camera_vectors();

public:
  // construtor com vetores
  Camera(
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f),
    float yaw = -90.0f,
    float pitch = 0.0f,
    float aspect = 4.0f / 3.0f
  );

  // construtor com valores escalares
  Camera(
    float posX, float posY, float posZ,
    float world_upX, float world_upY, float world_upZ,
    float yaw,
    float pitch,
    float aspect = 4.0f / 3.0f
  );

  glm::mat4 get_view_matrix() const;
  glm::mat4 get_projection_matrix() const;
  glm::mat4 get_ortho_matrix() const;

  void set_position(const glm::vec3& pos);
  void set_aspect(const float aspect);
  void set_aspect(const float height, const float width);
  void set_orientation(float yaw, float pitch);
  void set_target(const glm::vec3& target);
  void set_world_up(const glm::vec3& up);
};
```

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// falta a renderer