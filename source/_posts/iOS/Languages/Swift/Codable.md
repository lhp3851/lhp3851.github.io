---
title: iOS编程语言之 swift Codable
abbrlink: 574d0134
date: 2021-07-23 16:46:02
tags:
---

## 1. [Codable = Decodable + Encodable](https://medium.com/doyeona/codable-decodable-encodable-feat-json-5643dc3d7766)

### 1.1 NSCoding

```Swift
func encode(with aCoder: NSCoder) {
  
}

required convenience init?(coder aDecoder: NSCoder) {
  self.init(title: "", rating: 0)
}
```

* Still best way of using in inherited classes

* Be aware of using it with NSObject

* Code redundancy

* Doesn’t support structs and enums

* Depends on Foundation

### 1.2 Codable

```Swift
import UIKit

struct Response: Codable {
    let resultCount: Int
    let tracks: [Track]
    
    enum CodingKeys: String, CodingKey {
        case resultCount
        case tracks = "results"
    }
}

struct Track: Codable {
    let title: String
    let artistName: String
    let thumbnailPath: String
    
    enum CodingKeys: String, CodingKey {
        case title = "trackName"
        case artistName
        case thumbnailPath = "artworkUrl100"
    }
}
func encodeData(){
    let trackObject = Response(resultCount: 3, tracks: [
        Track(title: "hello",
              artistName: "heeloo",
              thumbnailPath: "eed"),
        Track(title: "hello",
              artistName: "heeloo",
              thumbnailPath: "eed"),
        Track(title: "hello",
              artistName: "heeloo",
              thumbnailPath: "eed")
    ])
    let encodeData = try? JSONEncoder().encode(trackObject)
    print("EncodeData: \(encodeData)")
    decodeData(decodeData: encodeData!)
}
encodeData()

func decodeData(decodeData: Data) {
    //let resultString = String(data: decodeData, encoding: .utf8)
    //print("Data in String: \(resultString)")
    
    do {
        let decoder = JSONDecoder()
        let response = try decoder.decode(Response.self, from: decodeData)
        print("\(response)")
    } catch let error {
        print(error.localizedDescription)
    }
}
```

## 2. [Complete Guide to Codable — Encodable](https://medium.com/flawless-app-stories/complete-guide-to-codable-encodable-f15b408b8eaa)

### 2.1 设置 codingKey 策略

```Swift
struct PhotoFeed: Encodable {
    let feedKey: String
    let feedUrl: String
    let feedDate: Date?
    let location: Location
    
    struct Location: Encodable {
        var latitude: Double
        var longitude: Double
        
        enum CodingKeys: String, CodingKey {
            case latitude = "lat"
            case longitude = "long"
        }
    }
}

let photoFeed = PhotoFeed(feedKey: "12345", feedUrl: "https://dummy.url.com/thumbnails/16869828-e75babd8.jpg", feedDate: Date(), location: PhotoFeed.Location(latitude: 73.7432861, longitude: 18.6119477))
let encoder = JSONEncoder()
encoder.keyEncodingStrategy = .convertToSnakeCase
encoder.outputFormatting = .prettyPrinted

let data = try! encoder.encode(photoFeed)
print(String(data: data, encoding: .utf8)!)

Output:
{
  "feed_date" : 610808974.47951901,
  "feed_url" : "https:\/\/dummy.url.com\/thumbnails\/16869828-e75babd8.jpg",
  "feed_key" : "12345",
  "location" : {
    "lat" : 73.743286100000006,
    "long" : 18.611947700000002
  }
}
```

### 2.2 自定义 codingKey 策略

