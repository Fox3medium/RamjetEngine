#include "FPS_Camera.h"
#include <CoreBasicInclude.h>
#include <Managers/Control_Manager.h>
#include <Init/Window.h>

namespace Core
{
	namespace Rendering
	{
		namespace Cameras
		{
			using namespace Maths;

			FPS_Camera::FPS_Camera(const Maths::mat4& projectionMatrix)
				: Camera(projectionMatrix)
			{
				
			}

			FPS_Camera::~FPS_Camera()
			{
			}

			void FPS_Camera::update()
			{
				Core::Init::Window* m_Window = Core::Init::Window::getWindowClass();

				if (Control_Manager::isKeyPressed(GLFW_KEY_LEFT_ALT))
				{
					vec2 delta = m_Window->getMousePos();

					if (Control_Manager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_3))
						mousePan(delta);
					else if (Control_Manager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
						mouseRotate(delta);
					else if (Control_Manager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
						mouseZoom(delta.y);
				}

				Quaternion orientation = getOrientation();
				m_Rotation = orientation.ToEulerAngles() * (180.0f / M_PI);
				m_ViewMatrix = mat4::Rotate(orientation.Conjugate());
				m_ViewMatrix *= mat4::Translate(-getPosition());
			}

			void FPS_Camera::mousePan(const Maths::vec2& delta)
			{
				m_FocalPoint += -getRightDirection() * delta.x * m_PanSpeed * m_Distance;
				m_FocalPoint += getUpDirection() * delta.y * m_PanSpeed * m_Distance;
			}

			void FPS_Camera::mouseRotate(const Maths::vec2& delta)
			{
				float yawSign = getUpDirection().y < 0 ? -1.0f : 1.0f;
				m_Yaw += yawSign * delta.x * m_RotationSpeed;
				m_Pitch += delta.y * m_RotationSpeed;
			}

			void FPS_Camera::mouseZoom(float delta)
			{
				m_Distance -= delta * m_ZoomSpeed;
			}

		}
	}
}