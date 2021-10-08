---
title: 网络协议之 WebSocket
abbrlink: 1cd3002f
date: 2021-04-20 21:36:02
tags:
---

## Websocket

```oc
/* From RFC:
 +
 + 0                   1                   2                   3
 + 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 + +-+-+-+-+-------+-+-------------+-------------------------------+
 + |F|R|R|R| opcode|M| Payload len |    Extended payload length    |
 + |I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
 + |N|V|V|V|       |S|             |   (if payload len==126/127)   |
 + | |1|2|3|       |K|             |                               |
 + +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
 + |     Extended payload length continued, if payload len == 127  |
 + + - - - - - - - - - - - - - - - +-------------------------------+
 + |                               |Masking-key, if MASK set to 1  |
 + +-------------------------------+-------------------------------+
 + | Masking-key (continued)       |          Payload Data         |
 + +-------------------------------- - - - - - - - - - - - - - - - +
 + :                     Payload Data continued ...                :
 + + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
 + |                     Payload Data continued ...                |
 + +---------------------------------------------------------------+
 +
 */
```
