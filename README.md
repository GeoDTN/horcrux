#This C++17 code will achieve the following requirements.

##Save a file with the following steps:
```
> The user selects a file from his/her filesystem
> The user specifies the number of horcrux he/she wants to create
> The application encrypts the file with a randomly generated key
> The application splits the resulting buffer in n chunks where n is the
number of horcrux specified by the user
> The application saves the horcruxes on the disk in a folder specified
by the user
> The application shows the key used for encryption in base64 format
```
## Load a file with the following steps:
> The user selects the horcruxes he/she created before\
> The user inserts the encryption key he/she got during the saving\
process above
> The application reads the horcruxes from the disk\
> The application joins the encrypted buffers\
> The application decrypts the joined buffer with the provided key\
> The application saves back the plain file in a folder specified by the\
user

##The CLI should expose the following commands:\
                1.To encrypt and save

``` user@hostname:~$ horcrux create -n <horcrux count> <inputpath> <output path> ```\
                2.To load, decrypt and retrieve
  
```  user@hostname:~$ horcrux load -k <decryption key> <inputfiles> <output_file>```

          
To build and test this repo on ubuntu or similar distro, after installing all necessary libraries and setting up environment:\
``` git clone git@github.com:GeoDTN/horcrux.git```\
 ``` cd horcrux &&  mkdir  build  &&  cd build  &&  cmake ..  &&  make```
#### The app program executable is horcrux and unit test executable is  UnitTest/test_horcrux
### Note unit tests do not cover all test cases. And for  both app test and unit test, create and configure necessary files and directories.
