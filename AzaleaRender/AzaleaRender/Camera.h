#pragma once
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"

class Camera
{
private:
	float nearPlane;
	float farPlane;

	float fovy;
	glm::mat4 projMatrix;

	glm::vec3 translation;
	glm::vec3 rotation;
	glm::mat4 viewMatrix;

	glm::mat4 invViewMatrix;
	glm::mat4 transposeInvViewMatrix;
	glm::mat4 oldViewMatrix;

	glm::vec3 forward;

public:
	Camera(float n, float f, float fov);
	Camera(const Camera& other);
	~Camera();

	void OnWindowResize(int width, int height);

	float GetFOV();

	glm::mat4& GetProjectionMatrix();
	glm::mat4& GetViewMatrix();
	glm::mat4& GetInvViewMatrix();
	glm::mat4& GetTransposeInvViewMatrix();
	glm::mat4& GetOldViewMatrix();

	void SetPosition(glm::vec3 pos);
	void TranslateView(glm::vec3 translation);
	void RotateView(glm::vec3 rotation);

	void LookAt(glm::vec3 eye, glm::vec3 target);

	const glm::vec3& GetForwardVector() const
	{
		return forward;
	}

	const glm::vec3& GetPosition() const
	{
		return translation;
	}

	const glm::vec3& GetRotation() const
	{
		return rotation;
	}

private:
	void InitProjectionMatrix();
	void InitViewMatrix();
	void UpdateViewMatrix();
};

