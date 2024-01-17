import tkinter as tk
import threading
import sys
import queue
import warnings
 
HIGH_LIGHT="black"
LOW_LIGHT="#92b098"
class TimerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("时分秒计时器")
        self.root.config(bg=LOW_LIGHT)
        self.display_digits = []
        # 创建35*5的Canvas数组
        self.create_display()

        # 创建按钮
        self.create_buttons()

        self.exit_program = threading.Event()
        self.input_queue=queue.Queue()

        self.input_thread=threading.Thread(target=self.console_input_listener)
        self.input_thread.start()

        root.protocol("WM_DELETE_WINDOW", self.on_close)

        self.update_timer()
        
    def create_display(self):
        # 创建Canvas数组
        for i in range(5):
            row_digits = []
            for j in range(39):
                digit = tk.Canvas(self.root, width=20, height=35,bg=LOW_LIGHT, highlightthickness=1,highlightbackground=LOW_LIGHT)
                digit.grid(row=i, column=j)
                row_digits.append(digit)
            self.display_digits.append(row_digits)

    def create_buttons(self):
        # 创建按钮框架
        button_frame = tk.Frame(self.root)
        button_frame.grid(row=5, columnspan=39, pady=10)
        button_frame.config(bg=LOW_LIGHT)
        # 创建开始、重置按钮
        start_button = tk.Button(button_frame, text="开始", width=10, font=("Arial", 20, "bold"),bg=LOW_LIGHT, command=self.start_timer)
        start_button.grid(row=0, column=0, padx=10)

        self.pause_button = tk.Button(button_frame, text="暂停", width=10, font=("Arial", 20, "bold"),bg=LOW_LIGHT, command=self.pause_timer)
        self.pause_button.grid(row=0, column=1, padx=10)

        reset_button = tk.Button(button_frame, text="重置", width=10, font=("Arial", 20, "bold"),bg=LOW_LIGHT, command=self.reset_timer)
        reset_button.grid(row=0, column=2, padx=10)

    def start_timer(self):
        # 读取文本文件中的数据
        sys.stdout.write("start\n")
        sys.stdout.flush()
        self.state=1

    def reset_timer(self):
        sys.stdout.write("zero\n")
        sys.stdout.flush()
        self.state=0
        for row in self.display_digits:
            for digit in row:
                digit.config(bg=LOW_LIGHT)

    def pause_timer(self):
        if self.state==1:
            sys.stdout.write("pause\n")
            sys.stdout.flush()
            self.pause_button.config(text="启动")
            self.state=0
        elif self.state==0:
            sys.stdout.write("work\n")
            sys.stdout.flush()
            self.pause_button.config(text="暂停")
            self.state=1

    def console_input_listener(self):
        while not self.exit_program.is_set():
            try:
                data=[]
                for i in range(5):
                    line=sys.stdin.readline()
                    data.append(line)
                self.input_queue.put(data)
            except EOFError:
                pass
                
    def clear_timer(self):
        for row in self.display_digits:
            for digit in row:
                digit.config(bg=LOW_LIGHT)

    def update_timer(self):
        if not self.exit_program.is_set():
            try:
                data=self.input_queue.get_nowait()
                self.clear_timer()
                for i in range(5):
                    for j in range(39):
                        if data[i][j]=='*':
                            self.display_digits[i][j].config(bg=HIGH_LIGHT)
            except queue.Empty:
                pass
            self.root.after(50,self.update_timer)

    def on_close(self):
        # 处理窗口关闭事件
        self.exit_program.set()
        self.root.destroy()
        
if __name__ == "__main__":

    with warnings.catch_warnings():
        warnings.simplefilter("ignore")
        root = tk.Tk()
        app = TimerApp(root)
        root.mainloop()
