//
// Created by Ali Kooshesh on 1/22/23.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        inputFileName{name} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
    return c == '<' || c == '/' || c == '>';

    // you need to replace this with code that compares c with characters like '<', '>', etc.
}

Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    while( inputStream.get(c) && ! charOfInterest(c) ) {
        // keep track of the line number and the character position

    }

    // The above loop stops because one of its conditions is false. That means
    // either function get failed, which happens at the end of the file, or
    // c, the character that get read, is a character of interest. The other
    // possibility is if the input file was not open or the input somehow got clobbered.

    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }

    // Now, we go through a sequence of if ... else if statements
    // to identify the token whose first character we have just read. This is
    // the character that caused the while loop to terminate.

    if( c == '<' ) {
        // A possible open tag.
        // When this condition is ture, you need to
        // determine if it is immediately followed by a name, which means it is
        // an open tag, or a /, which means it might be a close tag, or it is a
        // random open angle-bracket. Here, to demonstrate how you make an open
        // tag token, we assume the input contained <em. That mean, we have
        // determined that it is a open tag (that there is a letter after the open
        // angle bracket, and that we have read the tag name, em, into a variable.
        // We use the variable that contains the name to create the token.
        if ( inputStream.peek() == '/'){
            inputStream.get(c)
            token.makeCloseTag(c);
        }
        const std::string fakeTagName = "em";
        token.makeOpenTag(fakeTagName);
        return token;
    } else if( c == '>' ) {
        token.isCloseAngleBracket() = true;
        return token;
    } // ... more if-else statements here.
    else {
        // The condition of one of the above "if ... else if" statements should
        // evaluate to true because function charOfInterest return true when it
        // finds a character that is the start of some token and that the
        // "if ... else if" has one case for each character that starts a token.
        // Therefore, the control should never get here. However, it is always
        // a good idea to have an "else" when you have a sequence of "if ... else if"
        // statements so that you do not end up with a case that has not been handled.
        // For example, you forgot to account for one of the cases.
        std::cout << "There is a logic error in unction Tokenizer::getToken.\n";
        std::cout << "The function doesn't know how to process this character: ->" << c << "<-\n";
        exit(1);
    }

    return token; // The control SHOULD NOT reach this statement.
}
