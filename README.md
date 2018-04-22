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
TeleRAT เป็นโปรแกรมสนับสนุนการทำงานระยะไกลของระบบปฎิบัติการ Ubuntu (or Linux debian base) ซึ่งนำโปรแกรมแกรม Telegram มาใช้เป็นตัวกลางในการควบคุม shell ของเครื่อง client แต่ละตัวผ่านการแชท
<p align="center">
<img align="center" src="https://media.giphy.com/media/hTDO28e3i3Di3H2Y8f/giphy.gif" alt="how TeleRAT work.">
</p>

## Telegram Commands

### Commands list
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
/select <id> - Select the client by id
/shell  <shell-cmd> - Exec shell commands with timeout
/cp [-Option] <Source> <Destination> - Copy file/folder
/mv [-Option] <Source> <Destination> - Move file/folder
/rm [-Option] <Source> - Remove file/folder
/mkdir [-Option] <Folder destination> - Make directory
/getfile <File Path> - Download file from bot
/boom - DESTROY ITSELF!
```
### Commands manual
* **help** <br>
   แสดงว่ามีคอมมานอะไรบ้าง<br>
   **Command** <br>
   ```
   /help 
   ```
* **list** <br>
    แสดงว่ามี Client ตัวไหนกำลังออนไลน์อยู่ <br>
    **Command** <br>
    ```
    /list
    ```
* **select** <br>
    เลือก Client ที่ต้องการใช้งาน <br>
    **Command** <br>
    ```
    /select <id>
    ```
    **Argument** <br>
    * id - ID ของ client ที่ต้องการใช้งาน
* **shell** <br>
    ใช้เพื่อ execute command ที่ต้องการ <br>
    **Command** <br>
    ```
    /shell <shell-cmd>
    ```
    **Argument** <br>
    * shell-cmd - Linux Command ที่เราต้องการ execute
* **cp** <br>
    ใช้คัดลอกไฟล์หรือโฟลเดอร์โดยมีรูปแบบเหมือน Unix command <br>
    **Command**<br>
    ```
    /cp [-Option] <Source> <Destination>
    ```
    **Argument**<br>
    * Option - Option การคัดลอกไฟล์โดยมีรูปแบบเหมือน Unix
    * Source - ไฟล์หรือโฟลเดอร์ต้นฉบับ
    * Destination - ไฟล์หรือโฟลเดอร์ปลายทาง
* **mv**
    ใช้ย้ายไฟล์หรือโฟลเดอร์โดยมีรูปแบบเหมือน Unix command <br>
    **Command**<br>
    ```
    /mv [-Option] <Source> <Destination>
    ```
    **Argument**<br>
    * Option - Option การย้ายไฟล์โดยมีรูปแบบเหมือน Unix
    * Source - ไฟล์หรือโฟลเดอร์ต้นฉบับ
    * Destination - ไฟล์หรือโฟลเดอร์ปลายทาง
* **rm**
    ใช้ลบไฟล์หรือโฟลเดอร์โดยมีรูปแบบเหมือน Unix command <br>
    **Command**<br>
    ```
    /rm [-Option] <Source>
    ```
    **Argument**<br>
    * Option - Option การลบไฟล์โดยมีรูปแบบเหมือน Unix
    * Source - ไฟล์หรือโฟลเดอร์ต้นฉบับ
* **mkdir**
    ใช้สร้างโฟลเดอร์โดยมีรูปแบบเหมือน Unix command <br>
    **Command**<br>
    ```
    /mkdir [-Option] <Source>
    ```
    **Argument**<br>
    * Option - Option การย้ายไฟล์โดยมีรูปแบบเหมือน Unix
    * Source - โฟลเดอร์ที่ต้องการสร้าง
* **getfile**
    ใช้ดาวน์โหลดไฟล์จาก Client ที่ต้องการ <br>
    **Command**<br>
    ```
    /getfile <File Path>
    ```
    **Argument**<br>
    * File Path - ตำแหน่งของไฟล์ที่ต้องการดาวน์โหลดจาก Client
* **boom**
    * ใช้เพื่อลบ TeleRAT บนเครื่อง Client
    ```
    /boom
    ```

## How TeleRAT Work
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

## Library
* [OpenSSL](https://www.openssl.org/)

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
3. แก้ไขไฟล์ Config โดยเข้าไปที่โฟล์เดอร์ Telegram แล้วแก้ชื่อไฟล์ `config.example.h` เป็น `config.h` จากนั้นตรง `TELEGRAM_TOKEN` แก้ค่าเป็น Token ของ Telegram Bot ที่สร้างจาก @BotFather ของ Telegram

4. ทำการ Complie โดยใช้ MAKE FILE
```
make all
```
5. ตั้งค่า Telegram Webhook
```
./set_webhook <https://yourdomainOr.IP>
```
6. ทำการเปิด Server โดยใช้คำสั่ง
```
./server-d <PORT>
```
ในการเปิด Server ครั้งต่อไป สามารถใช้คำสั่ง `./server-d <PORT>` ได้เลย
และนำไฟล์ client-d ไปติดตั้งที่เครื่อง Client และรันโดยใช้คำสั่ง
```
sudo ./client-d <IP> <PORT> -init
```

## Our Team
พงศธร กิตติวรปัญญา | พุฒิเมธ ธรรมแสง | ปริญ สิทธิกุล
-----------------|--------------|------------
![Phongsathron Kittiworapanya](/resource/fluke.jpg) | ![Puttimate Thumsank](/resource/gun.jpg) | ![Parin Sittigul](/resource/dump.jpg)
60070055 | 60070068 | 60070047

## Assistant Teachers
ผศ. ดร. กิติ์สุชาติ พสุภา | ผศ. ดร. ปานวิทย์ ธุวะนุติ
--------------------|----------------------
![ผศ. ดร. กิติ์สุชาติ พสุภา](/resource/AJOung.jpg) |![ผศ. ดร. ปานวิทย์ ธุวะนุติ](/resource/AJPanwit.jpg)
