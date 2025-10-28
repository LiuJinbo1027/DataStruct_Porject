import math

m_hook = 43
m_plate = 480
m_circle = 366
m_zhu = 150
R_plate = 100
R_in_circle = 90
R_out_circle = 100
d_1 = 50
d_2 =75
g = 9.7988

R_roll = float(input("转轮半径(mm)"))
m_weight = float(input("砝码质量(g)"))
B_1 = float(input("B_1: "))
B_2 = float(input("B_2: "))

J = (m_weight + m_hook)* 10**(-6) * R_roll *(g - R_roll*B_1* 10**(-3)) / (B_1 - B_2)

print(f"J = {J:.3e}")
