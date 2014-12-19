
#![no_std]
#![feature(intrinsics, lang_items)]

extern crate libc;
extern "rust-intrinsic" { fn transmute<T, U>(t: T) -> U; }

extern {
    pub fn _kprintf(fmt: *const u8);
}

#[no_mangle]
#[no_stack_check]
pub unsafe fn _user_func() {
    let (ptr, _): (*const u8, uint) = transmute("Rust in user mode!\n");
    _kprintf(ptr);
}
