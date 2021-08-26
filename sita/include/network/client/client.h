#pragma once

#include "core/types.h"

#include "core/threadsafe_queue.h"

#include "network/net_common.h"
#include "network/connection.h"
#include "network/message.h"

namespace sita::network::client {

	class Client {
	public:
		Client() = default;
		virtual ~Client();

		bool connect(const std::string& host, uint16_t port);
		void disconnect();

		void send(const Message& msg) const;

		void setId(u32 id) const;

		[[nodiscard]] bool isConnected() const;
		[[nodiscard]] u32 getId() const;
		[[nodiscard]] core::Threadsafe_Queue<Owned_Message>& incoming();

	protected:
		asio::io_context m_context;
		std::thread m_contextThread;

		std::unique_ptr<Connection> m_connection;

	private:
		core::Threadsafe_Queue<Owned_Message> m_messagesIn;
	};

}
