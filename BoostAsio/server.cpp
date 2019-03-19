#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include <string.h>

using boost::asio::ip::tcp;
using namespace std;

class session
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

	int string_length(char s[]) {
  	int i=0;
   	while(s[i]!='\0')
      i++;
   	return i;
	}

	//переворачивает слово
	void word_reverse(char st[]) {
   	int i,j,len;
   	char ch;
   	j = len = string_length(st) - 1;
   	i = 0;

   	while(i < j) {
      ch = st[j];
      st[j] = st[i];
      st[i] = ch;
      i++;
      j--;
   	}
	}

	//переворачивает все слова в строке
	void string_reverse(){
		int n = string_length(data_);
		char reverse[n+10]="",temp[n+10];
		int i,j;

   	for(i = 0; i < n; i++) {
      for(j = 0; i < n && data_[i]!=' '; ++i,++j) {
         temp[j] = data_[i];
      }

      temp[j] = '\0';

      word_reverse(temp);
      strncat(reverse, temp, j);
      strcat(reverse, " ");
   	}
		strcpy(data_, reverse);
	}


  void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)); //асинхронное чтение данных из сокета

  }

private:
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {

    if (!error)
    {
	string_reverse();
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error)); //ответ клиенту
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));//прием сообщения от клиента
    }
    else
    {
      delete this;
    }
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_service& io_service)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), 0))
  {
	boost::asio::ip::tcp::endpoint endpoint = acceptor_.local_endpoint();
	cout<<"~~Порт для подключения: "<<endpoint.port()<<endl;
    	start_accept();
  }

private:
  void start_accept()
  {
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {

    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
  try
  {
    boost::asio::io_service io_service;
    server s(io_service);

    io_service.run(); //цикл обработки событий
  }
  catch (exception& e)
  {
    cerr << "~~Исключения: " << e.what() << "\n";
  }

  return 0;
}
