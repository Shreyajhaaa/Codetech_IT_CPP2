FILE-MANAGEMENT-TOOL *COMPANY *: CODTECH IT SOLUTIONS

*NAME *: SHREYA KUMARI

*INTERN ID *: CT12VYO

"DOMAIN *: C++ PROGRAMING

"DURATION *: 8 WEEEKS

*MENTOR *: NEELA SANTOSH

*DESCRIOTON:
Multithreaded File Compression Tool

Introduction

The Multithreaded File Compression Tool is a C++ program that compresses large files efficiently using multiple threads. This tool leverages zlib for data compression and C++ threading libraries to divide the compression task into smaller chunks, enabling parallel execution for faster processing.

Features

Multithreading Support: The program uses multiple threads to compress different portions of the file simultaneously, enhancing performance.

Data Compression: It uses the zlib library to perform lossless data compression.

Dynamic Thread Allocation: Automatically assigns the optimal number of threads based on system hardware capabilities.

Chunk-Based Compression: Splits the input file into equal-sized chunks, each processed independently by a separate thread.

Error Handling: Detects and reports file I/O errors and compression failures.

How It Works

File Reading
The program opens the input file in binary mode to read its content. It calculates the file size and determines how to split the file into chunks based on the number of threads.

Chunk Division
The file is divided into N chunks, where N is the number of available threads. Each chunk is assigned to a separate thread for compression.

Compression
Each thread calls the compressChunk() function, which uses the zlib library to compress the assigned chunk. The compressed data is stored in a vector.

Synchronization
The std::thread::join() method ensures all threads finish execution before writing the compressed data to the output file.

Writing Output
After compression, the program writes the compressed data chunks sequentially to the output file in binary mode.

Technical Details

Libraries Used

iostream: Standard input-output operations

fstream: File input-output stream

thread: Multithreading functionality

mutex: Thread synchronization

vector: Dynamic array storage

zlib.h: Compression library

Functions

Function

Description

compressChunk()

Compresses a single chunk of data

compressFileMultithreaded()

Splits the file into chunks and assigns threads for compression

Multithreading Approach

The program uses std::thread to launch parallel threads.

The number of threads is set to the minimum of available hardware threads or 4 to balance performance and resource usage.

Error Handling

Displays an error message if the input or output file cannot be opened.

Clears the output buffer if compression fails.

Use Cases

Compressing large text files or binary data files.

Speeding up file compression on multi-core systems.

Learning multithreaded programming and file handling in C++.

Future Improvements

Decompression feature.

Progress display during compression.

Support for different compression algorithms.

Encryption support for compressed files.

Conclusion

The Multithreaded File Compression Tool demonstrates the power of C++ multithreading and zlib compression for efficient file management. This project is a great example of how parallel processing can significantly improve the performance of time-consuming tasks.

OUTPUT:![Image](https://github.com/user-attachments/assets/7ae2734e-657e-4975-a141-7ba69a10963a)
