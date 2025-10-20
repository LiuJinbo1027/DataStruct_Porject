import math

R_0 = float(input("R_0 （欧姆）"))
delta_R = float(input("delta_R (欧姆)"))
delta_I = float(input("delta_A (微安)"))
I_m = float(input("I_m (微安)"))
R_0_ = float(input("R_0`"))
delta_R_ = float(input("delta_R_0`"))
delta_I_ = float(input("delta_I (微安)"))

R_x = math.sqrt(R_0*R_0_)
print(R_x)
def delta_R_calculation(number):
    """
    对数字的各个数位进行加权运算，返回浮点数结果 total。
    格式：数位值 * 权重 * 10^{-指数}
    """
    # 转换为字符串处理
    num_str = str(number)

    # 分离整数和小数部分
    if '.' in num_str:
        integer_str, decimal_str = num_str.split('.')
    else:
        integer_str = num_str
        decimal_str = '0'

    # 确保小数部分至少有一位
    decimal_str = decimal_str.ljust(1, '0')

    total = 0.0
    n = len(integer_str) + 1  # 总位数+1

    # 处理整数部分
    for i, digit_char in enumerate(integer_str):
        digit = int(digit_char)
        position = len(integer_str) - i
        place_value = 10 ** (position - 1)

        if position >= 3:
            weight = 1
            exponent = 3
            term = digit * place_value * weight * (10 ** -exponent)
        elif position == 2:
            weight = 2
            exponent = 3
            term = digit * place_value * weight * (10 ** -exponent)
        elif position == 1:
            weight = 5
            exponent = 2
            term = digit * place_value * weight * (10 ** -exponent)
        else:
            term = 0

        total += term

    # 处理小数部分
    for i, digit_char in enumerate(decimal_str):
        digit = int(digit_char)
        position = -(i + 1)

        if i == 0:
            weight = 5
            exponent = 2
            place_value = 10 ** position
            term = digit * place_value * weight * (10 ** -exponent)
            total += term

    # 添加 n * 30 * 10^{-3} 项
    n_term = n * 30 * (10 ** -3)
    total += n_term

    return total


def E_calculate(delta_R_0, delta_R_0_, R_0, I_m, S, S_):
    E = 1/2 * math.sqrt( (delta_R_0/(math.sqrt(3)*R_0))**2 + (delta_R_0_/(math.sqrt(3)*R_0))**2 + (I_m/S)**2 + (I_m/S_)**2)
    return E

delta_R_0 = delta_R_calculation(R_0)
delta_R_0_ = delta_R_calculation(R_0_)
print(f"delta_R_0 = {delta_R_0:.10f}, delta_R_0' = {delta_R_0_:.10f}")

S = delta_I * R_0 / delta_R
S_ = delta_I_ * R_0_ / delta_R_
print(f"S = {S:.10f}, S' = {S_:.10f}")

E = E_calculate(delta_R_0, delta_R_0_, R_0, I_m, S, S_)
print(f"E = {E:.10f}")

U = R_x * E
print(f"U = {U:.10f}")

print(f"R = {R_x:.10f} ± {U:.10f}")


