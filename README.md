# Yacc/Lex/C Compiler Project - Implementation of a Programming Language with AST - December 2022 

The Yacc/Lex/C Compiler Project is a powerful undertaking that aims to develop a complete programming language and its corresponding compiler components. This project involves the integration of Yacc (Yet Another Compiler Compiler) and Lex (Lexical Analyzer) tools with C programming language to create a functional and efficient compiler for the designed language. The compiler supports various features, including declarations, attributions, and expressions, and uses the Abstract Syntax Tree (AST) representation for effective code generation.

## Features

- **Custom Programming Language**: The Yacc/Lex/C Compiler Project introduces a new programming language tailored to specific requirements. This language is designed to be expressive, easy to understand, and capable of handling a wide range of computational tasks.

- **Compiler Components**: The project encompasses the complete compiler components, including the lexical analyzer (implemented with Lex) and the parser (implemented with Yacc). These components work together to translate source code into intermediate code or directly to machine code.

- **Declarations and Attributions**: The designed programming language supports variable and function declarations and allows attributions of values to variables. The compiler ensures proper type-checking and scope resolution during declaration and attribution processing.

- **Expressions and Operators**: The language includes various operators to perform arithmetic, logical, and bitwise operations. The compiler translates expressions into corresponding intermediate or machine code to execute these operations efficiently.

- **Abstract Syntax Tree (AST)**: To optimize code generation and simplify semantic analysis, the compiler employs an Abstract Syntax Tree (AST). The AST represents the hierarchical structure of the source code, making it easier to analyze and translate into intermediate or machine code.

- **Symbol Table**: Variable declarations and their corresponding values are saved in a "simbol.txt" file.

- **Function Table**: Functions and their parameters are saved in a "functii.txt" file in the following format: 

## Technical Overview

The Yacc/Lex/C Compiler Project utilizes the Yacc and Lex tools to generate the parser and lexical analyzer, respectively, from specified grammars and patterns. The C programming language is employed to write the semantic actions, which process the input tokens and construct the Abstract Syntax Tree (AST). The AST serves as an intermediate representation of the source code, simplifying further processing and code generation.

### Key Technical Components:

- **Yacc (Yet Another Compiler Compiler)**: Yacc is a tool for generating parsers based on specified context-free grammars. It takes a formal grammar description and produces a parser capable of recognizing valid input tokens.

- **Lex (Lexical Analyzer)**: Lex is a tool used to generate lexical analyzers from regular expressions. It reads the input source code and breaks it down into a series of tokens for further parsing.

- **C Programming Language**: The compiler project is written in the C programming language. C provides the necessary flexibility and performance required to build a compiler and generate efficient code.

- **Abstract Syntax Tree (AST)**: The compiler constructs an Abstract Syntax Tree (AST) during the parsing phase. The AST represents the hierarchical structure of the source code and simplifies semantic analysis and code generation.

- **Code Generation**: After parsing and semantic analysis, the compiler generates intermediate code or directly translates the AST into machine code. This code generation phase is crucial for producing executable code for the target platform.

The Yacc/Lex/C Compiler Project is an ambitious venture that demonstrates the power of Yacc and Lex tools in building a robust compiler. By employing the Abstract Syntax Tree (AST) representation, the compiler achieves efficient code generation and enables the implementation of a custom programming language tailored to specific requirements.
