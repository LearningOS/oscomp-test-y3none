use convert_case::{Case, Casing};
use std::rc::Rc;
use std::sync::Arc;

// use std::ffi::{OsString};

#[test]
fn string_type() {
    let s: String = String::from("rust_programming_language");
    assert_eq!("RustProgrammingLanguage", s.to_case(Case::Pascal),);
}

#[test]
fn str_type() {
    let s: &str = "rust_programming_language";
    assert_eq!("RustProgrammingLanguage", s.to_case(Case::Pascal),);
}

#[test]
fn string_ref_type() {
    let s: String = String::from("rust_programming_language");
    assert_eq!("RustProgrammingLanguage", (&s).to_case(Case::Pascal),);
}

#[test]
fn rc_str_type() {
    let s: Rc<str> = Rc::from("rust_programming_language");
    assert_eq!("RustProgrammingLanguage", s.to_case(Case::Pascal),);
}

#[test]
fn arc_str_type() {
    let s: Arc<str> = Arc::from("rust_programming_language");
    assert_eq!("RustProgrammingLanguage", s.to_case(Case::Pascal),);
}

/*
#[test]
fn os_string_type() {
    let s: OsString = OsString::from("rust_programming_language");
    assert_eq!(
        "RustProgrammingLanguage",
        s.to_case(Case::Pascal),
    );
}
*/
