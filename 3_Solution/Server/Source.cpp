#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <mysql.h>
#include <sstream>
#include <vector>
#include <SFML/Network.hpp>
#include "RequestRegister.h"

using namespace std;
using namespace sf;

int main()
{
	TcpListener listener; //asculta conexiuni
	SocketSelector selector; //gestioneaza evenimentele pe socket
	vector<TcpSocket*>clients; 

	listener.listen(2002); 
	selector.add(listener);

	while (true) {
		cout << "sunt in while" << endl;
		if (selector.wait())	// astept sa se conecteze cineva
		{
			cout << "sunt in wait" << endl;
			if (selector.isReady(listener))		// listener-ul este gata sa primeasca date
			{
				cout << "sunt in isReady" << endl;
				TcpSocket* socket = new TcpSocket;		//creez socket pt a retine conexiunea
				listener.accept(*socket);				//verific daca exista conexiunea si daca poate accepta mesaje
				clients.push_back(socket);
				selector.add(*socket);					//il pot recunoaste la o conectare ulterioara
			}
			else   //daca nu e conexiune noua
			{
				for (int i = 0; i < clients.size(); i++) {
					cout << "sunt in for in vector clienti " <<i<< endl;
					if (selector.isReady(*clients[i]))    //verifica daca asta e socketul de la care a primit mesajul
					{
						cout << "sunt in isReady client " << i << endl;
						char buffer[1024];
						size_t received = 0;
						memset(buffer, 0, sizeof(buffer));
						clients[i]->receive(&buffer, sizeof(buffer), received);

						cout << "Primit: " << buffer << endl;
						string sentence(buffer);

						//decriptare cu functia din Tools;
						IRequest* request = IRequest::Factory::getRequest(sentence);
						request->gestionare_request();			//analizez cererea clientului
						string raspuns = request->gestionare_raspuns();
						memset(buffer, 0, sizeof(buffer));
						//criptare cu functia din Tools;
						cout << "Raspuns: " << raspuns << endl;
						
						clients[i]->send(raspuns.c_str(), raspuns.size());
						if (Tools::split(sentence, '/')[0] == "5") //logout
						{
							selector.remove(*clients[i]);
							clients[i]->disconnect();
							delete clients[i];
							clients.erase(clients.begin() + i);
							cout << "Conexiune intrerupta!" << endl;
							break;
							//se elimina socketul din selector, se deconecteaza si se sterge din vectorul de clienti
						}
					}
				}
				cout << "sunt in else dupa for" << endl;
			}
		}
	}
	for (vector<TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
		delete* it;


	return 0;
}