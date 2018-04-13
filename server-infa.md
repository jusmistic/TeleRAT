                    [ main ]
                      /   \
        [ Bot Server ]     [Telegram Server]
         /     |    \                  \
  [ Multithread for client] <------->  {Global Struct} - selected_id
        /                        |                     - command
       /          .each bot loop check selected id.
      /
{sock_thread_struct}
    - socket_desc
    - struct sockaddr client
    
