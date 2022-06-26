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

namespace VisCore::Buffer {
	/**
	 * \brief Buffer type enum for buffer
	 */
	enum class VIS_CORE_EXPORTS BufferType : uint8_t {
		/**
		 * \brief ConstraintBuffer, disallow resize/append/insert
		 */
		Constraint = 0,
		/**
		 * \brief DynamicBuffer, allow resize/append/insert
		 */
		Dynamic = 1,
		/**
		 * \brief StreamingBuffer, disallow resize/append/insert
		 */
		Streaming = 2
	};

	inline const char* ToString(BufferType buffer) {
		switch (buffer) {
			case BufferType::Constraint:
				return "Constraint";
			case BufferType::Dynamic:
				return "Dynamic";
			case BufferType::Streaming:
				return "Streaming";
			default:
				return "unknown";
		}
	}
}

#endif //VISCORE_BUFFER_TYPE_H