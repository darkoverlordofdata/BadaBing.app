## CoreFramework 


Based on https://github.com/Midar/corefw, heavily influenced by the gnustep core.

### CoreFoundation.h
* CFArray
* CFBitVector*
* CFBool
* CFBox
* CFClass
* CFDate
* CFDouble
* CFFile
* CFInt
* CFMap
* CFObject
* CFRange
* CFRefPool
* CFSocket
* CFStream
* CFString
* CFTypes
* CFUUID*


missing?
* CFCalendar
* CFData
* CFBundle
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

