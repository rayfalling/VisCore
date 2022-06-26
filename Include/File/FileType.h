/**
 * Created by Rayfalling on 2022/6/26.
 *
 * File Type enum
 * */

#ifndef VISCORE_FILE_TYPE_H
#define VISCORE_FILE_TYPE_H

#include <cstdint>

#include "VisCoreExport.generate.h"

namespace VisCore::File {
	/**
	 * \brief File type, mark file is streaming or is binary, not file format
	 */
	enum class VIS_CORE_EXPORTS FileType : uint8_t {
		/**
		 * \brief Mark file can be read/write as text file
		 */
		Text = 0,
		/**
		 * \brief Mark file must be read/write as binary file
		 */
		Binary = 1,
		/**
		 * \brief Mark file is read/write in streaming(binary) mode
		 */
		Streaming = 2
	};

	inline const char* VIS_CORE_EXPORTS ToString(FileType buffer) {
		switch (buffer) {
			case FileType::Text:
				return "Text";
			case FileType::Binary:
				return "Binary";
			case FileType::Streaming:
				return "Streaming";
			default:
				return "unknown";
		}
	}
}

#endif //VISCORE_FILETYPE_H