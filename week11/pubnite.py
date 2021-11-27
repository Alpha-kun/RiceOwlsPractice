import math

x_s, y_s, s_s, r_i, r_f = map(int, input().split())
x_a, y_a, s_a = map(int, input().split())
dis = math.sqrt((x_s - x_a) ** 2 + (y_s - y_a) ** 2)
t = (r_i - r_f) / s_s
dis_t = dis - s_a * t
res = 0
if r_f >= dis:
    pass
elif r_i >= dis and r_f >= dis_t:
    pass
elif r_i >= dis and r_f < dis_t:
    t_end = (dis - r_f) / s_a
    t_m = (dis - r_i) / (s_a - s_s)
    res = t_end - t_m
elif r_i < dis and r_f >= dis_t:
    t_m = (dis - r_i) / (s_a - s_s)
    res = t_m
else:
    t_end = (dis - r_f) / s_a
    res = t_end

print(res)
