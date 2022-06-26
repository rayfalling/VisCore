/**
 * Created by Rayfalling on 2022/6/12.
 * */

#include "TestBuffer.h"

#include <iostream>

#include "Buffer/Buffer.h"
#include "Streaming/Streaming.h"

#ifdef _WIN32
#include <windows.h>
#endif


void TestBuffer() {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif
	std::cout << "Test Constraint Buffer Get Function......" << std::endl;

	const auto buffer = CreateBuffer(VisCore::Buffer::BufferType::Constraint, 200, '1');

	std::cout << "Buffer Data: " << buffer->GetData() << std::endl;
	std::cout << "Buffer Size: " << buffer->GetLength() << std::endl;
	std::cout << "Buffer Memory: " << buffer->GetMemSize() << std::endl;

	std::cout << "Test Buffer Update Function......" << std::endl;
	const char* newData = "这是测试数据";
	buffer->Update(0, strlen(newData), newData);
	std::cout << "Buffer Data: " << buffer->GetData() << std::endl;

	std::cout << "Test Dynamic Buffer......" << std::endl;
	const auto buffer1 = VisCore::Buffer::IBuffer::Create(VisCore::Buffer::BufferType::Dynamic, "测试数据11", strlen("测试数据11"));
	const auto buffer2 = VisCore::Buffer::IBuffer::Create(VisCore::Buffer::BufferType::Dynamic, "测试数据22", strlen("测试数据22"));
	std::cout << "Buffer Data: " << buffer1->GetData() << std::endl;
	std::cout << "Buffer Data: " << buffer2->GetData() << std::endl;

	std::cout << "Test Append Buffer......" << std::endl;
	*buffer1 += *buffer2;
	std::cout << "Buffer Data: " << buffer1->GetData() << std::endl;

	std::cout << "Test Clear Buffer......" << std::endl;
	buffer1->Clear();
	std::cout << "Buffer Data: " << buffer1->GetData() << std::endl;

	std::cout << "Test Streaming Buffer......" << std::endl;
	const char* streamingData = "这是Streaming测试数据";
	const auto  bufferStreaming = CreateBuffer(VisCore::Buffer::BufferType::Streaming, streamingData, strlen(streamingData));

	std::cout << "Buffer Data: " << bufferStreaming->GetData() << std::endl;
	auto* streaming = bufferStreaming.get()->GetStreaming();
	std::cout << "Streaming Tell: " << streaming->Tell() << std::endl;
	std::cout << "Streaming Seek End: " << streaming->Seek(0, VisCore::Streaming::SeekMode::SeekEnd) << std::endl;
	std::cout << "Streaming IsEOF: " << streaming->IsEof() << std::endl;

	const auto bufferRead = CreateBuffer(VisCore::Buffer::BufferType::Constraint, 10, 0);
	std::cout << "Streaming Seek: " << streaming->Seek(6) << std::endl;
	streaming->Read(bufferRead.get(), 9);
	std::cout << "Streaming Read: " << bufferRead->GetData() << std::endl;

	std::cout << "Buffer Access Out of Range exception Test" << std::endl;
	try {
		(*bufferRead)[12];
		std::cout << "Detect Buffer Access Out of Range Failed" << std::endl;

	} catch (std::out_of_range) {
		std::cout << "Detect Buffer Access Out of Range Success" << std::endl;
	}
}