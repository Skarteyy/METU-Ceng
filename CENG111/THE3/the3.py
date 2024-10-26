import math

Q,T = [[(0, -2), (-3, 6), (-1, 5), (0, 0)], [(-2, 1), (4, -1), (2, -3)]]

def area(Q,T): 
    used_points = []

    if isInsideTriangle(T[0][0],T[0][1],T[1][0],T[1][1],T[2][0],T[2][1],Q[0][0],Q[0][1]):
        used_points.append([Q[0][0],Q[0][1]])
    if isInsideTriangle(T[0][0],T[0][1],T[1][0],T[1][1],T[2][0],T[2][1],Q[1][0],Q[1][1]):
        used_points.append([Q[1][0],Q[1][1]])
    if isInsideTriangle(T[0][0],T[0][1],T[1][0],T[1][1],T[2][0],T[2][1],Q[2][0],Q[2][1]):
        used_points.append([Q[2][0],Q[2][1]])
    if isInsideTriangle(T[0][0],T[0][1],T[1][0],T[1][1],T[2][0],T[2][1],Q[3][0],Q[3][1]):
        used_points.append([Q[3][0],Q[3][1]])
    
    if isInsideQuad(Q[0][0],Q[0][1],Q[1][0],Q[1][1],Q[2][0],Q[2][1],Q[3][0],Q[3][1],T[0][0],T[0][1]):
        used_points.append([T[0][0],T[0][1]])
    if isInsideQuad(Q[0][0],Q[0][1],Q[1][0],Q[1][1],Q[2][0],Q[2][1],Q[3][0],Q[3][1],T[1][0],T[1][1]):
        used_points.append([T[1][0],T[1][1]])
    if isInsideQuad(Q[0][0],Q[0][1],Q[1][0],Q[1][1],Q[2][0],Q[2][1],Q[3][0],Q[3][1],T[2][0],T[2][1]):
        used_points.append([T[2][0],T[2][1]])

    used_points = used_points + collisions(Q,T)
    if used_points == []:
        return 0
    sorted_points = sort_points_counterclockwise(used_points)

    return abs(area_calc(sorted_points))

def isInsideTriangle(x1,y1,x2,y2,x3,y3,x,y):
    A = area_triangle(x1,y1,x2,y2,x3,y3)
    A1 = area_triangle(x,y,x2,y2,x3,y3)
    A2 = area_triangle(x1,y1,x,y,x3,y3)
    A3 = area_triangle(x1,y1,x2,y2,x,y)

    if(A == A1+A2+A3):
        return True
    else:
        return False
    

def isInsideQuad(x1,y1,x2,y2,x3,y3,x4,y4,x,y):
    if is_point_on_line(x,y,x1,y1,x3,y3):
        return True
    A1 = isInsideTriangle(x1,y1,x2,y2,x3,y3,x,y)
    A2 = isInsideTriangle(x1,y1,x3,y3,x4,y4,x,y)
    if A1 or A2:
        return True
    return False

def is_point_on_line(x, y, x1, y1, x2, y2):
    if x1 == x2:  # vertical line
        return x == x1
    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1
    return y == m * x + b

def intersec(x1,y1,x2,y2,x3,y3,x4,y4):
    s1_x = x2-x1
    s1_y = y2-y1
    s2_x = x4-x3
    s2_y = y4-y3
    denominator = -s2_x * s1_y + s1_x * s2_y
    if denominator == 0:
        return None
    s = (-s1_y * (x1 - x3) + s1_x * (y1-y3)) / denominator
    t = (s2_x * (y1 - y3) - s2_y * (x1 - x3)) / denominator
    if 0 <= s <= 1 and 0 <= t <= 1:
        inter_x = x1 + (t * s1_x)
        inter_y = y1 + (t * s1_y)
        return [inter_x, inter_y]
    else:
        return None


def collisions(Q,T):
    collision = []
    #Intersections with 1st edge of the triangle
    for i in range(len(Q)):
        if i < 3:    
            a = intersec(Q[i][0],Q[i][1],Q[i+1][0],Q[i+1][1],T[0][0],T[0][1],T[1][0],T[1][1]) 
        else:
            a = intersec(Q[i][0],Q[i][1],Q[0][0],Q[0][1],T[0][0],T[0][1],T[1][0],T[1][1])
        if(a):
            collision.append(a)
    #Intersections with 2nd edge of the triangle
    for i in range(len(Q)):
        if i < 3:
            a = intersec(Q[i][0],Q[i][1],Q[i+1][0],Q[i+1][1],T[1][0],T[1][1],T[2][0],T[2][1])
        else:
            a = intersec(Q[i][0],Q[i][1],Q[0][0],Q[0][1],T[1][0],T[1][1],T[2][0],T[2][1])
        if(a):
            collision.append(a)
    #Intersections with 3rd edge of the triangle
    for i in range(len(Q)):
        if i < 3:
            a = intersec(Q[i][0],Q[i][1],Q[i+1][0],Q[i+1][1],T[2][0],T[2][1],T[0][0],T[0][1])
        else:
            a = intersec(Q[i][0],Q[i][1],Q[0][0],Q[0][1],T[2][0],T[2][1],T[0][0],T[0][1])     
        if(a):
            collision.append(a) 
    return collision

def area_triangle(x1, y1, x2, y2, x3, y3): 
    return 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))

def area_quad(x1,y1,x2,y2,x3,y3,x4,y4):
    return 0.5 * abs((x1*y2 - x2*y1) + (x2*y3 - x3*y2) + (x3*y4 - x4*y3) + (x4*y1 - x1*y4)) 

#Area Calculator of a List
def area_calc(lis):
    result1 = 0
    result2 = 0
    n = len(lis)
    
    for i in range(n-1):
        result1 += lis[i][0]*lis[i+1][1]
    result1 += lis[-1][0]*lis[0][1]

    for i in range(n-1):
        result2 += lis[i][1]*lis[i+1][0]
    result2 += lis[-1][1]*lis[0][0] 

    return 0.5*(result1 - result2)

def calculate_pivot(points):
    x_sum = sum(p[0] for p in points)
    y_sum = sum(p[1] for p in points)
    n = len(points)
    return (x_sum / n, y_sum / n)

def calculate_polar_angles(points, pivot):
    angles = []
    for p in points:
        dx = p[0] - pivot[0]
        dy = p[1] - pivot[1]
        angle = math.atan2(dy, dx)
        angles.append(angle)
    return angles

def adjust_angles(angles):
    adjusted_angles = [angle if angle >= 0 else angle + 2 * math.pi for angle in angles]
    return adjusted_angles

def sort_points_counterclockwise(points):
    pivot = calculate_pivot(points)
    angles = calculate_polar_angles(points, pivot)
    adjusted_angles = adjust_angles(angles)
    sort_points = [p for _, p in sorted(zip(adjusted_angles, points))]
    return sort_points

