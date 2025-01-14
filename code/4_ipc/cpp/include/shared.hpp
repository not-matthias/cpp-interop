#pragma once

#include "serde.hpp"
#include "bincode.hpp"

namespace ipc {

    struct Genre {

        struct Action {
            friend bool operator==(const Action&, const Action&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Action bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Comedy {
            friend bool operator==(const Comedy&, const Comedy&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Comedy bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Drama {
            friend bool operator==(const Drama&, const Drama&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Drama bincodeDeserialize(std::vector<uint8_t>);
        };

        std::variant<Action, Comedy, Drama> value;

        friend bool operator==(const Genre&, const Genre&);
        std::vector<uint8_t> bincodeSerialize() const;
        static Genre bincodeDeserialize(std::vector<uint8_t>);
    };

    struct Movie {
        std::string title;
        uint16_t year;
        float rating;
        ipc::Genre genre;

        friend bool operator==(const Movie&, const Movie&);
        std::vector<uint8_t> bincodeSerialize() const;
        static Movie bincodeDeserialize(std::vector<uint8_t>);
    };

    struct Action {

        struct Add {
            ipc::Movie value;

            friend bool operator==(const Add&, const Add&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Add bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Get {
            std::string value;

            friend bool operator==(const Get&, const Get&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Get bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Remove {
            std::string value;

            friend bool operator==(const Remove&, const Remove&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Remove bincodeDeserialize(std::vector<uint8_t>);
        };

        std::variant<Add, Get, Remove> value;

        friend bool operator==(const Action&, const Action&);
        std::vector<uint8_t> bincodeSerialize() const;
        static Action bincodeDeserialize(std::vector<uint8_t>);
    };

    struct ActionResponse {

        struct Data {
            ipc::Movie value;

            friend bool operator==(const Data&, const Data&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Data bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Ok {
            friend bool operator==(const Ok&, const Ok&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Ok bincodeDeserialize(std::vector<uint8_t>);
        };

        struct Error {
            friend bool operator==(const Error&, const Error&);
            std::vector<uint8_t> bincodeSerialize() const;
            static Error bincodeDeserialize(std::vector<uint8_t>);
        };

        std::variant<Data, Ok, Error> value;

        friend bool operator==(const ActionResponse&, const ActionResponse&);
        std::vector<uint8_t> bincodeSerialize() const;
        static ActionResponse bincodeDeserialize(std::vector<uint8_t>);
    };

} // end of namespace ipc


namespace ipc {

    inline bool operator==(const Action &lhs, const Action &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Action::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Action>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Action Action::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Action>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Action>::serialize(const ipc::Action &obj, Serializer &serializer) {
    serializer.increase_container_depth();
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
    serializer.decrease_container_depth();
}

template <>
template <typename Deserializer>
ipc::Action serde::Deserializable<ipc::Action>::deserialize(Deserializer &deserializer) {
    deserializer.increase_container_depth();
    ipc::Action obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    deserializer.decrease_container_depth();
    return obj;
}

namespace ipc {

    inline bool operator==(const Action::Add &lhs, const Action::Add &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Action::Add::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Action::Add>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Action::Add Action::Add::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Action::Add>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Action::Add>::serialize(const ipc::Action::Add &obj, Serializer &serializer) {
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ipc::Action::Add serde::Deserializable<ipc::Action::Add>::deserialize(Deserializer &deserializer) {
    ipc::Action::Add obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}

namespace ipc {

    inline bool operator==(const Action::Get &lhs, const Action::Get &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Action::Get::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Action::Get>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Action::Get Action::Get::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Action::Get>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Action::Get>::serialize(const ipc::Action::Get &obj, Serializer &serializer) {
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ipc::Action::Get serde::Deserializable<ipc::Action::Get>::deserialize(Deserializer &deserializer) {
    ipc::Action::Get obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}

namespace ipc {

    inline bool operator==(const Action::Remove &lhs, const Action::Remove &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Action::Remove::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Action::Remove>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Action::Remove Action::Remove::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Action::Remove>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Action::Remove>::serialize(const ipc::Action::Remove &obj, Serializer &serializer) {
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ipc::Action::Remove serde::Deserializable<ipc::Action::Remove>::deserialize(Deserializer &deserializer) {
    ipc::Action::Remove obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}

namespace ipc {

    inline bool operator==(const ActionResponse &lhs, const ActionResponse &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> ActionResponse::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<ActionResponse>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline ActionResponse ActionResponse::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<ActionResponse>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::ActionResponse>::serialize(const ipc::ActionResponse &obj, Serializer &serializer) {
    serializer.increase_container_depth();
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
    serializer.decrease_container_depth();
}

template <>
template <typename Deserializer>
ipc::ActionResponse serde::Deserializable<ipc::ActionResponse>::deserialize(Deserializer &deserializer) {
    deserializer.increase_container_depth();
    ipc::ActionResponse obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    deserializer.decrease_container_depth();
    return obj;
}

namespace ipc {

    inline bool operator==(const ActionResponse::Data &lhs, const ActionResponse::Data &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> ActionResponse::Data::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<ActionResponse::Data>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline ActionResponse::Data ActionResponse::Data::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<ActionResponse::Data>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::ActionResponse::Data>::serialize(const ipc::ActionResponse::Data &obj, Serializer &serializer) {
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ipc::ActionResponse::Data serde::Deserializable<ipc::ActionResponse::Data>::deserialize(Deserializer &deserializer) {
    ipc::ActionResponse::Data obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}

namespace ipc {

    inline bool operator==(const ActionResponse::Ok &lhs, const ActionResponse::Ok &rhs) {
        return true;
    }

    inline std::vector<uint8_t> ActionResponse::Ok::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<ActionResponse::Ok>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline ActionResponse::Ok ActionResponse::Ok::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<ActionResponse::Ok>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::ActionResponse::Ok>::serialize(const ipc::ActionResponse::Ok &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
ipc::ActionResponse::Ok serde::Deserializable<ipc::ActionResponse::Ok>::deserialize(Deserializer &deserializer) {
    ipc::ActionResponse::Ok obj;
    return obj;
}

namespace ipc {

    inline bool operator==(const ActionResponse::Error &lhs, const ActionResponse::Error &rhs) {
        return true;
    }

    inline std::vector<uint8_t> ActionResponse::Error::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<ActionResponse::Error>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline ActionResponse::Error ActionResponse::Error::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<ActionResponse::Error>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::ActionResponse::Error>::serialize(const ipc::ActionResponse::Error &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
ipc::ActionResponse::Error serde::Deserializable<ipc::ActionResponse::Error>::deserialize(Deserializer &deserializer) {
    ipc::ActionResponse::Error obj;
    return obj;
}

namespace ipc {

    inline bool operator==(const Genre &lhs, const Genre &rhs) {
        if (!(lhs.value == rhs.value)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Genre::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Genre>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Genre Genre::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Genre>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Genre>::serialize(const ipc::Genre &obj, Serializer &serializer) {
    serializer.increase_container_depth();
    serde::Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
    serializer.decrease_container_depth();
}

template <>
template <typename Deserializer>
ipc::Genre serde::Deserializable<ipc::Genre>::deserialize(Deserializer &deserializer) {
    deserializer.increase_container_depth();
    ipc::Genre obj;
    obj.value = serde::Deserializable<decltype(obj.value)>::deserialize(deserializer);
    deserializer.decrease_container_depth();
    return obj;
}

namespace ipc {

    inline bool operator==(const Genre::Action &lhs, const Genre::Action &rhs) {
        return true;
    }

    inline std::vector<uint8_t> Genre::Action::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Genre::Action>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Genre::Action Genre::Action::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Genre::Action>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Genre::Action>::serialize(const ipc::Genre::Action &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
ipc::Genre::Action serde::Deserializable<ipc::Genre::Action>::deserialize(Deserializer &deserializer) {
    ipc::Genre::Action obj;
    return obj;
}

namespace ipc {

    inline bool operator==(const Genre::Comedy &lhs, const Genre::Comedy &rhs) {
        return true;
    }

    inline std::vector<uint8_t> Genre::Comedy::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Genre::Comedy>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Genre::Comedy Genre::Comedy::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Genre::Comedy>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Genre::Comedy>::serialize(const ipc::Genre::Comedy &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
ipc::Genre::Comedy serde::Deserializable<ipc::Genre::Comedy>::deserialize(Deserializer &deserializer) {
    ipc::Genre::Comedy obj;
    return obj;
}

namespace ipc {

    inline bool operator==(const Genre::Drama &lhs, const Genre::Drama &rhs) {
        return true;
    }

    inline std::vector<uint8_t> Genre::Drama::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Genre::Drama>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Genre::Drama Genre::Drama::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Genre::Drama>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Genre::Drama>::serialize(const ipc::Genre::Drama &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
ipc::Genre::Drama serde::Deserializable<ipc::Genre::Drama>::deserialize(Deserializer &deserializer) {
    ipc::Genre::Drama obj;
    return obj;
}

namespace ipc {

    inline bool operator==(const Movie &lhs, const Movie &rhs) {
        if (!(lhs.title == rhs.title)) { return false; }
        if (!(lhs.year == rhs.year)) { return false; }
        if (!(lhs.rating == rhs.rating)) { return false; }
        if (!(lhs.genre == rhs.genre)) { return false; }
        return true;
    }

    inline std::vector<uint8_t> Movie::bincodeSerialize() const {
        auto serializer = serde::BincodeSerializer();
        serde::Serializable<Movie>::serialize(*this, serializer);
        return std::move(serializer).bytes();
    }

    inline Movie Movie::bincodeDeserialize(std::vector<uint8_t> input) {
        auto deserializer = serde::BincodeDeserializer(input);
        auto value = serde::Deserializable<Movie>::deserialize(deserializer);
        if (deserializer.get_buffer_offset() < input.size()) {
            throw serde::deserialization_error("Some input bytes were not read");
        }
        return value;
    }

} // end of namespace ipc

template <>
template <typename Serializer>
void serde::Serializable<ipc::Movie>::serialize(const ipc::Movie &obj, Serializer &serializer) {
    serializer.increase_container_depth();
    serde::Serializable<decltype(obj.title)>::serialize(obj.title, serializer);
    serde::Serializable<decltype(obj.year)>::serialize(obj.year, serializer);
    serde::Serializable<decltype(obj.rating)>::serialize(obj.rating, serializer);
    serde::Serializable<decltype(obj.genre)>::serialize(obj.genre, serializer);
    serializer.decrease_container_depth();
}

template <>
template <typename Deserializer>
ipc::Movie serde::Deserializable<ipc::Movie>::deserialize(Deserializer &deserializer) {
    deserializer.increase_container_depth();
    ipc::Movie obj;
    obj.title = serde::Deserializable<decltype(obj.title)>::deserialize(deserializer);
    obj.year = serde::Deserializable<decltype(obj.year)>::deserialize(deserializer);
    obj.rating = serde::Deserializable<decltype(obj.rating)>::deserialize(deserializer);
    obj.genre = serde::Deserializable<decltype(obj.genre)>::deserialize(deserializer);
    deserializer.decrease_container_depth();
    return obj;
}
