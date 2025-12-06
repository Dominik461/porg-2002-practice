#ifndef GAME_H_
#define GAME_H_

#include "GLFWApplication.h"
#include "GameObjectData.h"
#include "GeometricTools.h"
#include "Renderer.h"
#include "PerspectiveCamera.h"
#include "MatrixOperations.h"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Game : GLFWApplication
{
	struct Player
	{
		std::shared_ptr<GameObjectData> data = std::make_shared<GameObjectData>();
		glm::vec3 moveDir = glm::vec3(0.0f);
		const float SPEED = 5.0f;
		bool isGrounded = false;
	};

	struct Floor
	{
		std::shared_ptr<GameObjectData> data = std::make_shared<GameObjectData>();
	};

	struct Platform
	{
		std::shared_ptr<GameObjectData> data = std::make_shared<GameObjectData>();
	};

	const int WINDOW_HEIGHT = 600;
	const int WINDOW_WIDTH = 800;
	const float GRAVITY = -9.0f;

	GLFWwindow* m_window;
	double m_startTime;
	// Delta time for frame-independent movement
	float m_deltaTime;
	float m_lastFrameTime;

	bool jump = false;

	PerspectiveCamera camera;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 15.0f);

	std::shared_ptr<Renderer> m_renderer;

	std::shared_ptr <Floor> m_floor;
	std::shared_ptr <Player> m_player;
	std::vector< std::shared_ptr<Platform>> m_platforms;
	std::vector< std::shared_ptr<GameObjectData>> m_platformsData;

	bool initializeOpenGL();

	void createPlayer();
	void createPlatforms();
	void createFloor();
	void createCamera();
	void updateCamera();

	bool checkCollison();
	void movePlayer();
	void handleInput();

	void extractAxes(const glm::mat4& transform);
public:
	Game();

	unsigned Init() override;
	unsigned Run() const override;
	void Shutdown() override;


	GLFWwindow* getWindow() const { return m_window; }
};



#endif