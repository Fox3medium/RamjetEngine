#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include <Utils/types.h>
#include <Utils/Maths/maths.h>
#include <Utils/Log.h>

#include <Rendering/Platform/OpenGL/CoreOpenGLTypes.h>

namespace Core 
{
	namespace Rendering 
	{
		struct CORE_API BufferLayoutType 
		{
			String name;
			uint type;
			uint size;
			uint count;
			uint offset;
			bool normalized;
		};

		class CORE_API BufferLayout
		{
		private:
			uint m_Size;
			std::vector<BufferLayoutType> m_Layout;
		public:
			BufferLayout();

			template<typename T>
			void push(const String& name, uint count = 1, bool normalized = false)
			{
				CORE_ASSERT(false, "Unkown type!");
			}

			template<> void push<float>(const String& name, uint count, bool normalized) 
				{ push(name, GL_FLOAT, sizeof(float) * count, count, normalized); }

			template<> void push<uint>(const String& name, uint count, bool normalized) 
				{ push(name, GL_UNSIGNED_INT, sizeof(uint) * count, count, normalized); }

			template<> void push<byte>(const String& name, uint count, bool normalized) 
				{ push(name, GL_UNSIGNED_BYTE, sizeof(byte) * count, count, normalized); }

			template<> void push<Maths::vec2>(const String& name, uint count, bool normalized) 
				{ push(name, GL_FLOAT, sizeof(Maths::vec2) * count, 2 * count, normalized); }
			template<> void push<Maths::vec3>(const String& name, uint count, bool normalized) 
				{ push(name, GL_FLOAT, sizeof(Maths::vec3) * count, 3 * count, normalized); }
			template<> void push<Maths::vec4>(const String& name, uint count, bool normalized)
				{ push(name, GL_FLOAT, sizeof(Maths::vec4) * count, 4 * count, normalized); }

			inline const std::vector<BufferLayoutType>& getLayout() const 
				{ return m_Layout; }

			inline uint getStride() const 
				{ return m_Size; }
		private:
			void push(const String& name, uint type, uint size, uint count, bool normalized);
		};
	}
}