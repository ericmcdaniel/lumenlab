from tkinter import Tk
from tkinter import ttk

# Create the main window
root = Tk()
root.title("Hello World with ttk")

# Create a frame to hold the widgets
frm = ttk.Frame(root, padding=10)
frm.grid()

# Create a Label widget
ttk.Label(frm, text="Hello World!").grid(column=0, row=0)

# Create a Button widget to quit the application
ttk.Button(frm, text="Quit", command=root.destroy).grid(column=1, row=0)

# Start the main event loop
root.mainloop()