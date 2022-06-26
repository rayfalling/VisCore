/**
 * Created by Rayfalling on 2022/6/12.
 * */

#include "Buffer/DynamicBuffer.h"

#include <stdexcept>

using namespace std;
using namespace VisCore::Buffer;
using namespace VisCore::Streaming;

DynamicBuffer::DynamicBuffer() : Data(0), Size(0) {
}

DynamicBuffer::~DynamicBuffer() {
	DynamicBuffer::Release();
}

DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) noexcept {
	// take buffer from other
	Size = other.Size;
	Data.swap(other.Data);

	other.Size = 0;
	other.Data.clear();
}

DynamicBuffer::DynamicBuffer(const DynamicBuffer& other) noexcept {
	// copy buffer
	Size = other.Size;
	Data = other.Data;
}

const DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// Copy the resource
	Size = other.Size;
	Data.swap(other.Data);

	other.Size = 0;
	other.Data.clear();

	return *this;
}

const DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// Copy the resource
	Size = other.Size;
	Data = other.Data;

	return *this;
}

char* DynamicBuffer::operator*() {
	return Data.data();
}

const char* DynamicBuffer::operator*() const {
	return Data.data();
}

char& DynamicBuffer::operator[](size_t position) {
	if (position > Size) {
		throw std::out_of_range("Access constraint buffer out of range!!!");
	}

	return Data[position];
}

IBuffer* DynamicBuffer::operator+(char& value) {
	Size += 1;
	Data.resize(Size + 1);
	Data[Size - 1] = value;
	Data[Size] = '\0';
	return this;
}

IBuffer* DynamicBuffer::operator+(IBuffer& buffer) {
	Append(buffer.GetData(), buffer.GetLength());
	return this;
}

IBufferPtr DynamicBuffer::operator+(IBufferPtr& buffer) {
	auto newBuffer = CreateBuffer(BufferType::Constraint, Size + buffer->GetLength(), 0);
	memcpy(**newBuffer, Data.data(), Size);
	memcpy(**newBuffer + Size, buffer->GetData(), buffer->GetLength());
	return newBuffer;
}

IBuffer* DynamicBuffer::operator+=(char& value) {
	return *this + value;
}

IBuffer* DynamicBuffer::operator+=(IBuffer& buffer) {
	return *this + buffer;
}

IBufferPtr DynamicBuffer::operator+=(IBufferPtr& buffer) {
	return *this + buffer;
}

BufferType DynamicBuffer::GetType() {
	return BufferType::Dynamic;
}

void DynamicBuffer::InitBuffer(const size_t size, const char initData) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data.resize(Size + 1, initData);
	Data[Size] = '\0';
}

void DynamicBuffer::InitBuffer(const char* ptr, const size_t size) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data.resize(Size + 1);
	memcpy(Data.data(), ptr, size);
	Data[Size] = '\0';
}

void DynamicBuffer::Release() {
	decltype(Data)().swap(Data);
	Size = 0;
}

bool DynamicBuffer::Update(const size_t offset, const size_t size, const char* ptr) {
	if (offset + size > Size) {
		Size = offset + size;
		Data.resize(Size + 1);
	}

	memcpy(Data.data() + offset, ptr, size);
	return true;
}

void DynamicBuffer::CopyTo(IBufferPtr buffer, const int length) const {
	if (Size == 0)
		return;

	const auto size = length == -1 || length > Size ? Size : length;
	buffer->Update(0, size < buffer->GetLength() ? size : buffer->GetLength(), Data.data());
}

bool DynamicBuffer::Append(const char& data) {
	Size += 1;
	Data.resize(Size + 1);
	Data[Size - 1] = data;
	Data[Size] = '\0';

	return true;
}

bool DynamicBuffer::Append(const char* data, const int length) {
	const auto oldSize = Size;

	Size += length;
	Data.resize(Size + 1);
	memcpy(Data.data() + oldSize, data, length);
	Data[Size] = '\0';

	return true;
}

bool DynamicBuffer::Insert(int index, const char* data, const int length) {
	Size += length;
	Data.insert(Data.begin() + index, data, data + length);

	return true;
}

void DynamicBuffer::Clear(const int length) {
	if (Size == 0)
		return;

	const auto clearSize = length == -1 || length > Size ? Size : length;
	memset(Data.data(), 0, clearSize);
}

size_t DynamicBuffer::GetLength() const {
	return Size;
}

size_t DynamicBuffer::GetMemSize() const {
	return sizeof(DynamicBuffer) + Data.capacity();
}

const char* DynamicBuffer::GetData() const {
	return Data.data();
}

IBufferPtr DynamicBuffer::CreateBufferCopy(const BufferType type, const int length) const {
	if (Size == 0)
		return CreateBuffer(type, length, 0);

	const auto size = length == -1 || length > Size ? Size : length;
	return CreateBuffer(type, Data.data(), size);
}

IStreaming* DynamicBuffer::GetStreaming() {
	return nullptr;
}
