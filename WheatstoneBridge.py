import math

R_0 = input("R_0 （欧姆）")
delta_R = input("delta_R (欧姆)")
delta_I = input("delta_A (微安)")
I_m = input("I_m (微安)")
R_0_ = input("R_0`")
delta_R_ = input("delta_R_0`")
delta_I_ = input("delta_I (微安)")

R_x = math.sqrt(R_0*R_0_)
print(R_x)

def delta_R_calculation(number):
    """
    对数字的各个数位进行加权运算
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
    
    total = 0
    n = len(integer_str) + 1  # 总位数+1
    # process_steps = []  # 记录计算过程
    
    # 处理整数部分（从高位到低位）
    for i, digit_char in enumerate(integer_str):
        digit = int(digit_char)
        position = len(integer_str) - i  # 位置（万位=5，千位=4，百位=3，十位=2，个位=1）
        place_value = 10 ** (position - 1)  # 位值（10000, 1000, 100, 10, 1）
        
        # 根据位置设置不同的权重
        if position >= 3:  # 百位及以上
            weight = 1
            exponent = 3
            term = digit * place_value * weight * (10 ** -exponent)
        elif position == 2:  # 十位
            weight = 2
            exponent = 3
            term = digit * place_value * weight * (10 ** -exponent)
        elif position == 1:  # 个位
            weight = 5
            exponent = 2
            term = digit * place_value * weight * (10 ** -exponent)
        
        total += term
        process_steps += (f"{digit}*{place_value}*{weight}*10^{{-{exponent}}} = {term:.4f}")
    
    # 处理小数部分
    for i, digit_char in enumerate(decimal_str):
        digit = int(digit_char)
        position = -(i + 1)  # 小数位位置（-1, -2, ...）
        
        if i == 0:  # 第一位小数
            weight = 5
            exponent = 2
            place_value = 10 ** position  # 0.1, 0.01, ...
            term = digit * place_value * weight * (10 ** -exponent)
            
            total += term
            process_steps += (f"{digit}*{place_value}*{weight}*10^{{-{exponent}}} = {term:.6f}")
    
    # 添加 n * 30 * 10^{-3} 项
    n_term = n * 30 * (10 ** -3)
    total += n_term
    process_steps += (f"n*30*10^{{-3}} = {n}*30*0.001 = {n_term:.4f}")
    
    return process_steps

def E_calculate(delta_R_0, delta_R_0_, R_0, I_m, S, S_):
    E = 1/2 * math.sqrt( (delta_R_0/(math.sqrt(3)*R_0))**2 + (delta_R_0_/(math.sqrt(3)*R_0))**2 + (I_m/S)**2 + (I_m/S_)**2)
    return E

delta_R_0 = delta_R_calculation(R_0)
delta_R_0_ = delta_R_calculation(R_0_)
print("delta_R_0 = %.10f, delta_R_0 = %.10f", delta_R_0, delta_R_0_)

S = delta_I * R_0 / delta_R
S_ = delta_I_ * R_0_ / delta_R_
print("S= %.10f, S` = %.10f", S, S_)

E = E_calculate(delta_R_0, delta_R_0_, R_0, I_m, S, S_)
print("E= %.10f", E)

U = R_x * E
print("U = %.10f", U)
print("R = %.10f +- %.10f", R_x, U)

