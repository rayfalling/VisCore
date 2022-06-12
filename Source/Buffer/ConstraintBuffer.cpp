/**
 * Created by Rayfalling on 2022/6/12.
 * */

#include "Buffer/ConstraintBuffer.h"

#include <stdexcept>

using namespace std;
using namespace VisCore;


ConstraintBuffer::ConstraintBuffer() : Data(nullptr), Size(0) {
}

ConstraintBuffer::~ConstraintBuffer() {
	ConstraintBuffer::Release();
}

ConstraintBuffer::ConstraintBuffer(ConstraintBuffer&& other) noexcept {
	// take buffer from other
	Size = other.Size;
	Data = other.Data;

	other.Size = 0;
	other.Data = nullptr;
}

ConstraintBuffer::ConstraintBuffer(const ConstraintBuffer& other) noexcept {
	// copy buffer
	Size = other.Size;
	Data = new char[Size + 1];
	memcpy(Data, other.Data, Size);
	Data[Size] = '\0';
}

const ConstraintBuffer& ConstraintBuffer::operator=(ConstraintBuffer&& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// take buffer from other
	Size = other.Size;
	Data = other.Data;

	other.Size = 0;
	other.Data = nullptr;

	return *this;
}

const ConstraintBuffer& ConstraintBuffer::operator=(const ConstraintBuffer& other) noexcept {
	// Self-assignment detection
	if (&other == this)
		return *this;

	// Release any resource we're holding
	Release();

	// Copy the resource
	Size = other.Size;
	Data = new char[Size + 1];
	memcpy(Data, other.Data, Size);
	Data[Size] = '\0';

	return *this;
}

char* ConstraintBuffer::operator*() {
	return Data;
}

const char* ConstraintBuffer::operator*() const {
	return Data;
}

char& ConstraintBuffer::operator[](const size_t position) {
	if (position > Size) {
		throw std::out_of_range("Access constraint buffer out of range!!!");
	}

	return Data[position];
}

IBuffer* ConstraintBuffer::operator+(char& value) {
	const auto buffer = new ConstraintBuffer();
	buffer->InitBuffer(Data, Size + 1);
	(*buffer)[Size] = value;
	return buffer;
}

IBuffer* ConstraintBuffer::operator+(IBuffer& buffer) {
	const auto newBuffer = new ConstraintBuffer();
	memcpy(**newBuffer, Data, Size);
	memcpy(**newBuffer + Size, buffer.GetData(), buffer.GetLength());
	return newBuffer;
}

IBufferPtr ConstraintBuffer::operator+(IBufferPtr& buffer) {
	auto newBuffer = CreateBuffer(BufferType::Constraint, Size + buffer->GetLength(), 0);
	memcpy(**newBuffer, Data, Size);
	memcpy(**newBuffer + Size, buffer->GetData(), buffer->GetLength());
	return newBuffer;
}

IBuffer* ConstraintBuffer::operator+=(char& value) {
	return *this + value;
}

IBuffer* ConstraintBuffer::operator+=(IBuffer& buffer) {
	return *this + buffer;
}

IBufferPtr ConstraintBuffer::operator+=(IBufferPtr& buffer) {
	return *this + buffer;
}

BufferType ConstraintBuffer::GetType() {
	return BufferType::Constraint;
}

void ConstraintBuffer::InitBuffer(const size_t size, const char initData) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data = new char[Size + 1];
	memset(Data, initData, Size);
	Data[Size] = '\0';
}

void ConstraintBuffer::InitBuffer(const char* ptr, const size_t size) {
	// Release any resource we're holding
	Release();

	// init buffer
	Size = size;
	Data = new char[Size + 1];
	memcpy(Data, ptr, Size);
	Data[Size] = '\0';
}

void ConstraintBuffer::Release() {
	delete Data;
	Data = nullptr;
	Size = 0;
}

bool ConstraintBuffer::Update(const size_t offset, const size_t size, const char* ptr) {
	if (!Data || offset + size > Size)
		return false;

	memcpy(Data + offset, ptr, size);
	return true;
}

void ConstraintBuffer::CopyTo(IBufferPtr buffer, const int length) const {
	if (!Data || Size == 0)
		return;

	const auto size = length == -1 || length > Size ? Size : length;
	buffer->Update(0, size < buffer->GetLength() ? size : buffer->GetLength(), Data);
}

bool ConstraintBuffer::Append(const char& data) {
	// Do nothing
	return false;
}

bool ConstraintBuffer::Append(const char* data, const int length) {
	// Do nothing
	return false;
}

bool ConstraintBuffer::Insert(const int index, const char* data, const int length) {
	// Do nothing
	return false;
}

void ConstraintBuffer::Clear(const int length) {
	if (!Data || Size == 0)
		return;

	const auto clearSize = length == -1 || length > Size ? Size : length;
	memset(Data, 0, clearSize);
}

size_t ConstraintBuffer::GetLength() const {
	return Size;
}

size_t ConstraintBuffer::GetMemSize() const {
	return sizeof(ConstraintBuffer) + Size + 1;
}

const char* ConstraintBuffer::GetData() const {
	return Data;
}

IBufferPtr ConstraintBuffer::CreateBufferCopy(const BufferType type, const int length) const {
	if (!Data || Size == 0)
		return CreateBuffer(type, length, 0);

	const auto size = length == -1 || length > Size ? Size : length;
	return CreateBuffer(type, Data, size);
}