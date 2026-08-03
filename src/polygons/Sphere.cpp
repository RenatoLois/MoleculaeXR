#include "polygons/Sphere.hpp"
#include "core/Logger.hpp"
#include "engine/Material.hpp"
#include "engine/Vertex.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>
#include <cmath>


struct vertices_and_indices_pointers {
  std::shared_ptr<std::vector<Vertex>> vertices;
  std::shared_ptr<std::vector<unsigned int>> indices;
};


int num_lat_lines(int lat_level) {
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

int get_sphere_vertice_index(
    int lat_pos,
    int lon_pos,
    int lat_lines,
    int lon_lines,
    const std::shared_ptr< std::vector<Vertex> > vertices
) {
  lat_pos %= lat_lines + 2;  // lat_lines + 2 (indexado a 0) -> lat_lines + 1 
                             // -> +1 por causa do módulo da divisão -> lat_lines + 2
  lon_pos %= lon_lines;
  int lat_sides = lat_lines + 1;
  int lon_sides = lon_lines;
  int index = lat_pos * lat_sides + lon_pos;
  return index;
}

struct vertices_and_indices_pointers get_sphere_vertices_and_indices(int lat_level, int lon_level, float radius) {
  int lat_lines = num_lat_lines(lat_level);
  int lat_sides = lat_lines + 1;

  float single_lat_angle = M_PI / (float) lat_sides;

  int lon_sides = num_lon_rings(lon_level) * 2;
  int lon_lines = lon_sides;

  float single_lon_angle = 2 * M_PI / lon_sides;
  
  
  auto sphere_vertices = std::make_shared< std::vector<Vertex> >();
  sphere_vertices->reserve(lon_lines * (2 + lat_lines));  // lat_lines * lon_lines (total) + lon_lines * 2 (polos)

  // vértice norte
  for (int i = 1; i <= lon_sides; i++) {
    float x_tex_coord = (single_lon_angle * i) / (M_PI * 2);
    float y_tex_coord = 1.0f;
    Vertex nort_vertice(
      {0.0f, radius, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {x_tex_coord, y_tex_coord}
    );

    sphere_vertices->push_back(nort_vertice);
  }



  // para cada ponto do poligono exceto os polos
  for (int i = 1; i <= lat_lines; i++) {
    float y = y_lat_coord(single_lat_angle, M_PI / 2, i, radius);

    //float sub_circle_radius = sqrt((radius*radius) - (y*y));
    float sub_circle_radius = fabs(cos(M_PI / 2.0f + single_lat_angle * i) * radius);

    for (int j = 1; j <= lon_lines; j++) {
      float z = z_lon_coord(single_lon_angle, 0, j, sub_circle_radius);
      float x = x_lon_coord(single_lon_angle, 0, j, sub_circle_radius);

      float x_normal = x / radius;
      float y_normal = y / radius;
      float z_normal = z / radius;

      // calcular a posicao contando toda a esfera
      float x_tex_coord = (single_lon_angle * j) / (M_PI * 2);
      // calcular a posicao contando de um polo a outro apenas
      float y_tex_coord = (single_lat_angle * i) / (M_PI);

      sphere_vertices->push_back(
        Vertex(
          {x, y, z},
          {x_normal, y_normal, z_normal},
          {x_tex_coord, y_tex_coord}
        )
      );
    }
  }

  // vértice sul
  for (int i = 1; i <= lon_sides; i++) {
    float x_tex_coord = (single_lon_angle * i) / (M_PI * 2);
    float y_tex_coord = 0.0f;
    Vertex south_vertice(
      {0.0f, -radius, 0.0f},
      {0.0f, -1.0f, 0.0f},
      {x_tex_coord, y_tex_coord}
    );

    sphere_vertices->push_back(south_vertice);
  }


  auto sphere_indices = std::make_shared< std::vector<unsigned int> >();

  // indices do norte
  for(int i = 0; i < lon_lines; i++) {
    sphere_indices->push_back(i);
    sphere_indices->push_back(i + lon_lines);
    sphere_indices-> push_back( (i + 1) % (lon_lines) + lon_lines);
  }

  // indices da malha da esfera
  for(int i = 1; i < lat_lines; i++) {
    for(int j = 0; j < lon_lines; j++) {
      sphere_indices->push_back(i * lon_lines + j);
      sphere_indices->push_back( (i + 1) * lon_lines + j);
      sphere_indices->push_back( (i + 1) * lon_lines + (j + 1) % lon_lines );

      sphere_indices->push_back(i * lon_lines + j);
      sphere_indices->push_back( (i + 1) * lon_lines + (j + 1) % lon_lines );
      sphere_indices->push_back(i * lon_lines + (j + 1) % lon_lines);
    }
  }

  // indices do sul
  for(int i = 0; i < lon_lines; i++) {
    sphere_indices->push_back(i + lat_sides * lon_lines);
    sphere_indices-> push_back( ( (i + 1) % (lon_lines) ) + (lat_sides - 1) * lon_lines);
    sphere_indices->push_back(i + (lat_sides - 1) * lon_lines);
  }


  return {
    sphere_vertices,
    sphere_indices
  };
}

Sphere::Sphere(
  float radius,
  int lat_level,
  int lon_level,
  glm::vec4 sphere_color  // default = {1.0f, 0.0f, 0.0f, 1.0f}
) {
  auto [
    sphere_vertices,
    sphere_indices
  ] = get_sphere_vertices_and_indices(
    lat_level,
    lon_level,
    radius
  );

  Transform sphere_transform(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  );

  auto sphere_mesh = std::make_shared<Mesh>(*sphere_vertices, *sphere_indices);

  auto sphere_shader = std::make_shared<Shader>("res/shaders/polygon.vert", "res/shaders/polygon.frag");

  auto sphere_material = std::make_shared<Material>(
    sphere_shader,
    glm::vec4(0.5f, 0.5f, 0.9f, 1.0f)
  );

  sphere_material->set_color(sphere_color);

  auto sphere_model = std::make_shared<Model>(
    std::vector<std::shared_ptr<Mesh>>{sphere_mesh},
    std::vector<std::shared_ptr<Material>>{sphere_material},
    std::vector<Transform>{sphere_transform}
  );

  auto sphere_entity = std::make_shared<Entity>(sphere_model, sphere_transform);

  this->sphere_entity = sphere_entity;
}




Transform Sphere::get_transform() const {
  return this->sphere_entity->get_transform();
}




void Sphere::set_transform(const Transform& transform) {
  /*
  this->sphere_entity->set_translation(transform.get_position());
  this->sphere_entity->set_rotation(transform.get_rotation());
  this->sphere_entity->set_scale(transform.get_scale());
  */
  this->sphere_entity->set_transform(transform);
}




glm::vec4 Sphere::get_color() const {
  auto model_piece_vector = this->sphere_entity->get_model()->get_model_pieces();
  if(model_piece_vector.size() != 1) {
    Logger::fatal("Sphere entity->model->model_pieces_vector must have a size of 1, but it doesn't.");
  }

  return model_piece_vector[0].material->get_color();
}




void Sphere::set_color(const glm::vec4& color) {
  auto model_piece_vector = this->sphere_entity->get_model()->get_model_pieces();
  if(model_piece_vector.size() != 1) {
    Logger::fatal("Sphere entity->model->model_pieces_vector must have a size of 1, but it doesn't.");
  }

  return model_piece_vector[0].material->set_color(color);
}




void Sphere::render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light) {
  render.render(camera, this->sphere_entity, light);
}
