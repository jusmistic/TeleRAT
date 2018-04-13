# Telegram API Library
This is Telegram API Library. It require OPENSSL for connecting to Telegram API.
## Functions
* **int telegram_get_me(char \*destination)**
    use for get bot information.
    * destination : pass array of char and get bot information.
    this function return `1` for success and `0` or `-1` for failed.
    
* **int telegram_set_webhook(char \*url, char \*public_key)**
    use for setup Telegram webhook.
    **argument**
    * url : the url of Telegram server.
    * public_key : file path to public key.
    this function return `1` for success and `0` or `-1` for failed.

* **int telegram_send_msg(char \*chat_id, char \*text)**
    use for send message to Telegram.
    **argument**
    * chat_id : Unique identifier for the target chat.
    * text : message you want to send.
    this function return `1` for success and `0` or `1` for failed.

* **int telegram_send_act(char *chat_id, char *action)**
    use for send chat action like typing, uploading file.
    **argument**
    * chat_id : Unique identifier for the target chat.
    * action : Type of action to broadcast. Choose one, depending on what the user is about to receive: `typing` for text messages, `upload_photo` for photos, `record_video` or `upload_video` for videos, `record_audio` or `upload_audio` for audio files, `upload_document` for general files, `find_location` for location data, `record_video_note` or `upload_video_note` for video notes.
    this function return `1` for success and `0` or `1` for failed.

* **int telegram_send_file(char \*chat_id, char \*file_path)**
    use for send file to target chat.
    **argument**
    * chat_id : Unique identifier for the target chat.
    * file_path : The location of file you want to send.
    this function return `1` for success and `0` or `1` for failed.