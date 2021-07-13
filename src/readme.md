## CoreFramework 


Based on https://github.com/Midar/corefw, heavily influenced by the gnustep core.

### CoreFoundation.h
* CFArray
* CFBitVector*
* CFBool
* CFBox
* CFClass
* CFDouble
* CFFile
* CFInt
* CFMap
* CFObject
* CFRange
* CFRefpool
* CFSocket
* CFStream
* CFString
* CFTypes
* CFUUID*


missing?
* CFCalendar
* CFData
* CFBundle
* CFDate
* CFDateFormatter
* CFDictionary
* CFError
* CFNull
* CFNumber
* CFNumberFormatter
* CFSet
* CFRunLoop
* CFURL

CFLog function. Use %@ as the print selector for CFObjects:
```
CFLog("My name is %@\n", CFGetName(obj));
```

## UI

x11 widgets in c.


UIApplication
UIWindow
UIFont
UILabel
UIText
UIImage
UIKeyboardInput

