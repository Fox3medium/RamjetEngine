#include "FPS_Camera.h"
#include <Managers/Control_Manager.h>
#include <Init/Window.h>

namespace Core
{
	namespace Rendering
	{
		namespace Camera
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
				Core::Manager::Control_Manager* C_Manager;

				if(C_Manager->isKeyPressed(GLFW_KEY_LEFT_ALT))
				{
					const vec2& mouse = m_Window->getMousePos();
					vec2 delta = mouse - m_InitialMousePosition;
					m_InitialMousePosition = mouse;

					/*if (window->ismousebuttonpressed(sp_mouse_middle))
						mousepan(delta);
					else if (window->ismousebuttonpressed(sp_mouse_left))
						mouserotate(delta);
					else if (window->ismousebuttonpressed(sp_mouse_right))
						mousezoom(delta.y);*/
				}
			}

			void FPS_Camera::mousePan(const Maths::vec2& delta)
			{
			}

			void FPS_Camera::mouseRotate(const Maths::vec2& delta)
			{
			}

			void FPS_Camera::mouseZoom(float delta)
			{
			}

		}
	}
}