/*
 * COP 3515 – Spring Semester 2023
 *
 * Homework #4: Securing The Message
 *
Coby Flannery

*/
use std::fs::File;
use std::io::{prelude::*};
use rand::{Rng, thread_rng};
use std::str::FromStr;

fn generate() {
    // Step 1: Generate two unique prime numbers
    let p = generate_prime();
    let q = generate_prime();
    println!("p = {}", p);
    println!("q = {}", q);

    // Step 2: Calculate n = p * q
    let n = p * q;
    println!("n = {}", n);

    // Step 3: Calculate the totient t = (p - 1) * (q - 1)
    let t = (p - 1) * (q - 1);
    println!("t = {}", t);

    // Step 4: Choose an integer e such that 1 < e < t and e and t have no common integer factors other than 1
    let e = generate_e(t);
    println!("e = {}", e);

    // Step 5: Compute d such that d * e ≡ 1 mod t
    let d = generate_d(e, t);
    println!("d = {}", d);

    // Create pub.key file containing the public key (e, n)
    let mut pub_file = File::create("pub.key").unwrap();
    let pub_key = format!("{} {}", e, n);
    pub_file.write_all(pub_key.as_bytes()).unwrap();

    // Create priv.key file containing the private key (d, n)
    let mut priv_file = File::create("priv.key").unwrap();
    let priv_key = format!("{} {}", d, n);
    priv_file.write_all(priv_key.as_bytes()).unwrap();
}

//Generates a random prime number between 2 and 99
fn generate_prime() -> u64 {
    let mut rng = thread_rng();
    loop {
        let n: u64 = rng.gen_range(2..100);
        if is_prime(n) {
            return n;
        }
    }
}

// Determines whether a given number is prime or not
fn is_prime(n: u64) -> bool {
    if n <= 1 {
        return false;
    }
    for i in 2..=n / 2 {
        if n % i == 0 {
            return false;
        }
    }
    true
}

// Generates a random number between 2 and t-1
fn generate_e(t: u64) -> u64 {
    let mut rng = thread_rng();
    loop {
        let e: u64 = rng.gen_range(2..t);
        if gcd(e, t) == 1 {
            return e;
        }
    }
}

// Generates a number d such that (d * e) % t = 1,
fn generate_d(e: u64, t: u64) -> u64 {
    let mut d: u64 = 1;
    while (d * e) % t != 1 {
        d += 1;
    }
    d
}

//Finds the gcd
fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        return a;
    }
    gcd(b, a % b)
}

fn encrypt(message: &str) -> String {
    // Print the ASCII decimal equivalent of the message
    println!("\nOriginal plain text message in ASCII decimal form:");
    for c in message.chars() {
        let m = c as u64;
        print!("{} ", m);
    }
    println!();

    // Read the public key from the file
    let mut pub_file = File::open("pub.key").unwrap();
    let mut pub_key = String::new();
    pub_file.read_to_string(&mut pub_key).unwrap();
    let pub_parts: Vec<&str> = pub_key.trim().split(" ").collect();
    let e = u64::from_str(pub_parts[0]).unwrap();
    let n = u64::from_str(pub_parts[1]).unwrap();

    // Encrypt the message using the public key
    let mut ciphertext = String::new();
    for c in message.chars() {
        let m = c as u64;
        let mut x = m;

        for _ in 1..=e-1 {
            x = (x * m) % n;
        }

        let c = x.to_string();
        ciphertext += &c;
        ciphertext += " ";
    }

    ciphertext.trim().to_string()
}

fn decrypt(ciphertext: &str) -> String {
    // Read the private key from the file
    let mut priv_file = File::open("priv.key").unwrap();
    let mut priv_key = String::new();
    priv_file.read_to_string(&mut priv_key).unwrap();
    let priv_parts: Vec<&str> = priv_key.trim().split(" ").collect();
    let d = u64::from_str(priv_parts[0]).unwrap();
    let n = u64::from_str(priv_parts[1]).unwrap();

    // Decrypt the message using the private key
    let mut plaintext = String::new();
    let ciphers: Vec<&str> = ciphertext.trim().split(" ").collect();
    for c in ciphers {
        let c = u64::from_str(c).unwrap();
        let mut x = c;

        for _ in 1..=d-1 {
            x = (x * c) % n;
        }

        let m = x as u8 as char;
        plaintext.push(m);
    }

    plaintext
}

fn main() {
  generate();
  
  let message = "The greatest discovery of all time is that a person can change his future by merely changing his attitude";
  println!("\nOriginal Message: \n{ }", message); //Printing original message
  
  let ciphertext = encrypt(message); //Encryption
    println!("\nCiphertext: \n{}", ciphertext); //Printing ciphertext
  
  let decrypted_message = decrypt(&ciphertext); //Decryption
    println!("\nDecrypted message: \n{}", decrypted_message); //printing relayed message
    
}
