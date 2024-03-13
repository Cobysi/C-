/*
 * COP 3515 – Spring Semester 2023
 *
 * Homework #3: Fixing The Problem
 *
 * Coby Flannery
 */

// Importing necessary modules from standard library
use std::fs::File;
use std::io::{BufRead, BufReader};

// Main function
fn main() {
    
    // Open and read file
    let file = File::open("Homework #3 - Encoding Text.txt").expect("Unable to open file");
    let reader = BufReader::new(file);
    let mut _contents = String::new();

    // Initialize variables
    let mut encoded_chars: Vec<String> = Vec::new();
    let mut encoded_binaries: Vec<String> = Vec::new(); // new vector for binary strings
    let mut encoded_val: u32 = 0;
      
    // Loop through each line of the file
    for line in reader.lines() {
        let line = line.expect("Unable to read line");
        let input = line;
        println!("");
        println!("Processing: {}", input);
      
        // Loop through each character in the line
        for c in input.chars() {
            // Convert character to its corresponding ASCII value
            let ascii_val = c as u32;
            let mut bits: Vec<u32> = Vec::new();

            // Convert ASCII value to a vector of its binary representation
            for i in 0..7 {
                bits.push((ascii_val >> i) & 1);
            }

            // Calculate Hamming code parity bits
            let p1 = bits[0] ^ bits[1] ^ bits[3] ^ bits[4] ^ bits[6];
            let p2 = bits[0] ^ bits[2] ^ bits[3] ^ bits[5] ^ bits[6];
            let p4 = bits[1] ^ bits[2] ^ bits[3];
            let p8 = bits[4] ^ bits[5] ^ bits[6];

            // Insert parity bits to their respective positions in the bits vector
            bits.insert(0, p1);
            bits.insert(1, p2);
            bits.insert(3, p4);
            bits.insert(7, p8);

            // Convert the Hamming code to its decimal representation
            for i in 0..bits.len() {
                encoded_val += bits[i] * 2u32.pow(i as u32);
            }

            // Add the decimal representation and its corresponding binary representation to their respective vectors
            encoded_chars.push(encoded_val.to_string());
            let binary_str = format!("{:016b}", encoded_val); // convert to binary string with leading zeros
            encoded_binaries.push(binary_str); // append to binary vector
            println!("Character = {}, token = {}", c, encoded_val);
        }

        // Print the Hamming code
        println!();
        print!("Hamming Code:");
        for (i, val) in encoded_chars.iter().enumerate() {
            println!("");   
            if i % 6 == 0 {
                println!();
            }
            print!("{:4} {:016} ", val, encoded_binaries[i]);
        }
        println!();
    }

    //decoding
    println!();
    println!("==> Starting the decoding process:");
    // TODO: Implement decoding process
    
    println!();
}


