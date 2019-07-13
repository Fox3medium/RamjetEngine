#pragma once

#include <Core/Common.h>
#include <Utils/Maths/maths.h>

namespace Core
{
	namespace Rendering
	{
		namespace Cameras
		{
			class CORE_API Camera 
			{
			protected:
				Maths::mat4 m_ProjectionMatrix, m_ViewMatrix;
				Maths::vec3 m_Position, m_Rotation, m_FocalPoint;

				float m_Pitch, m_Yaw;

				float m_Distance;
				float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;

			public:
				Camera(const Maths::mat4& projectionMatrix);
				~Camera();


				virtual void update() { }

				inline const Maths::vec3& getPosition() const { return m_Position; }
				inline void setPosition(const Maths::vec3& position) { m_Position = position; }

				inline const Maths::vec3& getRotation() const { return m_Rotation; }
				inline void setRotation(const Maths::vec3& rotation) { m_Rotation = rotation; }

				inline const Maths::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
				inline void setProjectionMatrix(const Maths::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

				inline void translate(const Maths::vec3& translation) { m_Position += translation; }
				inline void rotate(const Maths::vec3& rotation) { m_Rotation += rotation; }

				inline void translate(float x, float y, float z) { m_Position += Maths::vec3(x, y, z); }
				inline void rotate(float x, float y, float z) { m_Rotation += Maths::vec3(x, y, z); }

				inline const Maths::vec3& getFocalPoint() const { return m_FocalPoint; }

				inline const Maths::mat4& getViewMatrix() { return m_ViewMatrix; }

				Maths::vec3 getUpDirection();
				Maths::vec3 getRightDirection();
				Maths::vec3 getForwardDirection();

				Maths::vec3 getPosition();
				Maths::Quaternion getOrientation();

			};
		}
	}
}