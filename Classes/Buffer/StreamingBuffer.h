/**
 * Created by Rayfalling on 2022/6/12.
 * 
 * Streaming buffer implementation
 * */

#pragma once

#include "Buffer/Buffer.h"

#include "Streaming/Streaming.h"

#ifndef VISCORE_BUFFER_STREAMING_H
#define VISCORE_BUFFER_STREAMING_H

namespace VisCore {
	/**
	 * \brief Const Buffer class, Alloc only once, Disallow Append()/Insert(), Allow Update()
	 */
	class StreamingBuffer : public IBuffer, public IStreaming {
	public:
		StreamingBuffer();
		~StreamingBuffer() override;

		StreamingBuffer(StreamingBuffer&& other) noexcept;      // Move construct
		StreamingBuffer(const StreamingBuffer& other) noexcept; // Copy construct

		//--------------- operator -----------------

		const StreamingBuffer& operator=(StreamingBuffer&& other) noexcept;      // Move assignment
		const StreamingBuffer& operator=(const StreamingBuffer& other) noexcept; // Copy assignment

		/**
		 * \brief Get char data
		 * \return char data ptr
		 */
		char* operator*() override;

		/**
		 * \brief Get char data
		 * \return char data ptr
		 */
		const char* operator*() const override;

		/**
		 * \brief Get char by position
		 * \param position position
		 * \return char value
		 */
		char& operator[](size_t position) override;

		/**
		 * \brief Append buffer with char value
		 * \param value char data
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBuffer* operator+(char& value) override;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBuffer* operator+(IBuffer& buffer) override;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBufferPtr operator+(IBufferPtr& buffer) override;

		/**
		 * \brief Append buffer with char value
		 * \param value char data
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBuffer* operator+=(char& value) override;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBuffer* operator+=(IBuffer& buffer) override;

		/**
		 * \brief Append two buffer
		 * \param buffer another buffer
		 * \return new buffer copy(constraint buffer)/current buffer(dynamic buffer)
		 */
		IBufferPtr operator+=(IBufferPtr& buffer) override;

		//--------------- function -----------------

		/**
		 * \brief Get current IBuffer type
		 * \return Buffer type enum
		 */
		[[nodiscard]]
		BufferType GetType() override;

		/**
		 * \brief init buffer by given data ptr and size
		 * \param size Buffer size
		 * \param initData data to fill
		 */
		void InitBuffer(size_t size, char initData) override;

		/**
		 * \brief init buffer by given data ptr and size
		 * \param ptr data ptr
		 * \param size Buffer size
		 */
		void InitBuffer(const char* ptr, size_t size) override;

		/**
		 * \brief Release all buffer Data
		 */
		void Release() override;

		/**
		 * \brief Update buffer region
		 * \param offset start position
		 * \param size update size
		 * \param ptr data ptr
		 */
		[[maybe_unused]]
		bool Update(size_t offset, size_t size, const char* ptr) override;

		/**
		 * \brief Copy buffer with special size to another buffer
		 * \param buffer destination buffer
		 * \param length special size, default -1 means all,
		 *				 if length large than buffer size, will use buffer size as length
		 */
		void CopyTo(IBufferPtr buffer, int length = -1) const override;

		/**
		 * \brief Append char to buffer, Only dynamic buffer support this operator
		 * \param data char data
		 */
		[[maybe_unused]]
		bool Append(const char& data) override;

		/**
		 * \brief Append data to buffer, Only dynamic buffer support this operator
		 * \param data char data
		 * \param length data length
		 */
		[[maybe_unused]]
		bool Append(const char* data, int length) override;

		/**
		 * \brief Insert data to buffer, Only dynamic buffer support this operator
		 * \param index start index
		 * \param data char data
		 * \param length data length
		 */
		[[maybe_unused]]
		bool Insert(int index, const char* data, int length) override;

		/**
		 * \brief Clear buffer data, not release, default -1 means all
		 */
		void Clear(int length = -1) override;

		/**
		 * \brief Get buffer length
		 * \return Current buffer length
		 */
		[[nodiscard]]
		size_t GetLength() const override;

		/**
		 * \brief Get buffer Memory size
		 * \return Current buffer Memory used
		 */
		[[nodiscard]]
		size_t GetMemSize() const override;

		/**
		 * \brief Get buffer raw data ptr
		 * \return Raw buffer data ptr
		 */
		[[nodiscard]]
		const char* GetData() const override;

		/**
		 * \brief Copy buffer with special size
		 * \param type buffer type
		 * \param length Copy size, default -1 means all,
		 *				 if length large than buffer size, will use buffer size as length
		 * \return IBufferPtr
		 */
		IBufferPtr CreateBufferCopy(BufferType type, int length = -1) const override;

		/**
		 * \brief Get current position
		 * \return Current position
		 */
		[[nodiscard]]
		size_t Tell() const override;

		/**
		 * \brief Read streaming
		 * \param buffer Read to buffer cache
		 * \param length Read length, default -1 means read to all buffer 
		 * \return Size successfully read
		 */
		[[maybe_unused]]
		size_t Read(IBuffer* buffer, size_t length) override;

		/**
		 * \brief Seek to position
		 * \param offset position offset
		 * \param seekMode seek mode
		 * \return new absolute position, if seek failed return -1
		 */
		[[maybe_unused]]
		size_t Seek(int64_t offset, SeekMode seekMode = SeekMode::SeekSet) override;

		/**
		 * \brief Get if stream read to end
		 * \return Is reach EOF
		 */
		[[nodiscard]]
		bool IsEof() const override;

		/**
		 * \brief Close current streaming
		 */
		void Close() override;

	private:
		/**
		 * \brief Data ptr
		 */
		std::shared_ptr<char[]> Data;

		/**
		 * \brief Buffer size
		 */
		size_t Size;

		/**
		 * \brief Current position
		 */
		size_t Position;
	};
}

#endif //VISCORE_BUFFER_STREAMING_H
