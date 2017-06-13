import random
import brain
b = brain.IA()

actions = [0, 1, 2, 3, 4, 5]

def heuristic(id):
    return ((b.getNumberOfBoxesFromId(0) - b.getNumberOfBoxesFromId(id)) * 10)
    + ((b.getNumberOfPowerUpFromId(id) - b.getNumberOfPowerUpFromId(0)) * 100)
    + ((b.getNumberOfPlayerFromId(0) - b.getNumberOfPlayerFromId(id)) * 1000)

def calculate(id, depth):
    if depth == b.getMaxDepth():
        b.doUpdateFromId(id, 200)
        if b.amIDeadFromId(id):
            return -1
        return heuristic(id)

    res = []
    for action in actions:
        if b.amIDeadFromId(id):
            res += [-1]
        else:
            if b.isActionPossible(id, action):
                r = b.copyFromRefereeId(id)
                b.doActionFromId(r, action)
                b.doUpdateFromId(r, 0)
                h = calculate(r, depth + 1)
                res += [h + heuristic(id)]
            else:
                res += [-1]
    m = max(res)
    if depth == 0:
        ret = [i for i, j in enumerate(res) if j == m]
        if len(ret) == 1:
            return ret[0]
        if m == 0:
            ret = filter(lambda a: a != 0, ret)
        return random.choice(ret)
    return m

def execute():
    return calculate(0, 0)
