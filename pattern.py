import turtle

vikram = turtle.Turtle()

position = 100
vikram.speed(0)
a = 1
b = 1

for x in range (0,4):
    b *= -1
    if(x == 2):
        a *= -1

    vikram.penup()
    vikram.goto(position*a,position*b)
    vikram.pendown()

    for x in range (60):
        for x in range (4):
            vikram.forward(100)
            vikram.left(90 - x)
