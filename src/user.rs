
#![no_std]
#![feature(intrinsics, lang_items)]

extern crate libc;
extern "rust-intrinsic" { fn transmute<T, U>(t: T) -> U; }

extern {
    pub fn kprintf(fmt: *const u8, ...);
}

#[no_mangle]
#[no_stack_check]
pub unsafe fn rust_user_func() {
    let (ptr1, _): (*const u8, uint) = transmute("Rust in user mode!\n");
    kprintf(ptr1);
    let (ptr2, _): (*const u8, uint) = transmute("Another rust kprintf call!\n");
    kprintf(ptr2);
    while(true) {}
}
