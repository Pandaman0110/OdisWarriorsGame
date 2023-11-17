#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Texture2D.h"
#include "GLSLShader.h"
#include "utility/OdisMath.h"
#include "Mesh.h"

namespace OdisEngine
{
	class SpriteRenderer
	{

	private:
		GLSLShader shader;
		Mesh mesh{};

	public:
		SpriteRenderer() {};
		
		SpriteRenderer(GLSLShader& shader) : shader(shader)
		{
			std::vector<float> vertices
			{
				0.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,

				0.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 0.0f, 1.0f, 0.0f
			};

			mesh.set_vertices(vertices, 4);
		};

		template <IntVectorType T>
		void draw_texture(Texture2D& texture, T position, float rotation)
		{
			shader.use();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

			model = glm::translate(model, glm::vec3(0.5f * texture.width, 0.5f * texture.height, 0.0f));
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * texture.width, -0.5f * texture.height, 0.0f));

			model = glm::scale(model, glm::vec3(texture.width, texture.height, 1.0f));

			shader.set_matrix4("model", model);
			shader.set_vector3f("sprite_color", glm::vec3(1.0f, 1.0f, 1.0f));

			glActiveTexture(GL_TEXTURE0);
			texture.bind();

			mesh.draw();
		}

		void draw() {};
	};
}

#endif