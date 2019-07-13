#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>

#include <Utils/String.h>
#include <Utils/types.h>

struct ga_Sound;
struct ga_Handle;

namespace Core {

	namespace Audio {
	
		class CORE_API Sound {

		private:
			String m_Name;
			String m_FileName;

			ga_Sound* m_Sound;
			ga_Handle* m_Handle;
			int m_Position;

			uint m_Count;

			bool b_Playing;
			float m_Gain;

		public:
			Sound(const String& name, const String& filename);
			~Sound();

			void play();
			void loop();
			void pause();
			void resume();
			void stop();

			void setGain(float gain);

			inline const bool isPlaying() const { return b_Playing; }
			inline const float getGain() const { return m_Gain; }
			inline const String& getName() const { return m_Name; }
			inline const String& getFileName() const { return m_FileName; }

			friend void destroy_on_finish(ga_Handle* in_Handle, void* in_context);
			friend void loop_on_finish(ga_Handle* in_Handle, void* in_context);

		};

	}

}