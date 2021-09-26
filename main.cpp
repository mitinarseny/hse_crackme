#include <iostream>

std::string generate_key(std::string in);

int main() {
	std::cout << "Enter login: ";
	std::string login;
	std::cin >> login;
	auto key = generate_key(login);
	std::string user_key;
	std::cout << "Enter key: ";
	std::cin >> user_key;
	if (user_key != key) {
		std::cout << "Error!" << std::endl;
		return 1;
	};
	std::cout << "Success!" << std::endl;
}

std::string generate_key(std::string in) {
	return in;
}
