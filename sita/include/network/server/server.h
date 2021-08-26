#pragma once

#include "core/threadsafe_queue.h"

#include "core/types.h"
#include "network/connection.h"

namespace sita::network::server {

	class Server {
	public:
		Server(uint16_t port);
		virtual ~Server();

		bool start();
		void stop();

		void waitForClientConnection();

		void messageClient(std::shared_ptr<Connection> client, const Message& message);
		void messageAllClients(const Message& message, const std::shared_ptr<Connection>& ignoredClient = nullptr);

		void processMessages(u64 maxMessages = -1, bool wait = false);

		virtual void onClientValidated(std::shared_ptr<Connection> client);

	protected:
		virtual bool onClientConnect(std::shared_ptr<Connection> client);
		virtual void onClientDisconnect(std::shared_ptr<Connection> client);
		virtual void onMessage(std::shared_ptr<Connection> client, network::Message& message);

		core::Threadsafe_Queue<network::Owned_Message> m_MessagesIn;

		std::deque<std::shared_ptr<Connection>> m_connections;

		asio::io_context m_context;
		std::thread m_contextThread;

		asio::ip::tcp::acceptor m_acceptor;

		uint32_t m_idCounter = 10000;
	};

}
