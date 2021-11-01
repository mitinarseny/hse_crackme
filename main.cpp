#include <cstdint>
#include <exception>
#include <iostream>
#include <thread>

std::string generate_key(std::string in);

int main() {
  std::string login, key, user_key;
  std::cout << "Enter login ([a-zA-Z0-9_-.]): ";
  std::cin >> login;

  key = generate_key(login);
  std::cout << key << std::endl;

  std::cout << "Enter key: ";
  std::cin >> user_key;

  if (user_key != key) {
    std::cerr << "Error!" << std::endl;
    return 1;
  };

  std::cout << "Success!" << std::endl;
}

// custom obfuscated ceaser implementation
std::string custom_ceasar(const std::string &in, std::uint8_t shift) {
  std::string res(in.size(), 0);
  static const std::string ALPHABET =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-.";
  static const std::string ALPHABET_SHIFT13 =
      "0123456789_-.ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	// get the index of c in s
  auto index = [&](const std::string &s, char c) -> std::size_t {
    for (std::size_t i = 0; i < s.size(); ++i) {
      if (c == s[i]) {
        return i;
      }
    }
    throw std::invalid_argument("only [a-zA-Z0-9_-.] allowed!");
  };
  for (std::size_t i = 0; i < in.size(); ++i) {
		// get the index of current character from ALPHABET if i is even or ALPHABET_SHIFT13 otherwise
    std::size_t ind = index(i % 2 == 0 ? ALPHABET : ALPHABET_SHIFT13, in[i]);
		// get the character on the index ind from ALPHABET and shift 13 left if it was
		// taken from ALPHABET_SHIFT13
		res[i] = ALPHABET[(ind + shift + (i % 2 == 1 ? -13 : 0)) % ALPHABET.size()];
  }
  return res;
}

std::string generate_key(std::string in) {
  const auto cpu_count = std::thread::hardware_concurrency();
	// return ceaser-encrypted with shift of cpu count
  return custom_ceasar(in, cpu_count);
}
