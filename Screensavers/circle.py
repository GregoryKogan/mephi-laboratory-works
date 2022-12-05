import os
import random
import curses
# import math


VEL = 10
RADIUS = 5


def draw_frame(width, height, pos_x, pos_y):
	stdscr = curses.initscr()
	for x in range(width):
		for y in range(height):
			c_x = abs(pos_x - x)
			c_y = abs(pos_y - y)
			if c_x**2 + c_y**2 < RADIUS:
				stdscr.addch(y, x, '#')


def movement():
	...


def main():
	width, height = os.get_terminal_size()
	pos_x, pos_y = width // 2, height // 2
	vel_x = random.random() * VEL
	vel_y = (VEL**2 - vel_x**2)**0.5
	draw_frame(width, height, pos_x, pos_y)
	pos_x, pos_y, vel_x, vel_y = movement(pos_x, pos_y, vel_x, vel_y)


if __name__ == "__main__":
	main()

