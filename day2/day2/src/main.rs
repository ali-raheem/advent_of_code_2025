use std::fs;
use std::io::{self, BufRead, BufReader, Write};
use std::time::Duration;
use clap::{Arg, Command};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let matches = Command::new("Advent of Code Day 2 Host")
        .about("Manages transmitting and receiving from Arduino")
        .disable_version_flag(true)
        .arg(
            Arg::new("port")
                .help("The device path to a serial port")
                .use_value_delimiter(false)
                .required(true),
        )
        .arg(
            Arg::new("input")
                .help("the file to send over")
                .use_value_delimiter(false)
                .required(true)
        )
        .get_matches();

    let ser_port = matches.get_one::<String>("port").unwrap();
    let input_file = matches.get_one::<String>("input").unwrap();

    let mut port = serialport::new(ser_port, 115200)
        .timeout(Duration::from_secs(30))
        .open()?;

    println!("Waiting for Arduino to boot...");
    std::thread::sleep(Duration::from_secs(2));

    port.write_all(b"R")?;
    port.flush()?;
    
    let mut reader = BufReader::new(port);
    

    let mut line = String::new();
    loop {
        line.clear();
        reader.read_line(&mut line)?;
        println!("{}", line.trim());
        if line.trim() == "RESET" {
            println!("Arduino reset successfully");
            break;
        }
    }

    let content = fs::read_to_string(input_file)?;
    let ranges: Vec<&str> = content
        .split(',')
        .map(|s| s.trim())
        .filter(|s| !s.is_empty())
        .collect();

    let total = ranges.len();
    let mut password: u128 = 0;

    for (i, range) in ranges.iter().enumerate() {

        let msg = format!("{},", range);
        reader.get_mut().write_all(msg.as_bytes())?;
        reader.get_mut().flush()?;
        println!("Sent [{}/{}]: {}", i + 1, total, range);

        loop {
            line.clear();
            match reader.read_line(&mut line) {
                Ok(0) => {
                    eprintln!("  Timeout waiting for response!");
                    break;
                }
                Ok(_) => {
                    let response = line.trim();
                    if response.is_empty() {
                        continue;
                    }

                    if response.starts_with("M:") {
                        if let Ok(match_val) = response[2..].parse::<u128>() {
                            password += match_val;
                            println!("  Match: {}, Running total: {}", match_val, password);
                        }
                    } else if response == "DONE" {
                        println!("  Range complete. Total: {}", password);
                        break;
                    } else {
                        println!("  {}", response);
                    }
                }
                Err(e) => {
                    eprintln!("  Error reading: {:?}", e);
                    break;
                }
            }
        }
    }

    println!("\nRelease serial port");
    println!("Final answer: {}", password);

    Ok(())
}
