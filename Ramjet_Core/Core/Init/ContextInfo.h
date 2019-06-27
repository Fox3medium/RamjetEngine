#pragma once

namespace Core {

	namespace Init {

		struct ContextInfo {

			int major_version; // verions 4.XX where minor version is 4
			int minor_version; // Version XX.4 where minor version is 4
			bool bCore;

			ContextInfo() {
				major_version = 4;
				minor_version = 6;
				bCore = true;
			}

			ContextInfo(int inMajor, int inMinor, bool inCore) {
				major_version = inMajor;
				minor_version = inMinor;
				bCore = inCore;
			}

			ContextInfo(const ContextInfo& contextInfo) {
				major_version = contextInfo.major_version;
				minor_version = contextInfo.minor_version;
				bCore = contextInfo.bCore;
			}

			~ContextInfo() {

			}

			void operator=(const ContextInfo& contextInfo) {
				major_version = contextInfo.major_version;
				minor_version = contextInfo.minor_version;
				bCore = contextInfo.bCore;
			}

		};

	}

}