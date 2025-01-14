#include "include/shared.hpp"
using Movie = ipc::Movie;

#include "db.hpp"
#include "socket.hpp"

// FIXME: Very unsafe, guard with mutex
MovieDatabase db = MovieDatabase();

ipc::ActionResponse handle_action(const ipc::Action &action)
{
    using Action = ipc::Action;
    using ActionResponse = ipc::ActionResponse;

    return std::visit(
        [&](auto &&arg) -> ipc::ActionResponse {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, Action::Add>)
            {
                db.add_movie(arg.value);
                return ActionResponse{.value = ActionResponse::Ok()};
            }
            else if constexpr (std::is_same_v<T, Action::Get>)
            {
                auto movie = db.get_movie(arg.value.c_str());
                if (movie)
                {
                    return ActionResponse{.value = ActionResponse::Data{.value = *movie}};
                }
                else
                {
                    return ActionResponse{.value = ActionResponse::Error()};
                }
            }
            else if constexpr (std::is_same_v<T, Action::Remove>)
            {
                if (db.remove_movie(arg.value.c_str()))
                {
                    return ActionResponse{.value = ActionResponse::Ok()};
                }
                else
                {
                    return ActionResponse{.value = ActionResponse::Error()};
                }
            }
        },
        action.value);
}

void handle_client(ClientSocket client)
{
    uint8_t buffer[1024] = {0};
    while (true)
    {
        auto bytes_received = client.recv_data(buffer, sizeof(buffer) - 1);
        std::cout << "Received " << bytes_received << " bytes\n";

        if (bytes_received <= 0)
        {
            std::cout << "Client disconnected.\n";
            break;
        }

        auto action = ipc::Action::bincodeDeserialize(std::vector<uint8_t>(buffer, buffer + bytes_received));
        auto response = handle_action(action);
        auto response_bytes = response.bincodeSerialize();

        client.send_data(response_bytes.data(), response_bytes.size());
    }
}

int main()
{
    auto server = SocketServer(7878);

    while (true)
    {
        std::optional<ClientSocket> client_socket = server.accept_connection();
        if (!client_socket)
        {
            std::cerr << "Failed to accept connection\n";
            continue;
        }

        std::thread(handle_client, std::move(*client_socket)).detach();
    }
}
