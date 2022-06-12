/**
 * Created by Rayfalling on 2022/6/12.
 *
 * Buffer Type enum
 * */
#pragma once

#ifndef VISCORE_BUFFER_TYPE_H
#define VISCORE_BUFFER_TYPE_H

#include <cstdint>

#include "VisCoreExport.generate.h"

namespace VisCore {
	/**
	 * \brief Buffer type enum for buffer
	 */
	enum class VIS_CORE_EXPORTS BufferType : uint8_t {
		Constraint = 0,
		Dynamic = 1,
		Streaming = 2
	};
}

#endif //VISCORE_BUFFER_TYPE_H