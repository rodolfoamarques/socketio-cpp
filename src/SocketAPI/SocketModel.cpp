
#include "SocketModel.hpp"

std::condition_variable_any	SocketModel::_cond;
sio::client					SocketModel::api_socket;
sio::socket::ptr			SocketModel::current_socket;
std::mutex					SocketModel::m_generic_mutex;

int32_t						SocketModel::participants = -1;
bool						SocketModel::acknowledgement = false;


class connection_listener
{
	sio::client &handler;

	public:
		bool isConnected;

		connection_listener( sio::client &h ):
		handler( h ) {}

		void on_connected()
		{
			SocketModel::m_generic_mutex.lock();
			SocketModel::_cond.notify_all();

			isConnected = true;
			std::cout << "socket.io opened." << std::endl;

			SocketModel::m_generic_mutex.unlock();
		}

		void on_close( sio::client::close_reason const &reason )
		{
			SocketModel::m_generic_mutex.lock();
			isConnected = false;
			std::cout << "socket.io closed." << std::endl;
			SocketModel::m_generic_mutex.unlock();
		}
		
		void on_fail()
		{
			SocketModel::m_generic_mutex.lock();
			isConnected = false;
			std::cout << "socket.io failed." << std::endl;
			SocketModel::m_generic_mutex.unlock();
		}
};

void SocketModel::init(
	const std::string &host, uint32_t user_id )
{
	connection_listener l( api_socket );

	l.isConnected = false;

	api_socket.set_open_listener(
		std::bind(&connection_listener::on_connected, &l) );
	api_socket.set_close_listener(
		std::bind(&connection_listener::on_close, &l, std::placeholders::_1) );
	api_socket.set_fail_listener(
		std::bind(&connection_listener::on_fail, &l) );
	api_socket.connect( host );

	SocketModel::m_generic_mutex.lock();
	if( !l.isConnected )
	{
		_cond.wait( SocketModel::m_generic_mutex );
	}
	SocketModel::m_generic_mutex.unlock();

	current_socket = api_socket.socket();

	current_socket->on( "login",
		sio::socket::event_listener_aux(
			[&](std::string const &name, sio::message::ptr const &data, bool isAck, sio::message::list &ack_resp)
			{
				SocketModel::m_generic_mutex.lock();

				_cond.notify_all();
				acknowledgement = true;

				current_socket->off( "login" );

				SocketModel::m_generic_mutex.unlock();
			}
		)
	);
	current_socket->emit( "add user", "user" + std::to_string(user_id) );

	SocketModel::m_generic_mutex.lock();
	if( !acknowledgement && participants<0 )
	{
		_cond.wait( SocketModel::m_generic_mutex );
	}
	SocketModel::m_generic_mutex.unlock();

	bind_events( current_socket );
}

void SocketModel::cleanUp()
{
	SocketModel::m_generic_mutex.lock();

	current_socket->emit( "disconnect" );

	api_socket.close();
	api_socket.clear_con_listeners();

	SocketModel::m_generic_mutex.unlock();
}

void SocketModel::bind_events(
	sio::socket::ptr &socket )
{
	current_socket->on( "new message",
		sio::socket::event_listener_aux(
			[&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
			{
				SocketModel::m_generic_mutex.lock();

				std::string user = data->get_map()["username"]->get_string();
				std::string message = data->get_map()["message"]->get_string();

				std::cout << user << ": " << message << std::endl;

				SocketModel::m_generic_mutex.unlock();
			}
		)
	);

	current_socket->on( "user joined",
		sio::socket::event_listener_aux(
			[&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
			{
				SocketModel::m_generic_mutex.lock();

				std::string user = data->get_map()["username"]->get_string();
				participants  = data->get_map()["numUsers"]->get_int();

				bool plural = participants != 1;

				std::cout << user <<" joined" << "\nthere" <<
					(plural ? " are " : "'s ") << participants <<
					(plural ? " participants" : " participant") << std::endl;

				SocketModel::m_generic_mutex.unlock();
			}
		)
	);

	current_socket->on( "user left",
		sio::socket::event_listener_aux(
			[&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
			{
				SocketModel::m_generic_mutex.lock();

				std::string user = data->get_map()["username"]->get_string();
				participants  = data->get_map()["numUsers"]->get_int();

				bool plural = participants != 1;

				std::cout << user << " left" << "\nthere" <<
					(plural ? " are " : "'s ") << participants <<
					(plural ? " participants" : " participant") << std::endl;

				SocketModel::m_generic_mutex.unlock();
			}
		)
	);
}

void SocketModel::sendMessage(
	const std::string &event_type, const std::string &message )
{
	SocketModel::m_generic_mutex.lock();

	current_socket->emit( event_type, message );

	std::cout << "message: " << message << std::endl;
	std::cout << "event_type: " << event_type << std::endl;

	SocketModel::m_generic_mutex.unlock();
}
