/**
 * Created by Rayfalling on 2022/6/26.
 *
 * FileAccess enum
 * */

#pragma once

#ifndef VISCORE_FILE_ACCESS_H
#define VISCORE_FILE_ACCESS_H

#include <cstdint>

#include "VisCoreExport.generate.h"

namespace VisCore::File {
	/**
	 * \brief Contains constants for specifying the access you want for a file.
     * You can have Read, Write or ReadWrite access.
	 */
	enum class VIS_CORE_EXPORTS FileAccess : uint8_t {
		/**
		 * \brief Specifies read access to the file.
		 */
		Read = 1,

		/**
		 * \brief Specifies write access to the file.
		 */
		Write = 2,

		/**
		 * \brief Specifies read and write access to the file.
		 */
		ReadWrite = 3,
	};

	inline const char* VIS_CORE_EXPORTS ToString(FileAccess fileAccess) {
		switch (fileAccess) {
			case FileAccess::Read:
				return "Read";
			case FileAccess::Write:
				return "Write";
			case FileAccess::ReadWrite:
				return "ReadWrite";
			default:
				return "unknown";
		}
	}
}

#endif //VISCORE_FILE_ACCESS_H