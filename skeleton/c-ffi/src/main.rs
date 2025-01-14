/// Helper method to generate a NTS (null-terminated string) from a Rust string.
fn nts<const N: usize>(array: &[u8]) -> [i8; N] {
    let mut result = [0i8; N];
    for i in 0..array.len() {
        result[i] = array[i] as i8;
    }
    result
}


fn main() {
    println!("Hello, world!");

}
