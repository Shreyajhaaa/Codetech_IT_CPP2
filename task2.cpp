#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <zlib.h> // zlib library for compression

// Function to compress a chunk of data
void compressChunk(const std::vector<char>& input, std::vector<char>& output) {
    uLongf compressedSize = compressBound(input.size()); // Get the maximum possible compressed size
    output.resize(compressedSize); // Resize output buffer to hold compressed data

    // Compress the input data
    if (compress(reinterpret_cast<Bytef*>(output.data()), &compressedSize, 
                 reinterpret_cast<const Bytef*>(input.data()), input.size()) == Z_OK) {
        output.resize(compressedSize); // Resize output to actual compressed size
    } else {
        std::cerr << "Compression failed for a chunk\n";
        output.clear(); // Clear output if compression fails
    }
}

// Function to compress a file using multiple threads
void compressFileMultithreaded(const std::string& inputFile, const std::string& outputFile, size_t numThreads) {
    std::ifstream in(inputFile, std::ios::binary); // Open input file in binary mode
    if (!in) { // Check if file opened successfully
        std::cerr << "Error opening input file\n";
        return;
    }
    
    std::ofstream out(outputFile, std::ios::binary); // Open output file in binary mode
    if (!out) { // Check if file opened successfully
        std::cerr << "Error opening output file\n";
        return;
    }

    // Determine file size
    in.seekg(0, std::ios::end); // Move to end of file
    size_t fileSize = in.tellg(); // Get file size
    in.seekg(0, std::ios::beg); // Move back to beginning of file

    // Determine chunk size for each thread
    size_t chunkSize = (fileSize + numThreads - 1) / numThreads; // Ensure last chunk gets correct size
    std::vector<std::vector<char>> compressedChunks(numThreads); // Store compressed chunks
    std::vector<std::thread> threads; // Vector to store threads

    // Launch threads to compress file in chunks
    for (size_t i = 0; i < numThreads; ++i) {
        std::vector<char> buffer(chunkSize); // Buffer to hold file data
        in.read(buffer.data(), chunkSize); // Read data into buffer
        size_t bytesRead = in.gcount(); // Get actual number of bytes read

        buffer.resize(bytesRead); // Resize buffer to actual read size
        threads.emplace_back(compressChunk, std::cref(buffer), std::ref(compressedChunks[i])); // Start thread for compression
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    // Write compressed chunks to output file
    for (const auto& chunk : compressedChunks) {
        out.write(chunk.data(), chunk.size());
    }
    
    std::cout << "Compression complete.\n"; // Indicate compression is done
}

int main() {
    std::string inputFile = "input.txt"; // Input file name
    std::string outputFile = "compressed.bin"; // Output file name
    size_t numThreads = std::min(std::thread::hardware_concurrency(), 4u); // Use up to 4 threads for efficiency
    
    compressFileMultithreaded(inputFile, outputFile, numThreads); // Start compression
    return 0; // Exit program
}