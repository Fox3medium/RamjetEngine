#pragma once

#include <Utils\String.h>

using Utils::String;

namespace Core {

	namespace Init {

		struct WindowInfo {

			String name;
			int width, height;
			int position_x, position_y;
			bool bisReshapable;
			bool bisFullscreen;

			WindowInfo() {
				name = "Game";
				width = 960;
				height = 540;
				position_x = 500;
				position_y = 300;
				bisReshapable = true;
				bisFullscreen = false;
			}

			WindowInfo(String inName, int start_position_x, int start_position_y, int inWidth, int inHeight, bool isReshapable, bool isFullscreen) {
				name = inName;
				width = inWidth;
				height = inHeight;
				position_x = start_position_x;
				position_y = start_position_y;
				bisReshapable = isReshapable;
				bisFullscreen = isFullscreen;
			}

			WindowInfo(const WindowInfo& windowInfo) {
				name = windowInfo.name;
				width = windowInfo.width;
				height = windowInfo.height;
				position_x = windowInfo.position_x;
				position_y = windowInfo.position_y;
				bisReshapable = windowInfo.bisReshapable;
				bisFullscreen = windowInfo.bisFullscreen;
			}

			~WindowInfo() {}

			void operator=(const WindowInfo& windowInfo) {
				name = windowInfo.name;
				width = windowInfo.width;
				height = windowInfo.height;
				position_x = windowInfo.position_x;
				position_y = windowInfo.position_y;
				bisFullscreen = windowInfo.bisFullscreen;
				bisReshapable = windowInfo.bisReshapable;
			}

		};
	}
}