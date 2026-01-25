# Assignment 1 - Whimsi Browser

## Getting Started

Before diving into the tasks, ensure you have the client and server code up and running. Follow these steps to get started:

### Cloning the Repository
- Open your terminal.
- Clone the repository using Git:
  `git clone https://github.com/BradMcDanel/cps344-assignments.git`

### Install Dependencies
- You will need to install Pillow to run the client: `pip install pillow`

### Starting the Server
- Navigate to the `01-whimsi-browser` directory: 
  `cd cps344-assignments/01-whimsi-browser`
- Go to the `server/` directory: 
  `cd server`
- Run the Whimsi server:
  `python whimsi_server.py`

### Starting the Client
- Open another terminal, ensuring the server terminal remains active.
- Navigate to the `client/` directory:
  `cd ../client`
- Run the Whimsi client:
  `python whimsi_client.py localhost/hello.whimsi`

You should see a window pop up displaying the client interface. Check the server terminal for a confirmation message (`('127.0.0.1', port) - HELLO`) each time you start the client. This indicates successful communication between the client and server.

### Testing Your Implementation

Once you've implemented the client and server, test with the provided whimsi files:

1. Run `python whimsi_client.py localhost/hello.whimsi`
   - You should see text, shapes, cats, an alien, and a rainbow
   - Clicking "Click for more text..." should clear the screen and show new content
   - Clicking "Click back to hello..." should return to the original page

2. Try other files in the `whimsi/` folder:
   - `python whimsi_client.py localhost/cats.whimsi`

3. Test error handling:
   - Request a non-existent file and verify you get `ERROR::FILE_NOT_FOUND`

Now that the setup is complete, you can proceed with the assignment tasks.
