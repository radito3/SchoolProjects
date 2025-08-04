use std::cmp;
use std::collections::VecDeque;
use std::env;
use std::fs;
use std::io::{self, BufRead, Read, Seek};

fn main() {
    let args: Vec<String> = env::args().collect();

    match &args[..] {
        [_] => read_stdin(),
        [_, file] => read_file_wrapper(file),
        [_, files @ ..] => read_files(files),
        _ => eprintln!("empty os.args!"),
    }
}

fn read_stdin() {
    let mut lines: VecDeque<String> = VecDeque::new();

    io::stdin().lines().map_while(Result::ok).for_each(|line| {
        lines.push_back(line.to_string());
        if lines.len() > 10 {
            lines.pop_front();
        }
    });

    println!();
    lines.iter().for_each(|line| println!("{line}"));
}

fn read_file_wrapper(name: &str) {
    if let Err(err) = read_file(name) {
        eprintln!("tail: error for '{name}': {err}");
    }
}

fn read_file(name: &str) -> io::Result<()> {
    let mut file = fs::File::open(name)?;
    let size = file.metadata()?.len();
    let chunk_size = cmp::min(512, size);
    let mut total_offset = 0;
    let mut lines = 0;

    while lines < 10 && total_offset < size {
        file.seek(io::SeekFrom::End(-((chunk_size + total_offset) as i64)))?;
        let mut buffer = vec![0u8; chunk_size as usize];
        file.read_exact(&mut buffer)?;

        for byte in buffer.iter().rev() {
            if *byte == b'\n' {
                lines += 1;
                if lines > 10 {
                    break;
                }
            }
            total_offset += 1;
        }
    }

    file.seek(io::SeekFrom::End(-(total_offset as i64)))?;
    let reader = io::BufReader::new(file);
    reader
        .lines()
        .map_while(Result::ok)
        .for_each(|line| println!("{line}"));

    Ok(())
}

fn read_files(files: &[String]) {
    for file in files.iter() {
        if file == "-" {
            println!("==> stdin <==");
            read_stdin();
        } else {
            println!("==> {file} <==");
            read_file_wrapper(file);
        }
    }
}
