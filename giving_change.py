"""
Giving change by dynamic programming

Forces to include a coin of denomination 1

Tracing solution via a hack without additional table

Jose L Balcazar, 2019
"""

def gcdptable(denoms, lim):
    "the dynamic programming function proper, tabulates subproblem solutions"
    t = {}
    for q in range(lim):
        "init table for the coin of denoms[0] == 1 unit"
        t[0, q] = q
        #print(t[0,q])
    for d in range(1, len(denoms)):
        for q in range(lim):
            if denoms[d] <= q:
                "can use one more coin of denoms[d] units, or not use it"
                t[d, q] = min( t[d-1, q],  1 + t[d, q-denoms[d]] )
            else:
                "not anymore, forget that denomination"
                t[d, q] = t[d-1, q]
    print(t)
    return t

def trace(gctab, denoms, q):
    "returns solution in dict r, uses ugly, non-generalizable hack"
    r = {}
    for dn in denoms:
        r[dn] = 0
    d = len(denoms) - 1
    while q:
        "hack - we have just two cases and, in one, t[d,q] == t[d-1,q]"
        if d == 0:
            "only unit coins are used now"
            r[denoms[d]] += q
            break
        elif gctab[d, q] == gctab[d-1, q]:
            "coins of denoms[d] units were not employed"
            d -= 1
        else:
            r[denoms[d]] += 1
            q -= denoms[d]
    return r

dq = int(input("Type in the number of coin denominations: "))
denoms = []
for d in range(dq):
    denoms.append(int(input("Denomination " + str(d) + ": ")))

lim = int(input("Type in the upper limit: "))

if 1 not in denoms:
    print("Adding a denomination of 1 so that 1 is reachable.")
    denoms.append(1)

denoms.sort()

gctab = gcdptable(denoms, lim + 1) # must reach from 0 to lim

q = int(input("Type in a quantity to reach, 0 to finish: "))

while q:
    if q > lim:
        print(q, "is too large a quantity right now, sorry.")
    else:
        r = trace(gctab, denoms, q)
        for d in sorted(r):
            print(d, ":", r[d])
    q = int(input("Type in a quantity to reach, 0 to finish: "))

# uncomment to print out the DP table in full
#for g in sorted(gctab):
#    print(g[0], g[1], ":", gctab[g])
#
