#pragma once


#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <condition_variable>

#include <sio_client.h>


class SocketModel
{
	public:

		static bool							acknowledgement;
		static int32_t						participants;
		static sio::socket::ptr				current_socket;
		static sio::client					api_socket;
		static std::mutex					m_generic_mutex;
		static std::condition_variable_any	_cond;

		static void init(
			const std::string &host,
			uint32_t user_id );

		static void cleanUp();

		static void bind_events(
			sio::socket::ptr &socket );

		static void sendMessage(
			const std::string &channel,
			const std::string &message );
};
