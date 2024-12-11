#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vertexArray.Bind();

	VertexBuffer vertexBuffer(vertices);

	ElementBuffer elementBuffer(indices);

	vertexArray.linkAttrib(vertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vertexArray.linkAttrib(vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vertexArray.linkAttrib(vertexBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vertexArray.linkAttrib(vertexBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vertexArray.Unbind();
	vertexBuffer.Unbind();
	elementBuffer.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	vertexArray.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse") num = std::to_string(numDiffuse++);
		else if (type == "specular") num = std::to_string(numSpecular++);

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "position"), Position.x, Position.y, Position.z);
	glUniform1f(glGetUniformLocation(shader.ID, "rotationAngle"), rotateAngles);
	glUniform1f(glGetUniformLocation(shader.ID, "elevationAngle"), elevationAngle);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}