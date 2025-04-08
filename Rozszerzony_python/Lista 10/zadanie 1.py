import keyboard
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import patches

class Snake:
    def __init__(self,size=15,tick=15):
        self.size=size
        self.tick=tick
        self.snake=[(0,0)]
        self.food=self.gen_food()
        self.direction=(1,0)
        self.game_over=False

    def play(self):
        while not self.game_over:
            if keyboard.is_pressed("up"):
                self.direction=(0,1)
            elif keyboard.is_pressed("down"):
                self.direction=(0,-1)
            elif keyboard.is_pressed("left"):
                self.direction=(-1,0)
            elif keyboard.is_pressed("right"):
                self.direction=(1,0)
            elif keyboard.is_pressed("esc"):
                self.game_over=True
            self.move()
            self.display()

    def gen_food(self):
        while True:
            food=(np.random.randint(0,self.size),np.random.randint(0,self.size))
            if food not in self.snake:
                return food

    def move(self):
        head=self.snake[0]
        new_head=(head[0]+self.direction[0],head[1]+self.direction[1])
        if(new_head in self.snake or new_head[0]<0 or new_head[0]>=self.size or new_head[1]<0 or new_head[1]>=self.size):
            self.game_over=True
            return
        self.snake.insert(0,new_head)
        if new_head==self.food:
            self.food=self.gen_food()
        else:
            self.snake.pop()

    def display(self):
        plt.clf()
        plt.axis("off")
        for i in range(self.size+1):
            plt.axhline(y=i,color="black",linestyle="-",linewidth=0.5)
            plt.axvline(x=i,color="black",linestyle="-",linewidth=0.5)
        for segment in self.snake:
            plt.gca().add_patch(patches.Rectangle((segment[0],segment[1]),1,1,fc="green"))
        plt.gca().add_patch(patches.Rectangle((self.food[0],self.food[1]),1,1,fc="red"))
        plt.axhline(y=0.06,color="black",linestyle="-",linewidth=0.5)
        plt.axvline(x=self.size-0.04,color="black",linestyle="-",linewidth=0.5)
        plt.xlim(0,self.size)
        plt.ylim(0,self.size)
        plt.draw()
        plt.pause(1/self.tick)

snake=Snake(15,15)
snake.play()