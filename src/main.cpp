#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  bool quit=false
  while(! quit){
    std::string input;
    std::cout << "$ ";
    if (input == "exit") {

      break;

    }
    std::getline(std::cin, input);
    std::cout << input <<": command not found" << std::endl;


  }
}
