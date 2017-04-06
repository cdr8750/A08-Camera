#include "Camera.h"
#include "RE\ReEng.h"
using namespace ReEng;

Camera::Camera()
{
	cameraPos = vector3(0.0f, 0.0f, -700.0f);
	cameraProjO = glm::ortho(-1080.0f, 1080.0f, -768.0f, 768.0f, 0.01f, 100000.0f);
	cameraProjP = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 100000.0f);
	cameraUp = vector3(0.0f,1.0f,0.0f);
	cameraForward = vector3(0.0f,0.0f,1.0f);
	cameraTarget = vector3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat();
	cameraYaw = 0;
	cameraPitch = 0.0f;
	cameraRoll = 0;
	mouseUse = false;
	ortho = false;

	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	//CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
	//CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

	//Calculate the position of the mouse and store it
	POINT pt;
	GetCursorPos(&pt);
	MouseX = pt.x;
	MouseY = pt.y;
}


Camera::~Camera()
{
}

void Camera::SwitchMouseUse() {
	mouseUse = !mouseUse;
}

void Camera::SwitchProjection() {
	ortho = !ortho;
}

matrix4 Camera::GetView(vector2 mouse) {
	y += mouse.y;
	x += mouse.x;
	if (mouseUse) {
		orientation = glm::quat(vector3(cameraPitch, cameraYaw, cameraRoll));
	}
	else {
		orientation = glm::quat(vector3(glm::radians((y) / 10), glm::radians((x) / 10), 0.0f));
	}
	cameraView = glm::toMat4(orientation) * glm::translate(cameraPos);
	return cameraView;
}

matrix4 Camera::GetProjection(bool ort) {
	if (ortho) {
		return cameraProjO;
	}
	else {
		return cameraProjP;
	}
}

void Camera::SetPosition(vector3 pos) {
	cameraPos = pos;
}

void Camera::SetTarget(vector3 tar) {
	cameraTarget = tar;
}

void Camera::SetUp(vector3 up) {
	cameraUp = up;
}

void Camera::MoveForward(float z) {
	cameraForward = vector3(0.0,0.0,z) * orientation;
	cameraPos += glm::normalize(cameraForward);
	//cameraPos.z += z;
	//cameraTarget.z += z;
}

void Camera::MoveSideways(float x) {
	cameraRight = vector3(x, 0.0, 0.0) * orientation;
	cameraPos += glm::normalize(cameraRight);
	//cameraPos.x += x;
	//cameraTarget.x += x;
}

void Camera::MoveVertical(float y) {
	cameraPos.y += y;
	cameraTarget.y += y;
}

void Camera::ChangePitch(float p) {
	cameraPitch += p;
}

void Camera::ChangeRoll(float r) {
	cameraRoll += r;
}

void Camera::ChangeYaw(float y) {
	cameraYaw += y;
}

