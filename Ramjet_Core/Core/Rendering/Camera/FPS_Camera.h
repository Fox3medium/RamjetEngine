#pragma once

#include "Camera.h"

namespace Core
{
	namespace Rendering
	{
		namespace Camera
		{
			class FPS_Camera : public Camera 
			{
			private:
				bool m_Panning, m_Rotating;
				Maths::vec2 m_InitialMousePosition;
				Maths::vec3 m_InitialFocalPoint, m_InitialRotation;
				
				
			public:
				FPS_Camera(const Maths::mat4& projectionMatrix);
				~FPS_Camera();

				void update() override;
			private:
				void mousePan(const Maths::vec2& delta);
				void mouseRotate(const Maths::vec2& delta);
				void mouseZoom(float delta);				
			};
		}
	}
}