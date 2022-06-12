/**
 * Created by Rayfalling on 2022/6/12.
 * */

#include "Buffer/StreamingBuffer.h"

#include <stdexcept>

using namespace std;
using namespace VisCore;

StreamingBuffer::StreamingBuffer() : Data(nullptr), Size(0), Position(0) {
}

StreamingBuffer::~StreamingBuffer() {
	StreamingBuffer::Release();
}

StreamingBuffer::StreamingBuffer(StreamingBuffer&& other) noexcept {
	// take buffer from other
	Size = other.Size;
	Data = other.Data;
	Position = other.Position;

	other.Size = 0;
	other.Data = nullptr;
}

StreamingBuffer::StreamingBuffer(const StreamingBuffer& other) noexcept {
	// share buffer by shared_ptr
	Size = other.Size;
	Data = other.Data;
	Position = other.Position;
}

const StreamingBuffer& StreamingBuffer::operator=(StreamingBuffer&& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// take buffer from other
	Size = other.Size;
	Data = other.Data;
	Position = other.Position;

	other.Size = 0;
	other.Data.reset();

	return *this;
}

const StreamingBuffer& StreamingBuffer::operator=(const StreamingBuffer& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// Copy the resource
	Size = other.Size;
	Data = other.Data;
	Position = other.Position;

	return *this;
}

char* StreamingBuffer::operator*() {
	return Data.get();
}

const char* StreamingBuffer::operator*() const {
	return Data.get();
}

char& StreamingBuffer::operator[](const size_t position) {
	if (position > Size) {
		throw std::out_of_range("Access constraint buffer out of range!!!");
	}

	return Data[position];
}

IBuffer* StreamingBuffer::operator+(char& value) {
	const auto buffer = new StreamingBuffer();
	buffer->InitBuffer(Data.get(), Size + 1);
	(*buffer)[Size] = value;
	return buffer;
}

IBuffer* StreamingBuffer::operator+(IBuffer& buffer) {
	const auto newBuffer = new StreamingBuffer();
	memcpy(**newBuffer, Data.get(), Size);
	memcpy(**newBuffer + Size, buffer.GetData(), buffer.GetLength());
	return newBuffer;
}

IBufferPtr StreamingBuffer::operator+(IBufferPtr& buffer) {
	auto newBuffer = CreateBuffer(BufferType::Constraint, Size + buffer->GetLength(), 0);
	memcpy(**newBuffer, Data.get(), Size);
	memcpy(**newBuffer + Size, buffer->GetData(), buffer->GetLength());
	return newBuffer;
}

IBuffer* StreamingBuffer::operator+=(char& value) {
	return *this + value;
}

IBuffer* StreamingBuffer::operator+=(IBuffer& buffer) {
	return *this + buffer;
}

IBufferPtr StreamingBuffer::operator+=(IBufferPtr& buffer) {
	return *this + buffer;
}

BufferType StreamingBuffer::GetType() {
	return BufferType::Constraint;
}

void StreamingBuffer::InitBuffer(const size_t size, const char initData) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data = std::shared_ptr<char[]>(new char[Size + 1]);
	memset(Data.get(), initData, Size);
	Data[Size] = '\0';
}

void StreamingBuffer::InitBuffer(const char* ptr, const size_t size) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data = std::shared_ptr<char[]>(new char[Size + 1]);
	memcpy(Data.get(), ptr, Size);
	Data[Size] = '\0';
}

void StreamingBuffer::Release() {
	Data.reset();
	Size = 0;
}

bool StreamingBuffer::Update(const size_t offset, const size_t size, const char* ptr) {
	if (!Data || offset + size > Size)
		return false;

	memcpy(Data.get() + offset, ptr, size);
	return true;
}

void StreamingBuffer::CopyTo(IBufferPtr buffer, const int length) const {
	if (!Data || Size == 0)
		return;

	const auto size = length == -1 || length > Size ? Size : length;
	buffer->Update(0, size < buffer->GetLength() ? size : buffer->GetLength(), Data.get());
}

bool StreamingBuffer::Append(const char& data) {
	// Do nothing
	return false;
}

bool StreamingBuffer::Append(const char* data, const int length) {
	// Do nothing
	return false;
}

bool StreamingBuffer::Insert(const int index, const char* data, const int length) {
	// Do nothing
	return false;
}

void StreamingBuffer::Clear(const int length) {
	if (!Data || Size == 0)
		return;

	const auto clearSize = length == -1 || length > Size ? Size : length;
	memset(Data.get(), 0, clearSize);
}

size_t StreamingBuffer::GetLength() const {
	return Size;
}

size_t StreamingBuffer::GetMemSize() const {
	return sizeof(StreamingBuffer) + Size + 1;
}

const char* StreamingBuffer::GetData() const {
	return Data.get();
}

IBufferPtr StreamingBuffer::CreateBufferCopy(const BufferType type, const int length) const {
	if (!Data || Size == 0)
		return CreateBuffer(type, length, 0);

	const auto size = length == -1 || length > Size ? Size : length;
	return CreateBuffer(type, Data.get(), size);
}

size_t StreamingBuffer::Tell() const {
	return Position;
}

size_t StreamingBuffer::Read(IBuffer* buffer, const size_t length) {
	if (IsEof()) {
		return 0;
	}

	if (const size_t nextPosition = Position + length; nextPosition < Size) {
		const size_t copySize = buffer->GetLength() < length ? buffer->GetLength() : length;
		buffer->Update(0, copySize, Data.get() + Position);
		Position += copySize;
		return copySize;
	}

	const size_t delta = Size - Position;
	const size_t copySize = buffer->GetLength() < delta ? buffer->GetLength() : delta;
	buffer->Update(0, copySize, Data.get() + Position);
	Position += copySize;
	return delta;
}

size_t StreamingBuffer::Seek(const int64_t offset, const SeekMode seekMode) {
	switch (seekMode) {
		case SeekMode::SeekSet: {
			if (offset <= Size && offset >= 0) {
				Position = offset;
				return Position;
			}

			return -1;
		}
		case SeekMode::SeekCurrent: {
			if (offset >= 0) {
				const size_t delta = Position + offset;
				if (delta > Size) {
					return -1;
				}

				Position = delta;
				return Position;
			}

			if (-offset >= Position) {
				return -1;
			}

			Position -= -offset;
			return Position;
		}
		case SeekMode::SeekEnd: {
			if (offset <= 0 && -offset <= Size) {
				Position = Size - -offset;
				return Position;
			}

			return -1;
		}
		default:
			return -1;
	}
}

bool StreamingBuffer::IsEof() const {
	return Position == Size;
}

void StreamingBuffer::Close() {
	Release();
}