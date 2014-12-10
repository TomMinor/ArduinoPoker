#include <iostream>
#include <cstdlib>
#include <cstdint>

int main()
{
  uint16_t input = 5214;

  // Extract
  uint8_t a = (uint8_t)input;
  uint8_t b = (uint8_t)(input >> 8);

  // Combine
  uint16_t result = a | (b << 8);

  std::cout << "Input = " << input 
            << "(0x" << std::hex << input << ")\n";


  std::cout << "[0x" << std::hex << int(b) << "]"
            << "[0x" << std::hex << int(a) << "]"<< "\n";
  
  std::cout << "Result = " << result
            << "(0x" << std::hex << result << ")\n";

  return 0;
}