```Swift
struct PhotoFeed: Encodable {
    let feedKey: String
    let feedUrl: String
    let feedDate: Date?
}

// MARK:- PhotoCodingKeys
struct PhotoCodingKeys: CodingKey {
    
    var stringValue: String
    init?(stringValue: String) {
        self.stringValue = stringValue
    }
    
    var intValue: Int? { return nil }
    init?(intValue: Int) { return nil }
}

let photoFeed = PhotoFeed(feedKey: "12345", feedUrl: "https://dummy.url.com/thumbnails/16869828-e75babd8.jpg", feedDate: Date())
let encoder = JSONEncoder()
encoder.keyEncodingStrategy = .custom({ (keys) -> CodingKey in
    let keyString = keys.last!.stringValue
    let stringValue =  "photo_" + keyString
    return PhotoCodingKeys(stringValue: stringValue)!
})
encoder.outputFormatting = .prettyPrinted

let data = try! encoder.encode(photoFeed)
print(String(data: data, encoding: .utf8)!)

//OUTPUT
{
  "photo_feedUrl" : "https:\/\/dummy.url.com\/thumbnails\/16869828-e75babd8.jpg",
  "photo_feedDate" : 610810993.52611899,
  "photo_feedKey" : "12345"
}
```

## 3. [Encoding Custom Types With Encodable In Swift 4](https://medium.com/@pxpgraphics/encoding-custom-types-with-encodable-in-swift-4-947721e4d5dc)

### 3.1 Encodable

```Swift
struct FavoritedMedia {
    let id: Int
    let type: MediaType
    let isFavorited: Bool
}
extension FavoritedMedia {
    enum MediaType: String {
        case movie
        case tv
    }
}
extension FavoritedMedia: Encodable {
    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(id, forKey: .id)
        try container.encode(type.rawValue, forKey: .type)
        try container.encode(isFavorited, forKey: .isFavorited)
    }
}
```

### 3.2 Decodable

```Swift
struct Movie: Decodable {
    // Int, String, Date, Double all conform to Codable.
    let id: Int
    let title: String
    let tagline: String
    let releaseDate: Date
    let voteAverage: Double
    let voteCount: Int
// Some JSON keys should be renamed to follow the API Design Guidelines.
    enum CodingKeys: String, CodingKey {
        case id
        case title       = "original_title"
        case tagline
        case releaseDate = "release_date"
        case voteAverage = "vote_average"
        case voteCount   = "vote_count"
    }
}

extension Movie: Decodable {
    init(from decoder: Decoder) throws {
       let values = try decoder.container(keyedBy: CodingKeys.self)
       id = try values.decode(Int.self, forKey: .id)
       title = try values.decode(String.self, forKey: .title)
       tagline = try values.decode(String.self, forKey: .tagline)
// We decode the value to String, then transform into the desired Date type.
       let releaseDateString = try values.decode(String.self, forKey: .releaseDate)
       releaseDate = DateFormatter.date(from: releaseDateString)
        voteAverage = try values.decode(Double.self, forKey: .voteAverage)
        voteCount = try values.decode(Int.self, forKey: .voteCount)
    }
}
```

## 4. [ios - 使用Codable解析嵌套的无键JSON](https://www.coder.work/article/4413354)

```Swift

let json = """
        {
          "contents": {
            "data": [
              {
                "type": "type1",
                "id": "6a406cdd7a9cace5"
              },
              {
                "type": "type2",
                "dbl": 1.01
              },
              {
                "type": "type3",
                "int": 5
              }
            ]
          }
        }
        """

struct Item1: Codable {
   let type: String
   let id: String
}

struct Item2: Codable {
   let type: String
   let dbl: Double
}

struct Item3: Codable {
   let type: String
   let int: Int
}

enum Interim {
  case type1 (Item1)
  case type2 (Item2)
  case type3 (Item3)
  case unknown  //to handle unexpected json structures
}

extension Interim: Decodable {
   private enum InterimKeys: String, CodingKey {
      case type
      case id
      case dbl
      case int
   }
   init(from decoder: Decoder) throws {
      let container = try decoder.container(keyedBy: InterimKeys.self)
      let type = try container.decode(String.self, forKey: .type)
      switch type {
      case "type1":
         let id = try container.decode(String.self, forKey: .id)
         let item = Item1(type: type, id: id)
         self = .type1(item)
      case "type2":
         let dbl = try container.decode(Double.self, forKey: .dbl)
         let item = Item2(type: type, dbl: dbl)
         self = .type2(item)
      case "type3":
         let int = try container.decode(Int.self, forKey: .int)
         let item = Item3(type: type, int: int)
         self = .type3(item)
      default: self = .unknown
      }
   }
}
```
