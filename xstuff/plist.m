#include <Foundation/Foundation.h>
//clang plist.c -o plist -I/usr/local/include

int 
main (void)
{
  NSAutoreleasePool *pool = [NSAutoreleasePool new];
  NSMutableDictionary *dict;
  NSDictionary *dict2;

  dict = [NSMutableDictionary new];
  AUTORELEASE (dict);

  dict2 = [NSDictionary dictionaryWithObjectsAndKeys: 
             @"Nicola", @"Name",
             @"Pero", @"Surname",
             @"n.pero@mi.flashnet.it", @"Email", nil];
  [dict setObject: dict2  forKey: @"Nicola"];

  dict2 = [NSDictionary dictionaryWithObjectsAndKeys: 
             @"Ettore", @"Name",
             @"Perazzoli", @"Surname",
             @"ettore@helixcode.com", @"Email", nil];
  [dict setObject: dict2  forKey: @"Ettore"];

  dict2 = [NSDictionary dictionaryWithObjectsAndKeys: 
             @"Richard", @"Name",
             @"Frith-Macdonald", @"Surname",
             @"richard@brainstorm.co.uk", @"Email", nil];
  [dict setObject: dict2  forKey: @"Richard"];

  if ([dict writeToFile: @"/home/darko/testing" atomically: YES])
    {
      NSLog (@"Success");
    }
  else
    {
      NSLog (@"Failure");
    }

  return 0;
}

#include <Foundation/Foundation.h>

int 
main (void)
{
  NSAutoreleasePool *pool = [NSAutoreleasePool new];
  NSDictionary *dict;
  NSDictionary *dict2;
  NSString *email;

  dict = [NSDictionary dictionaryWithContentsOfFile: 
                         @"/home/nico/testing"];
  dict2 = [dict objectForKey: @"Ettore"];
  email = [dict2 objectForKey: @"Email"];

  NSLog (@"Ettore's Email is: %@", email);

  return 0;
}
