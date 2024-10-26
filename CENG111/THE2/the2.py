def check_month(month_calendar):
       
    num = [1,2,3,4,5,8,9,10,11,12,15,16,17,18,19,22,23,24,25,26,29,30,31]
    a = zip(month_calendar, num)
    b = list(a)[:]

    filtre_m = [g for g in b if "m" in g]
    points = [k[1] for k in filtre_m] #finds numbers of "m"s

    z = [j-i for i, j in zip(points[:-1], points[1:])] #finds the difference between mom's days

    diffposs = [0,7,14,21,28]
    mother = [x for x in z if x in diffposs]
    cost = 0
    errors = []

    if mother == z:
        cost = cost + len(points)*10
    else:
        errors.append(1)    

    #father
    filtre_f = [h for h in b if "f" in h]
    points_f = [j[1] for j in filtre_f]


    zf = [j-i for i, j in zip(points_f[:-1], points_f[1:])] #difference of father days

    if (1 in zf) or (len(points_f) > 2):
        errors.append(2)
    else:
        cost = cost + len(points_f)*20

    #babysitter

    filtre_b = [x for x in b if "b" in x]
    points_b = [y[1] for y in filtre_b]

    zb = [j-i for i, j in zip(points_b[:-1], points_b[1:])] #difference of babysitter days

    count1 = zb.count(2)
    count2 = zb.count(3)

    cost = cost + count1*30
    cost = cost + count2*60
    cost = cost + len(points_b)*30

    #grandma

    wednesdays = [3, 10, 17, 24, 31]

    filtre_g = [v for v in b if "g" in v]
    points_g = [n[1] for n in filtre_g]

    grand = [x for x in points_g if x in wednesdays]

    if len(grand) > 1:
        errors.append(4)
    else:
        cost = cost + len(points_g)*50

    #aunt1

    filtre_a1 = [x for x in b if "a1" in x]
    points_a1 = [x[1] for x in filtre_a1]
    tuefri = [2,5,9,12,16,19,23,26,30]
    aunt1 = [x for x in points_a1 if x in tuefri]

    if points_a1 == aunt1:
        cost = cost + len(points_a1)*32
    else:
        errors.append(5)

    #aunt2

    def plus1(plus):
        plus += 1
        return plus

    mapped = map(plus1, points_a1) #days after a1 babysat
    mappedlist = list(mapped)

    filtre_a2 = [x for x in b if "a2" in x]
    points_a2 = [x[1] for x in filtre_a2]
    aunt2 = [x for x in mappedlist if x in points_a2] #aunt2 equals to intercepts of aunt1 babysat afterdays and aunt2 babysat

    if len(aunt2) >= 1:
        errors.append(6)
    else:
        cost = cost + len(points_a2)*27

    #neighbour lady

    filtre_n = [x for x in b if "n" in x]
    points_n = [x[1] for x in filtre_n]
    montuewed = [1,2,3,8,9,10,15,16,17,22,23,24,29,30,31] #possible monday tuesday and wednesdays
    neiglady = [x for x in points_n if x in montuewed]
    cumul = [x for x in range(len(points_n))] 

    if neiglady == points_n:
        def neigcost(ncost):
            if ncost > 0:
                ncost = 5**ncost 
            
            else:
                ncost = 0
            return ncost
        mappedcumul = map(neigcost, cumul)
        listmapcumul = list(mappedcumul)
        sumcumul = sum(listmapcumul)  
        cost = cost + sumcumul

    else:
        errors.append(7)

    if len(errors) >= 1:
        return errors
    else:
        return cost
    
