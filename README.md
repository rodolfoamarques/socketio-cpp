# socketio-cpp
Basic usage of Socket.IO CPP implementation, based on the libs provided by the [SocketIO Team](https://github.com/socketio)

# First off
First things first. To completelly use this example you need to install:

X-Code
	Install it from the App Store.

Homebrew
	Open a terminal and type:
	`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

NPM & Node.JS
	Open a terminal and type:
	`brew install node`

CLang
	Follow the instructions provided in the llvm website: [CLang Get Started](http://clang.llvm.org/get_started.html)

CMake
	Open a terminal and type:
	`brew install cmake`


# socket.io submodule
This submodule is necessary to execute an example usage of this repo against the socket.io example chat!

## install
Follow the same instructions as in: [Socket.IO Chat Example](https://github.com/socketio/socket.io/tree/master/examples/chat)

```
$ cd socket.io
$ npm install
$ cd examples/chat
$ npm install
$ node .
```

This will open the server on localhost, port 3000.
You can now open your browser and navigate to localhost:3000/ to get a "what's your username?" page and then open the chat service.
You can kill the server at anytime by pressing ctrl+c.


# socket.io-cpp-client submodule
This submodule is the actual library that will be required in your C++ code.

### install
Follow the instructions labeled "With CMake" at: [Socket.IO Cpp Client Install With CMake](https://github.com/socketio/socket.io-client-cpp/blob/master/INSTALL.md#with-cmake)
You will only need to skip the step where it tells you to download the repository, since it is already submoduled here.
Also watch the information on step 5. If you wish, you can just copy the outputs of the `./build` directory to your project and use them as they are.


# Make and run this sample
 - Download this repository with all the submodules.
`git clone --recurse-submodules https://github.com/rodolfoamarques/socketio-cpp.git`

 - Install all the necessary 3rd party requirements described in []().
 - Execute the Chat example as described in []() and run it in the browser, leaving the chat window open and the server online.
 - Open the terminal at the root of this repository, execute the `make` command.

And that's it. This example usage will create 3 different users and send the message 'hello' 10 times for each of them.
You can read the terminal outputs of the process and also watch the result in the browser chat window!




Feel free to use this code as a start skeleton for your own projects and don't forget to credit the authors!
