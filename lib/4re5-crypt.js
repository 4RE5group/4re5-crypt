const SALT_SIZE = 16;
const MAX_INPUT_SIZE = 512;
const OUTPUT_SIZE = 32;

alert("still in developement /!\\");

function setStr(originalStr, textToPrepend) {
    // Ensure the new string is long enough to hold the prepended characters
    return textToPrepend + originalStr.substring(textToPrepend.length);
}

function replaceChar(text, index, newChar) {
    if (index < 0 || index >= text.length) {
        console.error("Index out of bounds");
        return text;
    }
    // Replace the character at the specified index
    return text.substring(0, index) + newChar + text.substring(index + 1);
}

const crypt4re5 = {
    getSalt: function(salt) {
        let a = salt.lengt;
        for (let i = 0; i < a; i++) {
            let b = salt.charCodeAt(i);
            console.log(a, b);
            a += (b % 2 === 0) ? b : -b;
        }
        return (a < 0) ? -a : a % 10;
    },

    crypt: function(_text, _salt) {
        let outputHash = Array(OUTPUT_SIZE).fill('\0').join('');;

        let salt = Array(SALT_SIZE).fill('\0').join('');
        let text = Array(MAX_INPUT_SIZE).fill('\0').join('');


        // Check for input arguments
        if (_text.length >= MAX_INPUT_SIZE) {
            console.error("Input text length is way too big: expected between 1 to %d chars\n", MAX_INPUT_SIZE - 1);
            return;
        }
        text = setStr(text, _text);
        if (text.length == 0) {
            console.error("Please enter a valid text to crypt\n");
            return;
        }
        
        // If the salt argument is provided but empty, or if it's not provided, use `text` as the salt
        if (_salt != "" && _salt && _salt.length > 0) {
            if (_salt.length >= SALT_SIZE) {
                console.error("Salt is too big");
                console.log("'", _salt, "'");
                return;
            }
            salt = setStr(salt, _salt); // copy given salt
            saltint = crypt4re5.getSalt(salt);
        } else {
            saltint = crypt4re5.getSalt(text); // Use text as salt if salt is empty or not provided
        }
        console.log("saltInt =>", saltint);

        let char1, char2;
        let running = true;
        while (running) {
            for (let i = 0; i < text.length - 1; i += 2) {
                char1 = text[i];
                if (i + 1 < text.length) {
                    char2 = text[i + 1];
                }
                let transformedChar = (i + outputHash.length + char1.charCodeAt(0) + char2.charCodeAt(0)) + saltint;
                // Ensure the transformed character is within ASCII 20 to 126
                while (transformedChar > 126 || transformedChar <= 32) {
                    transformedChar -= 106;
                }
                newChar = String.fromCharCode(transformedChar);
                console.log(outputHash, saltint);
                // return;
                // Append the new character to the outputHash
                let len = outputHash.length;
                if (len < OUTPUT_SIZE - 1) {
                    outputHash[len] = newChar;
                    outputHash[len+1] = '\0';
                } else {
                    running = false;
                    break;
                }
            }
        }
 
        output = outputHash;
        
        return output;
    }
};


// Usage example
console.log(crypt4re5.crypt("text", "hello"));

// should return rltnvpxrzt|v~x@zB|D~F@HBJD"F$H&J
