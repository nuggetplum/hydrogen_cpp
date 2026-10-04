#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "./tokenization.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Incorrect usage. Correct usage is...." << std::endl;
        std::cerr << "hydro <input.hy>" << std::endl;
        return EXIT_FAILURE;
    }
    

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Could not open input file: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream contents_stream;
    contents_stream << input.rdbuf();

    const auto tokens = Tokenizer(contents_stream.str()).tokenize();
    if (tokens.size() == 3 &&
        tokens[0].type == TokenType::return_ &&
        tokens[1].type == TokenType::int_lit &&
        tokens[2].type == TokenType::semi) {
        return std::stoi(tokens[1].value.value());
    }

    std::cerr << "Expected: return <integer>;" << std::endl;
    return EXIT_FAILURE;
}