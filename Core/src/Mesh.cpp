#include "Mesh.h"

Mesh::Mesh(shared_ptr<GameObject> g) : Component(g)
{
	material = nullptr;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	vertices.clear();
	indices.clear();
}

void Mesh::Render()
{
	if (material != nullptr)
	{
		mat4 MVPMatrix = gameObject->GetModelMatrix() * MainCamera->GetComponent<Camera>()->viewMatrix * MainCamera->GetComponent<Camera>()->projMatrix;
		if (material->shader->currentShaderProgram > 0)
		{
			glUseProgram(material->shader->currentShaderProgram);
			GLint MVPLocation = glGetUniformLocation(material->shader->currentShaderProgram, "MVP");
			GLint modelLocation = glGetUniformLocation(material->shader->currentShaderProgram, "Model");
			GLint texture0Location = glGetUniformLocation(material->shader->currentShaderProgram, "texture0");
			GLint cameraPositionLocation = glGetUniformLocation(material->shader->currentShaderProgram, "cameraPosition");

			if (material->GetDiffuseMap() > 0)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material->GetDiffuseMap());
				glUniform1i(texture0Location, 0);
			}

			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(gameObject->GetModelMatrix()));
			glUniform3fv(cameraPositionLocation, 1, value_ptr(MainCamera->transform.position.ConvertToVec3()));

			material->CalculateLighting(MainLight->GetComponent<Light>());

			glBindVertexArray(VAO);
			glBindBuffer(1, VBO);
			glBindBuffer(1, EBO);
			if (VAO > 0)
				glDrawElements(GL_TRIANGLES, gameObject->GetComponent<Mesh>()->indices.size(), GL_UNSIGNED_INT, 0);
		}
	}
}

void Mesh::GenerateBuffers()
{
	//Generate Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, gameObject->GetComponent<Mesh>()->vertices.size()*sizeof(Vertex), &(gameObject->GetComponent<Mesh>()->vertices[0]), GL_STATIC_DRAW);
	//create buffer
	glGenBuffers(1, &EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gameObject->GetComponent<Mesh>()->indices.size()*sizeof(int), &(gameObject->GetComponent<Mesh>()->indices[0]), GL_STATIC_DRAW);

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}