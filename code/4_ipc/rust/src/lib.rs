use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, Copy, Clone)]
pub enum Genre {
    Action,
    Comedy,
    Drama,
}

// Manual definition for simplicity and ergonomics
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Movie {
    pub title: String,
    pub year: u16,
    pub rating: f32,
    pub genre: Genre,
}

impl Binary for Movie {}

#[repr(C)]
#[derive(Serialize, Deserialize, Debug)]
pub enum Action {
    Add(Movie),
    Get(String),
    Remove(String),
}

impl Binary for Action {}

#[repr(C)]
#[derive(Serialize, Deserialize, Debug)]
pub enum ActionResponse {
    Data(Movie),
    Ok,
    Error,
}

impl Binary for ActionResponse {}

// Helper trait to convert structs to bytes
pub trait Binary {
    fn to_bytes(&self) -> Vec<u8>
    where
        Self: Serialize,
    {
        bincode::serialize(self).unwrap()
    }

    fn from_bytes<'a>(bytes: &'a [u8]) -> Option<Self>
    where
        Self: Deserialize<'a>,
    {
        bincode::deserialize(bytes).ok()
    }
}
