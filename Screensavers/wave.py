import math
import time
import os


def print_format_table():
    """
    prints table of formatted text format options
    """
    for style in range(8):
        for fg in range(30, 38):
            s1 = ''
            for bg in range(40, 48):
                fmt = ';'.join([str(style), str(fg), str(bg)])
                s1 += '\x1b[%sm %s \x1b[0m' % (fmt, fmt)
            print(s1)
        print('\n')


def colored(string, color):
    fmt = ';'.join([str(0), str(color + 30), str(48)])
    c_string = "\x1b[%sm %s \x1b[0m" % (fmt, string)
    return c_string


def main():
    try:
        width = os.get_terminal_size().columns - 1
    except OSError:
        width = 100

    step = 0.03
    greyscale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~i!lI;:,\"^`."

    i = 0
    while True:
        i += 1
        angle = step * i
        if angle > 2 * math.pi:
            angle -= 2 * math.pi

        line_len = (width // 2) + int(width // 2 * math.sin(angle))
        line = ""
        while len(line) < line_len:
            line += greyscale[::-1] + greyscale
        line = line[:line_len:]
        line = line[::-1]

        color = (i // 20) % 7 + 1
        line = colored(line, color)
        print(line)

        time.sleep(1 / 60)


if __name__ == "__main__":
    main()

