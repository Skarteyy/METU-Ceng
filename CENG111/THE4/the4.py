T = ['Fatma', ['sinan', ['Elif', 'ahmet'], 'mehmet'], 'veli', ['Ayse', ['Zeynep', 'arda'], ['fikret', ['ali','mustafa']], 'hikmet']]
a = 1
def depth(L,name):
    if not L == []:
        global a
        if L[0] == name:
            return 1
        elif name in L:
            return 2
        else:
            for i in range(len(L)):
                if type(L[i]) == list:
                    a += depth(L[i],name)
                    if a != 1:
                        return a
            return 0


def finder(L,name):
    history = []
    for i in range(len(L)):
        if type(L[i]) == str:
            history = history + [L[i]]
        else:
            history = history + [L[i][0]]
    if name in L:
        return [history]    
    else:
        for i in range(len(L)):
            if type(L[i]) == list:
                x = finder(L[i],name)
                if x:
                    return x + [history]
        return False
    
def siblings(T,pname):
    v =[]
    tree = finder(T,pname)
    tree = tree + ["a"]
    if tree[0][0] == pname:
        v = v + tree[1][1:]
        if pname in v:
            v.remove(pname)
        return v
    else:
        v = v + tree[0][1:]
        if pname in v:
            v.remove(pname)
        return v

def brothers(T,pname):
    v = []
    tree = finder(T,pname)
    tree = tree + ["a"]
    if tree[0][0] == pname:
        for i in range(len(tree[1][1:])):
            if str.islower(tree[1][1:][i]):
                v = v + [tree[1][1:][i]]
        if pname in v:
            v.remove(pname) 
        return v
    else:
        for i in range(len(tree[0][1:])):
            if str.islower(tree[0][1:][i]):
                v = v + [tree[0][1:][i]]
        if pname in v:
            v.remove(pname)
        return v        
        
def sisters(T,pname):
    v = []
    tree = finder(T,pname)
    tree = tree + ["a"]
    if tree[0][0] == pname:
        for i in range(len(tree[1][1:])):
            if str.istitle(tree[1][1:][i]):
                v = v + [tree[1][1:][i]]
        if pname in v:
            v.remove(pname) 
        return v
    else:
        for i in range(len(tree[0][1:])):
            if str.istitle(tree[0][1:][i]):
                v = v + [tree[0][1:][i]]
        if pname in v:
            v.remove(pname)
        return v       

def uncles(T,pname):
    v = []
    tree = finder(T,pname)
    #tree = tree + ["a"] + ["b"]
    if depth(T,pname)<3:
        return []
    elif tree[0][0] == pname:
        for i in range(len(tree[2][1:])):
            if str.islower(tree[2][1:][i]):
                v = v + [tree[2][1:][i]]        
        if str.islower(tree[1][0]):
            v.remove(tree[1][0])
        return v
    else:
        for i in range(len(tree[1][1:])):
            if str.islower(tree[1][1:][i]):
                v = v + [tree[1][1:][i]]
        if str.islower(tree[0][0]):
            v.remove(tree[0][0])
        return v    

def aunts(T,pname):
    v = []
    tree = finder(T,pname)
    #tree = tree + ["a"] + ["b"]
    if depth(T,pname)<3:
        return []
    elif tree[0][0] == pname:
        for i in range(len(tree[2][1:])):
            if str.istitle(tree[2][1:][i]):
                v = v + [tree[2][1:][i]]        
        if str.istitle(tree[1][0]):
            v.remove(tree[1][0])
        return v
    else:
        for i in range(len(tree[1][1:])):
            if str.istitle(tree[1][1:][i]):
                v = v + [tree[1][1:][i]]
        if str.istitle(tree[0][0]):
            v.remove(tree[0][0])
        return v    

def cousins(T,pname):
    auncle = aunts(T,pname) + uncles(T,pname)
    cousine = []
    for i in range(len(auncle)):
        if finder(T,auncle[i])[0][0] == auncle[i]:
            cousine = cousine + finder(T,auncle[i])[0][1:]
            
    return cousine

print(cousins(T,'Elif'))




