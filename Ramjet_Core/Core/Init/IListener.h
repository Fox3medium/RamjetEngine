#pragma once

// #include "glm/glm.hpp"

namespace Core {

	namespace Init {

		class IListener {

		public:

			virtual ~IListener() = 0;

			virtual void notifyBeginFrame() = 0;
			virtual void notifyDisplayFrame() = 0;
			virtual void notifyEndFrame() = 0;
			virtual void notifyReshape(int width, int height, int previous_widith, int previous_height) = 0;
			// virtual void notifyViewMatrixChanges(glm::mat4 inViewMatrix) = 0;

		};

		inline IListener::~IListener() {

		}

	}

}