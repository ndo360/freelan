/**
 * \file message_digest.cpp
 * \author Julien Kauffmann <julien.kauffmann@freelan.org>
 * \brief A message digest sample file.
 */

#include <cryptopen/hash/message_digest_context.hpp>
#include <cryptopen/error/error_strings.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

template <typename T>
std::string to_hex(const T& begin, const T& end)
{
	std::ostringstream oss;

	for (T i = begin; i != end; ++i)
	{
		oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*i);
	}

	return oss.str();
}

std::string to_hex(const void* buf, size_t buf_len)
{
	return to_hex(static_cast<const unsigned char*>(buf), static_cast<const unsigned char*>(buf) + buf_len);
}

void message_digest(const std::string& name, const std::string& data)
{
	try
	{
		cryptopen::hash::message_digest_algorithm algorithm(name);

		cryptopen::hash::message_digest_context ctx;

		ctx.initialize(algorithm);
		ctx.update(data.c_str(), data.size());
		std::vector<unsigned char> message_digest = ctx.finalize<unsigned char>();
		std::cout << name << ": " << to_hex(message_digest.begin(), message_digest.end()) << std::endl;
	}
	catch (cryptopen::error::cryptographic_exception& ex)
	{
		std::cerr << name << ": " << ex.what() << std::endl;
	}
}

int main()
{
	cryptopen::error::error_strings_initializer error_strings_initializer;
	cryptopen::hash::message_digest_initializer message_digest_initializer;

	std::cout << "Message digest sample" << std::endl;
	std::cout << "=====================" << std::endl;
	std::cout << std::endl;

	const std::string data = "some data from which we will compute the message digest";

	std::cout << "Data: " << data << std::endl;
	std::cout << std::endl;

	message_digest("MD5", data);
	message_digest("MD4", data);
	message_digest("SHA1", data);
	message_digest("SHA", data);
	message_digest("SHA224", data);
	message_digest("SHA256", data);
	message_digest("SHA384", data);
	message_digest("SHA512", data);
#if OPENSSL_VERSION_NUMBER >= 0x01000000
	message_digest("MDC2", data);
	message_digest("whirlpool", data);
#else
	message_digest("MD2", data);
#endif
	message_digest("RIPEMD160", data);

	return EXIT_SUCCESS;
}
