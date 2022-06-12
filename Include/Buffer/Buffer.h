/**
 * Created by Rayfalling on 2022/6/12.
 *
 * Buffer Interface
 * */

#pragma once

#ifndef VISCORE_BUFFER_H
#define VISCORE_BUFFER_H

#include <memory>

#include "BufferType.h"
#include "VisCoreExport.generate.h"

namespace VisCore {
	class IStreaming;

	class IBuffer;
	typedef std::shared_ptr<IBuffer> IBufferPtr;

	VIS_CORE_EXPORTS IBufferPtr CreateBuffer(BufferType type, size_t size, char initData);
	VIS_CORE_EXPORTS IBufferPtr CreateBuffer(BufferType type, const char* ptr, size_t size);

	class VIS_CORE_EXPORTS IBuffer {
	public:
		IBuffer() = default;
		virtual ~IBuffer() = default;

		IBuffer(IBuffer&& other) = default;      // Move construct
		IBuffer(const IBuffer& other) = default; // Copy construct

		//--------------- operator -----------------

		IBuffer& operator=(IBuffer&& other) = default;      // Move assignment
		IBuffer& operator=(const IBuffer& other) = default; // Copy assignment

		/**
		 * \brief Get char data
		 * \return char data ptr
		 */
		virtual char* operator*() = 0;

		/**
		 * \brief Get char data
		 * \return char data ptr
		 */
		virtual const char* operator*() const = 0;

		/**
		 * \brief Get char by position
		 * \param position position
		 * \return char value
		 */
		virtual char& operator[](size_t position) = 0;

		/**
		 * \brief Append buffer with char value
		 * \param value char data
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBuffer* operator+(char& value) = 0;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBuffer* operator+(IBuffer& buffer) = 0;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBufferPtr operator+(IBufferPtr& buffer) = 0;

		/**
		 * \brief Append buffer with char value
		 * \param value char data
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBuffer* operator+=(char& value) = 0;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBuffer* operator+=(IBuffer& buffer) = 0;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		virtual IBufferPtr operator+=(IBufferPtr& buffer) = 0;

		//--------------- function -----------------

		/**
		 * \brief Get current IBuffer type
		 * \return Buffer type enum
		 */
		[[nodiscard]]
		virtual BufferType GetType() = 0;

		/**
		 * \brief init buffer by given data and size
		 * \param size Buffer size
		 * \param initData data to fill
		 */
		virtual void InitBuffer(size_t size, char initData) = 0;

		/**
		 * \brief init buffer by given data ptr and size
		 * \param ptr data ptr
		 * \param size Buffer size
		 */
		virtual void InitBuffer(const char* ptr, size_t size) = 0;

		/**
		 * \brief Release all buffer Data
		 */
		virtual void Release() = 0;

		/**
		 * \brief Update buffer region
		 * \param offset start position
		 * \param size update size
		 * \param ptr data ptr
		 */
		[[maybe_unused]]
		virtual bool Update(size_t offset, size_t size, const char* ptr) = 0;

		/**
		 * \brief Copy buffer with special size to another buffer
		 * \param buffer destination buffer
		 * \param length special size, default -1 means all,
		 *				 if length large than buffer size, will use buffer size as length
		 */
		virtual void CopyTo(IBufferPtr buffer, int length = -1) const = 0;

		/**
		 * \brief Append char to buffer, Only dynamic buffer support this operator
		 * \param data char data
		 */
		[[maybe_unused]]
		virtual bool Append(const char& data) = 0;

		/**
		 * \brief Append data to buffer, Only dynamic buffer support this operator
		 * \param data char data
		 * \param length data length
		 */
		[[maybe_unused]]
		virtual bool Append(const char* data, int length) = 0;

		/**
		 * \brief Insert data to buffer, Only dynamic buffer support this operator
		 * \param index start index
		 * \param data char data
		 * \param length data length
		 */
		[[maybe_unused]]
		virtual bool Insert(int index, const char* data, int length) = 0;

		/**
		 * \brief Clear buffer data, not release, default -1 means all
		 */
		virtual void Clear(int length = -1) = 0;

		/**
		 * \brief Get buffer length
		 * \return Current buffer length
		 */
		[[nodiscard]]
		virtual size_t GetLength() const = 0;

		/**
		 * \brief Get buffer Memory size
		 * \return Current buffer Memory used
		 */
		[[nodiscard]]
		virtual size_t GetMemSize() const = 0;

		/**
		 * \brief Get buffer raw data ptr
		 * \return Raw buffer data ptr
		 */
		[[nodiscard]]
		virtual const char* GetData() const = 0;

		/**
		 * \brief Create sub buffer copy with special size
		 * \param type buffer type
		 * \param length Copy size, default -1 means all,
		 *				 if length large than buffer size, will use buffer size as length
		 * \return IBufferPtr
		 */
		virtual IBufferPtr CreateBufferCopy(BufferType type, int length = -1) const = 0;

		/**
		 * \brief Get buffer Streaming Interface(Constraint/Dynamic will return nullptr)
		 * \return IStreaming ptr
		 */
		virtual IStreaming* GetStreaming() = 0;

		/**
		 * \brief create buffer by given data and size
		 * \param type buffer type
		 * \param size buffer size
		 * \param initData data to fill
		 * \return 
		 */
		static IBufferPtr Create(BufferType type, size_t size, char initData);
		/**
		 * \brief create buffer by given data ptr and size
		 * \param type buffer type
		 * \param ptr  data ptr
		 * \param size buffer size
		 * \return 
		 */
		static IBufferPtr Create(BufferType type, const char* ptr, size_t size);
	};
}

#endif //VISCORE_BUFFER_H