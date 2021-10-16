def mycheck(game):
    # print(game)
    a, b = list(map(int, game.split(':')))
    sn = 0
    if a >= b:
        aa = a
        bb = b
        sa = 1
        sb = 2
    else:
        aa = b
        bb = a
        sa = 2
        sb = 1
    if mustwin != 0 and sa != mustwin:
        return sn
    if aa >= 8 or aa < 6:
        return sn
    if aa == 7:
        if bb == 5 or bb == 6:
            return sa
        return sn
    if aa - bb >= 2:
        return sa
    return sn


def check3(game):
    a, b = list(map(int, game.split(':')))
    if a - b >= 2 and a >= 6:
        if mustwin == 2:
            return 0
        return 1
    if b - a >= 2 and b >= 6:
        if mustwin == 1:
            return 0
        return 2
    return 0


name1, name2 = input().split(' ')
n = int(input())
mustwin = 0
if name1 == 'federer' or name2 == 'federer':
    if name1 == 'federer':
        mustwin = 1
    else:
        mustwin = 2

for i in range(n):
    fl = True
    games = input().split(' ')
    games_cnt = len(games)
    cnt = [0, 0, 0]
    if games_cnt == 2 or games_cnt == 3:
        for i in range(2):
            k = mycheck(games[i])
            if k == 0:
                fl = False
                break
            cnt[k] += 1
            if cnt[k] >= 2 and games_cnt == 3:
                fl = False
                break
        if not fl:
            print("ne")
            continue
        if games_cnt == 2:
            if cnt[1] == 2 or cnt[2] == 2:
                if mustwin == 0:
                    print("da")
                else:
                    if cnt[mustwin] < 2:
                        print("ne")
                    else:
                        print("da")
            else:
                print("ne")
            continue
        else:
            k = check3(games[2])
            if k == 0:
                print("ne")
            else:
                if mustwin == 0:
                    print("da")
                else:
                    cnt[k] += 1
                    if cnt[mustwin] < 2:
                        print("ne")
                    else:
                        print("da")
    else:
        print("ne")
