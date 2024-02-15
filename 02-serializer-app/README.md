## Writing a Custom Serialization Protocol using C++ Sockets

### Getting Started
If you cloned the repository for assignment 1, you should be able to run `git pull` to download this new project folder. If you forked the repository, you can try `git fetch upstream` to download the folder.

Inside `02-serializer-app/`, set up a `build/` directory for CMake as before:

```
mkdir build
cd build
```

Inside the build directory we can run CMake to generate a Makefile for the project.
```
cmake ..
make
```

### Part 1: Implementing the serializer
Take a look at include/bakery.hpp and src/bakery.cpp to get a sense of what changes you will need to make to implement the additional functions described in the write-up. I have provided function interfaces for each of these. For this part, you should modify src/test_serializer.cpp to test your implementation. You can run the tests by running `./test_serializer` from the build directory.

### Part 2: Implementing the server and client

Since this is a client-server application, running `make` will generate two programs: `client` and `server`. Try starting the server in one terminal `./server` and then running the client in another terminal `./client`. Make sure that you start the server first, as otherwise the client will complain about there not being a server.

Take a look at src/client.cpp and server.cpp for an example of how to send messages using sockets. After checking the you can run these files, start figuring out how to implement the message format for this protocol as laid out in the assignment pdf.


Note that for this assignment we are running everything locally (both client and server are running on the same computer). However, the code we write for this assignment should work over the internet!
