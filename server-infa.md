```
                    [ main ]
                     /    \
        [ Bot Server ]     [Telegram Server]
         /     |    \                  \
  [ Multithread for client] <------->  {Global Struct} - selected_id
        /                       |                      - command
       /          .each bot loop check selected id.    - Output
      /
{sock_thread_struct}
    - new_sock
    - ip
```
