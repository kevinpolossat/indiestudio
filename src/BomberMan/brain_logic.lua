function heuristic(me, id)
    return ((getNumberOfBoxes(me, 0) - getNumberOfBoxes(me, id)) * 10) + ((getNumberOfPowerUp(me, id) - getNumberOfPowerUp(me, 0)) * 100) + ((getNumberOfPlayer(me, 0) - getNumberOfPlayer(me, id)) * 1000)
end

function calculate(me, id, depth)
    if depth == getMaxDepth(me) then
        doUpdate(me, id, 200)
        if amIDead(me, id) then
            return -1
        end
        return heuristic(me, id)
    end

    local res = {}
    for action=0,5 do
        if amIDead(me, id) then
            res[#res+1] = -1
        else
            if isActionPossible(me, id, action) then
                local r = copy(me, id)
                doAction(me, r, action)
                doUpdate(me, r, 0)
                res[#res+1] = calculate(me, r, depth + 1) + heuristic(me, id)
            else
                res[#res+1] = -1
            end
        end
    end

    local m = math.max(table.unpack(res))
    if depth == 0 then
        local ret = {}
        for k in pairs (res) do
            if res[k] == m then
                ret[#ret+1] = k - 1
            end
        end
        if #ret == 1 then
            return ret[1]
        end
        if m == 0 then
            for k in pairs (ret) do
                if ret[k] == 0 then
                    ret[k] = nil
                end
            end
        end
        return ret[math.random(#ret)]
    end
    return m
end

brain = function(me)
    return calculate(me, 0, 0)
end