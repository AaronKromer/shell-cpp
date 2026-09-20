#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage

  while(true){
    std::string command;
    std::string input;
    std::cout << "$ ";
    std::cin >> command;
    std::getline(std::cin, input);
    if (!input.empty()) {
      input = input.substr(1);
    }
    if (command == "exit") {
      break;
    }
    if (command == "echo") {
      std::cout << input << std::endl;
      continue;
    }
    if (command == "type") {
      std::string supported[2] = {"echo", "exit"};
      for (int i=0; i<2;i++){
        if (supported[i] == input){
          std::cout << input << " is a shell builtin" << std::endl;
          continue;
        }
      }

      continue;
    }
    std::cout << command <<": command not found" << std::endl;


  }
}
