// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;

public:
	// Constructor that takes a message
    explicit CustomException(const std::string& msg) : message(msg) {}

	// Override the what() function to return the message
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

bool do_even_more_custom_application_logic()
{
    // Fixed: added runtime error
	throw std::runtime_error("Standard runtime error occurred in do_even_more_custom_application_logic.");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
 
    std::cout << "Running Custom Application Logic." << std::endl;

	// Fixed: wrapped risky call inside a try-catch block to handle std::exception
    try {
        if (do_even_more_custom_application_logic()) {
			std::cout << "Even More Custom Application Logic completed successfully." << std::endl;
        }
    }
	catch (const std::exception& e) {
		std::cerr << "Caught std::exception: " << e.what() << std::endl;
	}

    

	// Fixed: added catch block for CustomException
	catch (const CustomException& e) {
		std::cerr << "Caught CustomException: " << e.what() << std::endl;
	}


}

float divide(float num, float den)
{
	// Fixed Added explicit check for division by zero and throw a runtime error if denominator is zero
    if (den == 0.0f) {
		throw std::runtime_error("Division by zero error.");
    }
    return (num / den);
}

void do_division() noexcept
{


    float numerator = 10.0f;
    float denominator = 0;

    // Fixed wrapped the risky call inside a try-catch block to handle std::exception
    try {
        auto result = divide(numerator, denominator);
        std::cout << "Result of division: " << result << std::endl;
    }
    catch (const std::runtime_error& ex) {
        std::cerr << ">>> [Division Handler] Caught exception: " << ex.what() << std::endl; 
    }
}

    

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // Fixed: created main try-block wrapping the entire application test
    try {
        do_division();
		std::cout << std::endl; // Visual separation of output
        do_custom_application_logic();
    }
	// Fixed: Handler 1     catch (const std::runtime_error& ex) {
    catch (const CustomException& ex) {
		std::cerr << ">>> [Main Handler] Caught CustomException: " << ex.what() << std::endl;

	}
	// Fixed: Handler 2 fallback block for std::exception
	catch (const std::exception& ex) {
		std::cerr << ">>> [Main Handler] Caught std::exception: " << ex.what() << std::endl;
	}
	// Fixed: Handler 3 standard catch-all block for any other exceptions
    catch (...) {
        std::cerr << ">>> [Main Handler] Caught unknown exception." << std::endl;
    }
	std::cout << "Program completed." << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu