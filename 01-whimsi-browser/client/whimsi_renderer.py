import tkinter as tk
from PIL import Image, ImageTk

class WhimsiRenderer:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("WhimsiBrowser")
        self.root.resizable(False, False)
        self.canvas = tk.Canvas(self.root, width=800, height=600)
        self.canvas.pack()
        self.images = []
    
    def exitonclick(self):
        self.root.mainloop()

    def load_image(self, image_path, size):
        image = Image.open(image_path)
        w, h = image.size
        ratio = min(size / w, size / h)
        nw, nh = int(w * ratio), int(h * ratio)
        image = image.resize((nw, nh), Image.LANCZOS)
        return ImageTk.PhotoImage(image)

    def draw_text(self, x, y, text, size, color):
        self.canvas.create_text(x, y, text=text, font=("Arial", size), fill=color, anchor='nw')
    
    def draw_clickable_text(self, file_path, x, y, text, size, color, onclick_lambda):
        text_id = self.canvas.create_text(x, y, text=text, font=("Arial", size), fill=color, anchor='nw', tags="clickable")
        self.canvas.tag_bind(text_id, "<Button-1>", lambda _, path=file_path: onclick_lambda(path))

    def clear(self):
        self.canvas.delete("all")

    def draw_rectangle(self, x, y, width, height, color):
        self.canvas.create_rectangle(x, y, x + width, y + height, fill=color)

    def draw_circle(self, x, y, radius, color):
        self.canvas.create_oval(x - radius, y - radius, x + radius, y + radius, fill=color)

    def draw_cat(self, x, y, size):
        cat_img = self.load_image("imgs/cat.png", size)
        self.canvas.create_image(x, y, image=cat_img, anchor='nw')
        self.images.append(cat_img)

    def draw_alien(self, x, y, size):
        alien_img = self.load_image("imgs/alien.png", size)
        self.canvas.create_image(x, y, image=alien_img, anchor='nw')
        self.images.append(alien_img)

    def draw_rainbow(self, x, y, size):
        rainbow_img = self.load_image("imgs/rainbow.png", size)
        self.canvas.create_image(x, y, image=rainbow_img, anchor='nw')
        self.images.append(rainbow_img)
