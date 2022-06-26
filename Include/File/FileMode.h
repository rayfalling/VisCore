/**
 * Created by Rayfalling on 2022/6/26.
 *
 * FileMode enum
 * */

#ifndef VISCORE_FILE_MODE_H
#define VISCORE_FILE_MODE_H

#include <cstdint>

#include "VisCoreExport.generate.h"

namespace VisCore::File {
	/**
	 * \brief Contains constants for specifying how the OS should open a file.
	 * These will control whether you overwrite a file, open an existing
	 * file, or some combination thereof.
	 *
	 * To append to a file, use Append (which maps to OpenCreate then we seek
	 * to the end of the file). To truncate a file or create it if it doesn't
	 * exist, use Create.
	 *
	 */
	enum class VIS_CORE_EXPORTS FileMode : uint8_t {
		/**
		 * \brief Creates a new file. If the file already exists, it is overwritten.
		 */
		Create = 1,

		/**
		 * \brief Opens an existing file.
		 */
		Open = 2,

		/**
		 * \brief Opens the file if it exists. Otherwise, creates a new file.
		 */
		OpenCreate = 3,

		/**
		 * \brief Opens an existing file. Once opened, the file is truncated so that its size is zero bytes.
		 */
		Truncate = 4,

		/**
		 * \brief Opens the file if it exists and seeks to the end. Otherwise, creates a new file.
		 */
		Append = 5,
	};

	inline const char* VIS_CORE_EXPORTS ToString(FileMode fileMode) {
		switch (fileMode) {
			case FileMode::Create:
				return "Create";
			case FileMode::Open:
				return "Open";
			case FileMode::OpenCreate:
				return "OpenCreate";
			case FileMode::Truncate:
				return "Truncate";
			case FileMode::Append:
				return "Append";
			default:
				return "unknown";
		}
	}

}
#endif //VISCORE_FILE_MODE_H