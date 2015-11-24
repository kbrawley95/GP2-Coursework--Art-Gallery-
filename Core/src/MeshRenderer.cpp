#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::RenderGameObject(Camera* camera, shared_ptr<Light> light)
{
	
	MVPMatrix = camera->GetLookAt()*gameObject->GetModelMatrix();

	if (gameObject->getShaderProgram() > 0){
		currentShaderProgam = gameObject->getShaderProgram();
		glUseProgram(currentShaderProgam);
	}

	GLint MVPLocation = glGetUniformLocation(currentShaderProgam, "MVP");

	GLint cameraPositionLocation = glGetUniformLocation(currentShaderProgam, "cameraPosition");

	GLint modelLocation = glGetUniformLocation(currentShaderProgam, "Model");

	GLint texture0Location = glGetUniformLocation(currentShaderProgam, "texture0");

	if (gameObject->getDiffuseMap() > 0){
		currentDiffuseMap = gameObject->getDiffuseMap();
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, currentDiffuseMap);
	glUniform1i(texture0Location, 0);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(gameObject->GetModelMatrix()));

	glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

	light->CalculateLighting(material);

	glBindVertexArray(gameObject->getVertexArrayObject());
	if (gameObject->getVertexArrayObject()>0)
		glDrawElements(GL_TRIANGLES, gameObject->getNumberOfIndices(), GL_UNSIGNED_INT, 0);

	for (int i = 0; i < gameObject->getNumberOfChildren(); i++)
	{
		renderGameObject(gameObject->getChild(i));
	}
}
