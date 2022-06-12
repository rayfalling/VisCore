/**
 * Created by Rayfalling on 2022/6/12.
 *
 * Streaming class interface
 * */
#pragma once

#ifndef VISCORE_STREAMING_H
#define VISCORE_STREAMING_H

#include "SeekMode.h"
#include "VisCoreExport.generate.h"

namespace VisCore {
	class IBuffer;

	/**
	 * \brief Streaming Class Interface
	 */
	class VIS_CORE_EXPORTS IStreaming {
	public:
		virtual ~IStreaming() = default;

		/**
		 * \brief Get current position
		 * \return Current position
		 */
		[[nodiscard]]
		virtual size_t Tell() const = 0;

		/**
		 * \brief Read streaming
		 * \param buffer Read to buffer cache
		 * \param length Read length, default -1 means read to all buffer 
		 * \return Size successfully read
		 */
		[[maybe_unused]]
		virtual size_t Read(IBuffer* buffer, size_t length) = 0;

		/**
		 * \brief Seek to position
		 * \param offset position offset
		 * \param seekMode seek mode
		 * \return new absolute position, if seek failed return -1
		 */
		[[maybe_unused]]
		virtual size_t Seek(int64_t offset, SeekMode seekMode = SeekMode::SeekSet) = 0;

		/**
		 * \brief Get if stream read to end
		 * \return Is reach EOF
		 */
		[[nodiscard]]
		virtual bool IsEof() const = 0;

		/**
		 * \brief Close current streaming
		 */
		virtual void Close() = 0;
	};
}

#endif //VISCORE_STREAMING_H
