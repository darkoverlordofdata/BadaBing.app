## CoreFramework 


Based on https://github.com/Midar/corefw, heavily influenced by the gnustep core.

The first problem I ran into with inlining corefw, is that the string.h header name conflicts with the standard library. 

Since I have to make a trivial customization, why stop there? I have trouble reading snake case,so naming is refactored, as well as constructors. Mostly inspired by gnustep 

### <strike>CoreFoundation.h</strike>CoreFX.h
* CFArray
* CFBitVector - unfinished
* CFBool
* CFBox
* CFClass
* CFDate - unfinished
* CFDouble
* CFFile
* CFInt
* CFList - unfinished
* CFLog - partial
* CFMap
* CFObject
* CFRange
* CFRefPool
* CFRuntime - tbd?
* CFSocket
* CFStream
* CFString
* CFTypes
* CFTuple - unfinished
* CFUUID - unfinished



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

* CFEither ?
* CFMaybe ?
* CFOption ?
* CFTry ?

CFLog function. Use %@ as the print selector for CFObjects:
```
CFLog("My name is %@\n", CFGetName(obj));
```

