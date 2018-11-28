#![deny(warnings)]

extern crate clap;
extern crate reqwest;
#[macro_use]
extern crate serde_derive;

use clap::App;

#[derive(Deserialize, Debug)]
struct User {
    login: String,
    id: u32,
}

fn get_users(owner: &str, repo: &str) -> Vec<User> {
    let request_url = format!("https://api.github.com/repos/{owner}/{repo}/stargazers",
                              owner = owner,
                              repo = repo);
    println!("{}", request_url);
    let mut res = reqwest::get("https://www.rust-lang.org/en-US/");

    let users : Vec<User>= res.json()?;
    return users;
}

//fn run() -> Rresult<(), Box<std::error::Error>> {
//    let request_url = format!("https://api.github.com/repos/{owner}/{repo}/stargazers",
//                              owner = "rust-lang-nursery",
//                              repo = "rust-cookbook");
//    println!("{}", request_url);
//    let mut response = reqwest::get(&request_url)?;
//
//    let users: Vec<User> = response.json()?;
//    println!("{:?}", users);
//    Ok(())
//}

fn main() {
    App::new("jak")
        .version("0.1")
        .about("Development workspace management")
        .get_matches();

    let users: Vec<User> = get_users("rust-lang-nursery", "rust-cookbook");
    println!("{:?}", users);
}

