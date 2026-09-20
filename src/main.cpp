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
      bool found = false;
      std::string supported[3] = {"echo", "exit", "type"};
      for (int i=0; i<3;i++){
        if (supported[i] == input){
          std::cout << input << " is a shell builtin" << std::endl;
          found = true;
          continue;
        }
      }
      if(found){
        continue;
      }
      else{
        std::cout << input <<": not found" << std::endl;
      }
    }
    std::cout << command <<": command not found" << std::endl;


  }
}
