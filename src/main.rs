extern crate clap; 
use clap::App; 
 
fn main() { 
    App::new("jak")
       .version("0.1")
       .about("Development workspace management")
       .author("Graham Brooks")
       .get_matches(); 
}

