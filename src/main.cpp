#include <iostream>
#include <unistd.h>
#include <string>
#include <filesystem>
#include <optional>
#include <vector>
#include <sstream>


std::optional<std::string> pathSearch(std::string PATH, std::string exe){
  
  int len=PATH.length();
  int casebefore=0;
  std::string path;
  for(int i=0;i<len;i++){
    if(PATH[i] == ';' || PATH[i] == ':'){
      path=PATH.substr(casebefore, i-casebefore);
      casebefore=i+1;
      std::filesystem::path dirpath = std::string(path);
      bool dirpathExists = std::filesystem::is_directory(dirpath);
      std::string exepath_string = path + "/" + exe;
      std::filesystem::path exepath = std::string(exepath_string);
      bool exepathExists = std::filesystem::exists(exepath);
      if(exepathExists && dirpathExists && (access(exepath_string.c_str(), X_OK) == 0) ){
        return exepath_string;
      }
      
    }
  }
  return std::nullopt;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage

  while(true){
    std::string PATH = std::getenv("PATH");
    bool found = false;
    std::string command;
    std::string input;
    std::cout << "$ ";
    std::cin >> command;
    std::vector<std::string> args;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }
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
    if (command == "pwd") {
      std::cout << std::filesystem::current_path().string() << std::endl;
      continue;
    }
    if (command == "type") {
      std::vector<std::string> supported = {"echo", "exit", "type", "pwd"};
      bool isBuiltin = false;
      for (std::size_t i = 0; i < supported.size(); ++i){
        if (supported[i] == input){
          std::cout << input << " is a shell builtin" << std::endl;
          isBuiltin = true;
          break;
        }
      }
      if (isBuiltin) {
        continue;
      }
      if (auto executablePath = pathSearch(PATH, input))
      {
        std::cout << input << " is " << *executablePath << std::endl;
        continue;
      }else{
        std::cout << input <<": not found" << std::endl;
        continue;
      }

    }

    if((access(command.c_str(), X_OK) == 0) || (access(("./"+command).c_str(), X_OK) == 0)){
      int nArgs=args.size()+1;
      int result = std::system(command.c_str());
      continue;
    }
    if (auto executablePath = pathSearch(PATH, command))
    {
      int nArgs=args.size()+1;
      int result = std::system((command + " "+input).c_str());
      continue;
    }
  
    std::cout << command <<": command not found" << std::endl;


  }
}
