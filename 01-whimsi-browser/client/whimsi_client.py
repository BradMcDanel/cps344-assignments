import socket
import random

from whimsi_renderer import WhimsiRenderer

# YOU DO NOT NEED TO MODIFY THIS FUNCTION!
def send_request_to_server(request, host="localhost", port=53009):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(request.encode())
            response = s.recv(1024).decode()
            return response
    except Exception as e:
        print(f"Error communicating with server: {e}")
        return None

# Below is an example of how to use the renderer
# TODO: Replace this with your own code
# (1) Parse a .whimsi file and support all the commands
# (1a) Handling IMPORT requires recursive parsing
# (1b) Handling CLICK requires binding the on_click function below to load the file
# (2) Instead of loading files from the local file system, load them from the server
if __name__ == "__main__":
    whimsi = WhimsiRenderer()

    def on_click(file_path):
        # Example: Print the clicked file path
        print("Clicked file:", file_path)
        # TODO: Fetch file from server and render it
        # Here is an example of loading cats which you should replace
        whimsi.clear()
        for i in range(10):
            whimsi.draw_cat(random.randint(0, 800), random.randint(0, 600), random.randint(50, 200))

    for i in range(10):
        whimsi.draw_text(10 + i * 10, 10 + i * 20, "Hello World!", 20, "black")
    whimsi.draw_alien(200, 200, 200)

    whimsi.draw_clickable_text("../examples/cats.whimsi", 450, 450, "Load cats", 30, "blue", on_click)

    # Example of how to fetch from server
    # Note - make sure to run server first otherwise you will get None
    hello_response = send_request_to_server("HELLO")
    print("SERVER SAYS:", hello_response)

    # needed at very end, otherwise nothing will be shown
    whimsi.exitonclick()
