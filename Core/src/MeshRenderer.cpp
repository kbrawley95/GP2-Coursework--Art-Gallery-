#include "MeshRenderer.h"

void MeshRenderer::Update()
{

}

void MeshRenderer::RenderGameObject(Camera* camera)
{
	MVPMatrix = camera->GetLookAt()*gameObject->GetModelMatrix();

	if (gameObject->GetShaderProgram() > 0){
		shader->currentShaderProgram = gameObject->GetShaderProgram();
		glUseProgram(shader->currentShaderProgram);
	}

	GLint MVPLocation = glGetUniformLocation(shader->currentShaderProgram, "MVP");

	GLint ambientLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(shader->currentShaderProgram, "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(shader->currentShaderProgram, "specularPower");
	GLint cameraPositionLocation = glGetUniformLocation(shader->currentShaderProgram, "cameraPosition");

	GLint modelLocation = glGetUniformLocation(shader->currentShaderProgram, "Model");

	GLint texture0Location = glGetUniformLocation(shader->currentShaderProgram, "texture0");

	if (gameObject->GetDiffuseMap() > 0){
		shader->currentDiffuseMap = gameObject->GetDiffuseMap();
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shader->currentDiffuseMap);
	glUniform1i(texture0Location, 0);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(gameObject->GetModelMatrix()));

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(shader->AmbientLightColour()));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(gameObject->GetAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(shader->DiffuseLightColour()));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(gameObject->GetDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(camera->GetLightDirection()));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(shader->SpecularLightColour()));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(gameObject->GetSpecularMaterial()));
	glUniform1f(specularPowerLocation, gameObject->GetSpecularPower());
	glUniform3fv(cameraPositionLocation, 1, value_ptr(camera->gameObject->transform.position.ConvertToVec3()));


	glBindVertexArray(gameObject->GetVertexArrayObject());
	if (gameObject->GetVertexArrayObject()>0)
		glDrawElements(GL_TRIANGLES, gameObject->GetNumberOfIndices(), GL_UNSIGNED_INT, 0);

}