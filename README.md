# riscxii

## Overview

Riscxii is a virtual machine developed as a personal project for a Systems Programming course. This project was an journey into the intricacies of system-level programming, completed over a span of about a week.

## Features

- RV32I Instruction Set Architecture: 
Implements a substantial subset of the RV32I ISA, enabling the execution of a wide range of binaries compatible with this architecture.
- Execution and Output: The virtual machine accepts a binary file's filepath as an argument and executes it, with outputs directed to stdout, mimicking the expected behavior of a standard execution environment.

## Getting Started

To use riscxii, follow these steps:

- Clone the Repository
- Build the vm with the make command
- Run the vm
## Testing

A suite of input-output tests has been developed to validate each instruction's implementation. While the test suite covers a significant portion of the instructions, it remains a work in progress. Future updates may include additional tests to enhance the reliability of the virtual machine.

## License

This project is licensed under the MIT license.

