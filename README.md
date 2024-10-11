# 4re5-crypt
Simple one way hash algorithm

## Compile
```
git clone https://github.com/4RE5group/4re5-crypt
cd 4re5-crypt

g++ main.cpp -o 4re5-crypt
chmod 777 ./4re5-crypt
```
then see [Usage](#Usage)


## Usage
`./4re5-crypt <text> <salt>`  or `./4re5-crypt <text>` to use text as salt 
for exemple `./4re5-crypt "Hello World!" "mySalt"` will return `Dr,fA+Jx2lG1P~8r#7VD>x)=\JD~/Cb&JD`
