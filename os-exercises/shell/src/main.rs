use std::io::{self, Write};
use std::process::Command;

fn main() {
    let stdin = io::stdin();
    let mut buf = String::new();
    loop {
        print!("$ ");
        io::stdout().flush().unwrap();

        match stdin.read_line(&mut buf) {
            Ok(0) => break,
            Ok(_) => {
                let cmdline = parse_cmdline(&buf);
                run_command(cmdline);
                buf.clear();
            }
            Err(error) => {
                eprintln!("failed reading stdin: {error}");
                break;
            }
        }
    }
}

fn parse_cmdline(line: &str) -> Vec<&str> {
    line.split(" ").map(|arg| arg.trim()).collect::<Vec<&str>>()
}

fn run_command(cmdline: Vec<&str>) {
    if cmdline.is_empty() {
        return;
    }

    let (command, args) = cmdline.split_first().unwrap();
    match Command::new(command).args(args).status() {
        Ok(status) => {
            if !status.success() {
                println!("program {command} exited with {status}");
            }
        }
        Err(error) => eprintln!("could not get program {command} exit status: {error}"),
    }
}
