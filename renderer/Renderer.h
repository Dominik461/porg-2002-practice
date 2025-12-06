#ifndef RENDERER_H_
#define RENDERER_H_

#include "ShaderDefenitionsWorld.h"
#include "ShaderDefenitionsPlayer.h"
#include "GameObjectData.h"
#include "PerspectiveCamera.h"
#include "RenderCommands.h"
#include "Shader.h"


class Renderer
{
	std::shared_ptr<Shader> m_worldShader;
	std::shared_ptr<Shader> m_playerShader;

	float m_deltaTime;

	void setupShaders();

	void renderPlatofrm(std::vector<std::shared_ptr<GameObjectData>> platformDataList);
	void renderPlayer(std::shared_ptr <GameObjectData>& playerData);
	void renderFloor(std::shared_ptr <GameObjectData> floorData);

public:
	Renderer();

	unsigned init();
	void draw(PerspectiveCamera camera, std::shared_ptr <GameObjectData> floorData, std::vector<std::shared_ptr<GameObjectData>> platformDataList, std::shared_ptr <GameObjectData>& playerData, float deltaTime);
	unsigned shutdown();
};

#endif // !RENDERER_H_