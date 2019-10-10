# Using Raw Socket Send UDP

## 注意

在MacOS下有小bug，使用rawsocket发送的话IP首部的ip_len字段需要使用主机序填写，在代码中已经改正，否则会出现

> Invalid argument

如果在其他平台下使用需要注意并更正