def fibonacci(n):
   
    dp = [0] * (n + 1)
    if n > 0:
        dp[1] = 1

    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]

    return dp[n]

n = 3
print(f"Fibonacci number at position {n} is {fibonacci(n)}")
