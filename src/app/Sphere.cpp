#include "app/Sphere.hpp"
#include "engine/Vertex.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>
#include <cmath>


int num_lat_sides(int lat_level) {
  return 3 * (int) round( pow(2, lat_level-1) ) - 1;
}

float x_lat_coord(float single_lat_angle, float lat_angle_offset, int pos, float radius) {
  return cos(lat_angle_offset + single_lat_angle * pos) * radius;
}

float x_lon_coord(float single_lon_angle, float lon_angle_offset, int pos, float radius) {
  return x_lat_coord(single_lon_angle, lon_angle_offset, pos, radius);
}

float y_lat_coord(float single_lat_angle, float lat_angle_offset, int pos, float radius) {
  return sin(lat_angle_offset + single_lat_angle * pos) * radius;
}

float z_lon_coord(float single_lon_angle, float lon_angle_offset, int pos, float radius) {
  return y_lat_coord(single_lon_angle, lon_angle_offset, pos, radius);
}

int num_lon_rings(int lon_level) {
  return (int) round( pow(2, lon_level) );
}

std::shared_ptr< std::vector<Vertex> > get_sphere_vertices(int lat_level, int lon_level, float radius) {
  int lat_sides = num_lat_sides(lat_level);
  int lat_lines = lat_sides - 1;

  float single_lat_angle = 2 * M_PI / (float) lat_sides;

  int lon_sides = num_lon_rings(lon_level) * 2;
  int lon_lines = lon_sides;

  float single_lon_angle = 2 * M_PI / lon_sides;
  
  
  auto sphere_vertices = std::make_shared< std::vector<Vertex> >(lon_lines * lat_lines + 2);


  // nort vertice
  for(int i = 1; i <= lon_sides; i++) {
    float x_tex_coord = (single_lon_angle * i) / (M_PI * 2);
    float y_tex_coord = 1.0f;
    Vertex nort_vertice(
      {0, radius, 0},
      {0, radius, 0},
      {x_tex_coord, y_tex_coord}
    );

    sphere_vertices->push_back(nort_vertice);
  }



  // para cada ponto do poligono exceto os polos
  for(int i = 1; i <= lat_lines; i++) {
    float y = y_lat_coord(single_lat_angle, M_PI / 2, i, radius);

    // float sub_circle_radius = fabs(cos(M_PI / 2 + single_lat_angle * i) * radius);
    float sub_circle_radius = sqrt((radius*radius) - (y*y));

    for(int j = 1; j <= lon_lines; j++) {
      float z = z_lon_coord(single_lon_angle, 0, j, sub_circle_radius);
      float x = x_lon_coord(single_lon_angle, 0, j, sub_circle_radius);

      float x_normal = x / radius;
      float y_normal = y / radius;
      float z_normal = z / radius;

      // calcular a posicao contando toda a esfera
      float x_tex_coord = (single_lon_angle * j) / (M_PI * 2);
      // calcular a posicao contando de um polo a outro apenas
      float y_tex_coord = (single_lat_angle * i) / (M_PI);

      Vertex(
          {x, y, z},
          {x_normal, y_normal, z_normal},
          {x_tex_coord, y_tex_coord}
      ); 
    }
  }

  // south vertice
  for(int i = 1; i <= lon_sides; i++) {
    float x_tex_coord = (single_lon_angle * i) / (M_PI * 2);
    float y_tex_coord = 0.0f;
    Vertex south_vertice(
      {0, -radius, 0},
      {0, -radius, 0},
      {x_tex_coord, y_tex_coord}
    );

    sphere_vertices->push_back(south_vertice);
  }

  
}

Sphere::Sphere(
    float radius,  // 1 caso nao definido
    int h_level,   // 4 caso nao definido
    int v_level    // 4 caso nao definido
) {

  std::vector<Vertex> sphere_vertices = get_sphere_vertices(h_level, v_level, radius);

  std::vector<unsigned int> cube_indices = {
  };






  Transform cube_transform(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  );

  auto cube_mesh = std::make_shared<Mesh>(cube_vertices, cube_indices);

  auto cube_shader = std::make_shared<Shader>("res/shaders/cube.vert", "res/shaders/cube.frag");

  auto cube_material = std::make_shared<Material>(
    cube_shader,
    glm::vec4(0.5f, 0.5f, 0.9f, 1.0f)
  );

  auto cube_model = std::make_shared<Model>(
    std::vector<std::shared_ptr<Mesh>>{cube_mesh},
    std::vector<std::shared_ptr<Material>>{cube_material},
    std::vector<Transform>{cube_transform}
  );

  auto cube_entity = std::make_shared<Entity>(cube_model, cube_transform);

  this->cube_entity = cube_entity;
}




void Cube::render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light) {
  render.render(camera, this->cube_entity, light);
}
