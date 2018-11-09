#include "Trial.h"
#include <SFML/Network.hpp>
#include <iostream>

bool verify() {
	sf::Http http("http://davetanks.surge.sh");

	sf::Http::Request request;
	request.setMethod(sf::Http::Request::Get);
	request.setUri("/trial");
	request.setHttpVersion(1, 1); // HTTP 1.1

	sf::Http::Response response = http.sendRequest(request);

	return response.getBody().find(VERIFY_CODE) != std::string::npos;
}