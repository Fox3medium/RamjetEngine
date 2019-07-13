#include "Camera.h"
#include <CoreBasicInclude.h>

namespace Core
{
	namespace Rendering
	{
		namespace Cameras
		{
			Camera::Camera(const Maths::mat4& projectionMatrix)
				: m_ProjectionMatrix(projectionMatrix)
			{
				m_ViewMatrix = Maths::mat4::Identity();
				m_Position = Maths::vec3();
				m_Rotation = Maths::vec3();

				m_PanSpeed = 0.0015f;
				m_RotationSpeed = 0.002f;
				m_ZoomSpeed = 0.2f;

				m_Position = Maths::vec3(0.0f, 25.0f, -25.0f);
				m_Rotation = Maths::vec3(90.0f, 0.0f, 0.0f);

				m_FocalPoint = Maths::vec3::Zero();
				m_Distance = m_Position.Distance(m_FocalPoint);

				m_Yaw = 3.0f * CORE_PI / 4.0f;
				m_Pitch = CORE_PI / 4.0f;
			}

			Camera::~Camera()
			{
			}

			Maths::vec3 Camera::getUpDirection()
			{
				return Maths::Quaternion::Rotate(getOrientation(), Maths::vec3::YAxis());
			}

			Maths::vec3 Camera::getRightDirection()
			{
				return Maths::Quaternion::Rotate(getOrientation(), Maths::vec3::XAxis());
			}

			Maths::vec3 Camera::getForwardDirection()
			{
				return Maths::Quaternion::Rotate(getOrientation(), -Maths::vec3::ZAxis());
			}

			Maths::vec3 Camera::getPosition()
			{
				return m_FocalPoint - getForwardDirection() * m_Distance;
			}

			Maths::Quaternion Camera::getOrientation()
			{
				return Maths::Quaternion::RotationY(-m_Yaw) * Maths::Quaternion::RotationX(-m_Pitch);
			}

		}
	}
}