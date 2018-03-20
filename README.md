# TeleRAT
Project Computer Programing 
# How TeleRAT Work
```
 _____________                       _______________                       _______________
| BOT(Client) | ==================> |     Server    | ==================> |   Telegram    |
|   Ubuntu    |                     | Ubuntu On AWS |                     |    Message    | 
|_____________| <================== |_______________| <================== |_______________|

Bot communicate with Server        handle with command that recieve from
using Reverse TCP concept          Telegram massege 
with 1s refresh rate               Waiting for connection from BOT
                                   then send the command to execute


```

# Telegram Commands
```
/help - List of commands.
/shell - Exec shell commands with timeout.
/cp - Copy file/folder.
/mv - Move file/folder.
/rm - Remove file/folder.
/mkdir - Make directory.
/timeout - Set timeout for shell.
/mvbot - Move bot to custom location.
/getfile - Download file from bot.
/reserve - Warning text that found in shell.
/BOOM! - DESTROY ITSELF!
```
