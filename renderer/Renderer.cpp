#include "Renderer.h"

Renderer::Renderer()
	: m_playerShader(nullptr), m_worldShader(nullptr), m_deltaTime(0.0f)
{
	init();
}

void Renderer::setupShaders()
{
	m_playerShader = std::make_shared<Shader>(PLAYER_VERTEX_SHADER_SRC, PLAYER_FRAGMENT_SHADER_SRC);
	m_worldShader = std::make_shared<Shader>(WORLD_VERTEX_SHADER_SRC, WORLD_FRAGMENT_SHADER_SRC);
}

void Renderer::renderPlatofrm(std::vector<std::shared_ptr<GameObjectData>> platformDataList)
{
	//m_worldShader->Bind();



	//m_worldShader->Unbind();
}

void Renderer::renderPlayer(std::shared_ptr <GameObjectData>& playerData, bool applyGravity)
{
	m_playerShader->Bind();

	playerData->objectVAO->Bind();
	playerData->objectIBO->Bind();
	m_playerShader->UploadUniformMat4("u_Model", playerData->modelMatrix);
	RenderCommands::DrawIndex(playerData->objectVAO, GL_TRIANGLES);

	playerData->objectVAO->Unbind();

	m_playerShader->Unbind();
}

void Renderer::renderFloor(std::shared_ptr <GameObjectData> floorData)
{
	m_worldShader->Bind();
	
	floorData->objectVAO->Bind();
	floorData->objectIBO->Bind();
	m_worldShader->UploadUniformMat4("u_Model", floorData->modelMatrix);
	RenderCommands::DrawIndex(floorData->objectVAO, GL_TRIANGLES);
	
	floorData->objectVAO->Unbind();
	
	m_worldShader->Unbind();
}

unsigned Renderer::init()
{
	RenderCommands::SetClearColor(glm::vec4(0.3f, 0.0f, 0.0f, 1.0f));
	setupShaders();
	
	return 0;
}

void Renderer::draw(PerspectiveCamera camera, std::shared_ptr<GameObjectData> floorData, std::vector<std::shared_ptr<GameObjectData>> platformDataList, std::shared_ptr<GameObjectData>& playerData, bool applyGravity, float deltaTime)
{
	RenderCommands::Clear();
	RenderCommands::SetSolidMode();

	glm::mat4 viewProjectionMatrix = camera.GetViewProjectionMatrix();

	m_worldShader->Bind();
	m_worldShader->UploadUniformMat4("u_ViewProjection", viewProjectionMatrix);
	m_worldShader->Unbind();

	m_playerShader->Bind();
	m_playerShader->UploadUniformMat4("u_ViewProjection", viewProjectionMatrix);
	m_playerShader->Unbind();

	renderFloor(floorData);
	//renderPlatofrm(platformDataList);
	renderPlayer(playerData, applyGravity);
}

unsigned Renderer::shutdown()
{
	return 0;
}
