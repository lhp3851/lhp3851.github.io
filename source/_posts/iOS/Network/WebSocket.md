---
title: 网络协议之 WebSocket
abbrlink: 1cd3002f
date: 2021-04-20 21:36:02
tags:
---

## 1. [Websocket](https://datatracker.ietf.org/doc/html/rfc6455)

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

|       字段       |                                                                                                                                                                                                                                                                                                                                                                                                     含义                                                                                                                                                                                                                                                                                                                                                                                                      |
| :--------------: | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|       FIN        |                                                                                                                                                                                                                                                                                                                                                  Indicates that this is the final fragment in a message.  The first fragment MAY also be the final fragment.                                                                                                                                                                                                                                                                                                                                                  |
| RSV1, RSV2, RSV3 |                                                                                                                                                                                                                                                                    MUST be 0 unless an extension is negotiated that defines meanings for non-zero values.  If a nonzero value is received and none of the negotiated extensions defines the meaning of such a nonzero value, the receiving endpoint MUST _Fail the WebSocket Connection_.                                                                                                                                                                                                                                                                     |
|      Opcode      |                                                                                                                                                                                                                                                                                                             Defines the interpretation of the "Payload data".  If an unknown opcode is received, the receiving endpoint MUST _Fail the WebSocket Connection_.  The following values are defined.                                                                                                                                                                                                                                                                                                              |
|       Mask       |                                                                                                                                                                                                                                                                                     Defines whether the "Payload data" is masked.  If set to 1, a masking key is present in masking-key, and this is used to unmask the "Payload data" as per Section 5.3.  All frames sent from client to server have this bit set to 1.                                                                                                                                                                                                                                                                                     |
|  Payload length  | The length of the "Payload data", in bytes: if 0-125, that is the payload length.  If 126, the following 2 bytes interpreted as a 16-bit unsigned integer are the payload length.  If 127, the following 8 bytes interpreted as a 64-bit unsigned integer (the most significant bit MUST be 0) are the payload length.  Multibyte length quantities are expressed in network byte order.  Note that in all cases, the minimal number of bytes MUST be used to encode the length, for example, the length of a 124-byte-long string can't be encoded as the sequence 126, 0, 124.  The payload length is the length of the "Extension data" + the length of the "Application data".  The length of the "Extension data" may be zero, in which case the payload length is the length of the "Application data". |

## 2. [URLSessionWebSocketTask](https://developer.apple.com/documentation/foundation/urlsessionwebsockettask)

## 3. [An Introduction to WebSockets(Swift)](https://www.raywenderlich.com/13209594-an-introduction-to-websockets)

## 4. [WebSockets in iOS Using Swift](https://betterprogramming.pub/websockets-in-ios-using-swift-a176791e139f)

### 4.1 [Starscream(Swift)](https://github.com/daltoniam/Starscream)
