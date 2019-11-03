// ILPDFObjectParser.h
//
// Copyright (c) 2018 Derek Blair
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>


// This is the color for all pdf forms.
#define ILPDFWidgetColor [UIColor colorWithRed:0.7 green:0.85 blue:1.0 alpha:0.7]

// PDF uses ASCII for readable characters, but allows any 8 bit value unlike ASCII, so we use an extended ASCII set here.
// The character mapped to encoded bytes over 127 have no significance, and are octal escaped if needed to be read as text in the PDF file itself.
#define ILPDFStringCharacterEncoding NSISOLatin1StringEncoding

// Character macros
#define isWS(c) ((c) == 0 || (c) == 9 || (c) == 10 || (c) == 12 || (c) == 13 || (c) == 32)
#define isDelim(c) ((c) == '(' || (c) == ')' || (c) == '<' || (c) == '>' || (c) == '[' || (c) == ']' || (c) == '{' || (c) == '}' || (c) == '/' ||  (c) == '%')
#define isODelim(c) ((c) == '(' ||  (c) == '<' ||  (c) == '[')
#define isCDelim(c) ((c) == ')' ||  (c) == '>' ||  (c) == ']')

#define ILPDFFormMinFontSize 8
#define ILPDFFormMaxFontSize 22



@class ILPDFDocument;

NS_ASSUME_NONNULL_BEGIN

/** The ILPDFObjectParser class converts a string representation of a PDF object into
a series of tokens representing object components of the represented object. The tokens may be 
keys and values in the case of a dictionary or elements of an array, for example. ILPDFObjectParser makes no assumptions
about the type of the PDF object represented in str.
As an example:
 
     NSString *dictionaryString = @"<</Key1 (value1) /Key2 (value2) /Key3 [32 /aname]>>"
     ILPDFObjectParser *parser = [ILPDFObjectParser parserWithString:dictionaryString Parent:parentDocument];
     NSMutableArray *keysAndValues = [NSMutableArray array];
     
     for (id token in parser) {
        [keysAndValues addObject:token];
     }
     // From here we can extract all keys and corresponding values using the NSArray
 
 ILPDFObjectParser is not meant to replace the Core Graphics PDF functions but rather provide of means of extracting more data related to the PDF file structure such as specific object and generation numbers.
 */



@interface ILPDFObjectParser : NSObject <NSFastEnumeration>


/**---------------------------------------------------------------------------------------
 * @name Creating a ILPDFObjectParser
 *  ---------------------------------------------------------------------------------------
 */

/** Initializes with a byte sequence to parse
 @param bytes The byte sequence to parse.
 @discussion The byte sequence should be identical to how it appears in a PDF file.
 @return self.
 */
- (instancetype)initWithBytes:(NSData *)bytes NS_DESIGNATED_INITIALIZER;

/** Creates an instance of ILPDFObjectParser initialized with a sequence of bytes.
 @param bytes The byte sequence of the object to parse as it appears in a PDF file.
 @return An instance of ILPDFObjectParser.
 */
+ (ILPDFObjectParser *)parserWithBytes:(NSData *)bytes;

@end


NS_ASSUME_NONNULL_END
