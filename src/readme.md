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

### features

corefw features and memory management

gnustep style api

type inference using var and $ to declare variable,

```
var b = $(true);
CFLog("b = %$\n", b);
```

prints:
```
[2021-07-13 20:42:35] bb = YES
```

true is a _Bool value, so $ creates a CFBool.
CFLog with %$ extracts the .toString interface, displaying 'YES'

-DCoreFX_Advanced_Mode