# TeleRAT
```
    
     .--,       .--,     
    ( (  \.---./  ) )         _   _   _   _   _   _   _  
     '.__/o   o\__.'         / \ / \ / \ / \ / \ / \ / \ 
        {=  ^  =}           ( T | e | l | e | R | A | T )
         >  -  <             \_/ \_/ \_/ \_/ \_/ \_/ \_/          
        /       \
       //       \\
      //|   .   |\\
      "'\       /'"_.-~^`'-.
         \  _  /--'         `
       ___)( )(___
      (((__) (__)))    
```
## What is TeleRAT
TeleRAT เป็นโปรแกรมสนับสนุนการทำงานระยะไกลของระบบปฎิบัติการ Ubuntu(Linux debian base) ซึ่งนำโปรแกรมแกรม Telegram มาใช้เป็นตัวกลางในการควบคุม shell ของเครื่อง client แต่ละตัวผ่านการแชท
<p align="center">
<img align="center" src="https://media.giphy.com/media/hTDO28e3i3Di3H2Y8f/giphy.gif" alt="how TeleRAT work.">
</p>

## Installation
การติดตั้ง TeleRAT มีวิธีง่ายๆ ดังนี้
1. ทำการ clone จาก Github Repository
```
git clone https://github.com/jusmistic/TeleRAT.git
```

2. ทำการติดตั้ง Library ที่จำเป็นโดย 
```
cd TeleRAT && chmod a+x install.sh && sudo ./install.sh
```

3. ทำการ MAKE FILE
```
make all
```
4. ทำการเปิด Server โดย
```
./server-d <PORT>
```
และนำ client-d ไปติดตั้งที่เครื่อง Client และรันโดย
```
sudo ./client-d <IP> <PORT> -init
```

# How TeleRAT Work
```
             _____________                       _______________                       _______________
            | BOT(Client) | ==================> |     Server    | ==================> |   Telegram    |
            |   Ubuntu    |                     | Ubuntu On AWS |                     |    Message    | 
            |_____________|                     |_______________|                     |_______________|
                   ╚===========================================================================╝
            
            Bot communicate with Server        handle with command that recieve from
            via Socket server                  Telegram massege 
                                               Waiting for connection from BOT
                                               then send the command to execute

```

# Telegram Commands
```
 _________
< TeleRAT >
 ---------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||

/help - List of commands.
/list - Show all avaliable clients
/select - Select the client by id
/shell - Exec shell commands with timeout
/cp - Copy file/folder
/mv - Move file/folder
/rm - Remove file/folder
/mkdir - Make directory
/getfile - Download file from bot
/boom - DESTROY ITSELF!
```

# Setting up self-signed certificates

for connecting to Telegram API. You need to generate `public key` and `private key` for use HTTPS connection for POST request and setup webhook. use `openssl` command to generate the key in PEM encoded

```
openssl req -newkey rsa:2048 -sha256 -nodes -keyout private.pem -x509 -days 365 -out public.pem
```
