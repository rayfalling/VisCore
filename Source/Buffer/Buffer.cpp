/**
 * Created by Rayfalling on 2022/6/12.
 * */

#include "Buffer/Buffer.h"

#include "Buffer/ConstraintBuffer.h"
#include "Buffer/DynamicBuffer.h"
#include "Buffer/StreamingBuffer.h"

using namespace std;
using namespace VisCore;

Buffer::IBufferPtr Buffer::CreateBuffer(const BufferType type, const size_t size, const char initData) {
	IBufferPtr buffer;
	switch (type) {
		case BufferType::Constraint:
			buffer = std::make_shared<ConstraintBuffer>();
			break;
		case BufferType::Dynamic:
			buffer = std::make_shared<DynamicBuffer>();
			break;
		case BufferType::Streaming:
			buffer = std::make_shared<StreamingBuffer>();
			break;
		default:
			break;
	}

	if (buffer)
		buffer->InitBuffer(size, initData);

	return buffer;
}

Buffer::IBufferPtr Buffer::CreateBuffer(const BufferType type, const char* ptr, const size_t size) {
	IBufferPtr buffer;
	switch (type) {
		case BufferType::Constraint:
			buffer = std::make_shared<ConstraintBuffer>();
			break;
		case BufferType::Dynamic:
			buffer = std::make_shared<DynamicBuffer>();
			break;
		case BufferType::Streaming:
			buffer = std::make_shared<StreamingBuffer>();
			break;
		default:
			break;
	}

	if (buffer)
		buffer->InitBuffer(ptr, size);

	return buffer;
}

Buffer::IBufferPtr Buffer::IBuffer::Create(const BufferType type, const size_t size, const char initData) {
	return CreateBuffer(type, size, initData);
}

Buffer::IBufferPtr Buffer::IBuffer::Create(const BufferType type, const char* ptr, const size_t size) {
	return CreateBuffer(type, ptr, size);
}