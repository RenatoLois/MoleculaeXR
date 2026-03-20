<pre>
  ┌──────────────────────────────────────────────────────┐              
  │                                                      │              
  │    .   ,     .             .           .   , ,-.     │              
  │    |\ /|     |             |            \ /  |  )    │              
  │    | V | ,-. | ,-. ,-. . . | ,-: ,-.     X   |-<     │              
  │    |   | | | | |-' |   | | | | | |-'    / \  |  \    │              
  │    '   ' `-' ' `-' `-' `-` ' `-` `-'   '   ` '  '    │              
  │                                                      │              
  └──────────────────────────────────────────────────────┘              
						
             (¨¨¨¨¨¨¨¨¨)                                              
              |¨¨¨¨¨¨¨|                                               
              |       |        Authors:
              |       |         * Renato Lóis Marcondes da Silva        
              |       |          Github: https://github.com/renatolois  
              |       |                                               
             /         \
            /           \   
           /             \
          /   .-'-.     .-\
         /-.-´     `-.-´   \     
        /                   \    
       /                     \   
      /                       \  
     /                         \ 
     \_________________________/ 
</pre>

# Moleculae XR

Este é um projeto open-source voltado para trabalhar com a visualização de moleculas utilizando tecnologia de realidade aumentada.

## Estrutura do Projeto
	- include/ -> arquivos de cabeçalho
	- include/core -> arquivos de cabeçalho dependente de plataforma
	- include/render -> arquivos de cabeçalho de código OpenGL
	- src/ -> implementação de código
	- src/core/ -> implementação de código dependente de plataforma
	- src/render/ -> implementação de código OpenGL
	- res/ -> recursos
	- res/assets/ -> recursos estáticos
	- res/shaders/ -> códigos shader (GLSL)

## Rodar o Projeto
```bash
	git clone https://github.com/RenatoLois/MoleculaeXR
	cd MoleculaeXR/
	mkdir build/
	cd build/
	cmake ..
	make
	./MoleculaeXR
```
