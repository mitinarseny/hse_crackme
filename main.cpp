#include <cstdint>
#include <iostream>
#include <thread>
#include <exception>

std::string generate_key(std::string in);

int main() {
	std::string login, key, user_key;
	std::cout << "Enter login ([a-zA-Z0-9_-.]): ";
	std::cin >> login;

	key = generate_key(login);

	std::cout << "Enter key: ";
	std::cin >> user_key;

	if (user_key != key) {
		std::cout << "Error!" << std::endl;
		return 1;
	};

	std::cout << "Success!" << std::endl;
}

std::string ceasar(const std::string &in, std::uint8_t shift) {
	std::string res(in.size(), 0);
	static const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-.";
	auto index = [&](char c) -> std::size_t {
		for (std::size_t i = 0; i < ALPHABET.size(); ++i) {
			if (c == ALPHABET[i]) {
				return i;
			}
		}
		throw std::invalid_argument("only [a-zA-Z0-9_-.] allowed!");
	};
	for (std::size_t i = 0; i < in.size(); ++i) {
		res[i] = ALPHABET[(index(in[i])+shift) % ALPHABET.size()];
	}
	return res;
}

std::string generate_key(std::string in) {
	const auto cpu_count = std::thread::hardware_concurrency();
	return ceasar(in, cpu_count);
}

