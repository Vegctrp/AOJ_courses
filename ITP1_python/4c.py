while True:
    a, op, b = input().split()
    a, b = int(a), int(b)
    if op == "?":
        break

    if op == '+':
        print(a + b)
    elif op == '-':
        print(a - b)
    elif op == '*':
        print(a * b)
    elif op == '/':
        print(a // b)